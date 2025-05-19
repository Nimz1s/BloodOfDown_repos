// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NPC.h"
#include "BehaviorTree/BehaviorTreeComponent.h" 
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_MelleAttack.generated.h"

/**
 * 
 */
UCLASS()
class BLOODOFDOWN_API UBTTask_MelleAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MelleAttack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	bool MontageHasFinished(ANPC* npc);
	
};
