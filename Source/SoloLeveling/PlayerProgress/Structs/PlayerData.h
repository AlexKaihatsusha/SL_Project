#pragma once

#include "CoreMinimal.h"
#include "../Structs/PlayerLevel.h"
#include "../Structs/PlayerStats.h"
#include "../Structs/GameData.h"
#include "PlayerData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	FPlayerLevel PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	FPlayerStats PlayerStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	FGameData PlayerProgressData;

	// Default constructor
	FPlayerData()
	{
	}
};
