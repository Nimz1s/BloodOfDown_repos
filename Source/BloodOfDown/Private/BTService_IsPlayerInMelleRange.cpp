// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMelleRange.h"
#include "NPC_AIController.h"
#include "NPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInMelleRange::UBTService_IsPlayerInMelleRange()
{
	NodeName = TEXT("Is Player In Melle Range");
	bNotifyBecomeRelevant = true;
}

void UBTService_IsPlayerInMelleRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get controller and NPC
	auto const* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	auto const* const npc = Cast<ANPC>(cont->GetPawn());
	// get player character
	auto const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// write true or false to the blackboard key depending on whether or not the player is in range
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		GetSelectedBlackboardKey(),
		npc->GetDistanceTo(player) <= MeleeRange);
}
