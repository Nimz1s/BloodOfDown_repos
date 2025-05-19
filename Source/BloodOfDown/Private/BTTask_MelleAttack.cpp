// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MelleAttack.h"
#include "CombatInterface.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/world.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_MelleAttack::UBTTask_MelleAttack()
{
	NodeName = TEXT("Melle Attack");
}
EBTNodeResult::Type UBTTask_MelleAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// if we are out of range, do not attack the player
	auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		// finish the task
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
		
	//I we are in range so get the AI's controller and the NPC itself
	auto const * const cont = OwnerComp.GetAIOwner();
	auto* const npc = Cast<ANPC>(cont->GetPawn());
	// if the NPC supports the ICombatInterface, cast and call the Execute_MeleeAttack function
	if (auto* const icombat = Cast<ICombatInterface>(npc))
	{
		// necessary check to see if the montage has finished so we don't try and play it again
		if (MontageHasFinished(npc))
		{
			icombat->Execute_MeleeAttack(npc);
		}	
	}
	// finish the task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_MelleAttack::MontageHasFinished(ANPC* npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}
