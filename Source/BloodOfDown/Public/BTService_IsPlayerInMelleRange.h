// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsPlayerInMelleRange.generated.h"

/**
 * 
 */
UCLASS()
class BLOODOFDOWN_API UBTService_IsPlayerInMelleRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_IsPlayerInMelleRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	float MeleeRange = 2.5f;
};
