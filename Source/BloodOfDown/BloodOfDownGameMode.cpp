// Copyright Epic Games, Inc. All Rights Reserved.

#include "BloodOfDownGameMode.h"
#include "BloodOfDownCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABloodOfDownGameMode::ABloodOfDownGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
