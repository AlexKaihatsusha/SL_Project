// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoloLevelingGameMode.h"
#include "SoloLevelingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASoloLevelingGameMode::ASoloLevelingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
