// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class BLOODOFDOWN_API UBTService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
<<<<<<< HEAD

public:
=======
	
public:

>>>>>>> 42
	UBTService_ChangeSpeed();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
<<<<<<< HEAD
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "AI", meta = (AllowPrivateAccess = "true"))
	float Speed = 600.f;
	
=======
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AT", meta=(AllowPrivateAccess = "yes"))
	float Speed = 600.f;
>>>>>>> 42
};
