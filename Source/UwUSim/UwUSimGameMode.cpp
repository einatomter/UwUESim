// Copyright Epic Games, Inc. All Rights Reserved.

#include "UwUSimGameMode.h"
#include "UwUSimCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUwUSimGameMode::AUwUSimGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
