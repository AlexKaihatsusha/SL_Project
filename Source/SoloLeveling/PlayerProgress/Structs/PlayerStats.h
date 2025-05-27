#pragma once

#include "CoreMinimal.h"
#include "PlayerStats.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Agility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Intelligence;

	// Default constructor
	FPlayerStats()
		: Strength(1), Agility(1), Intelligence(1)
	{
	}
};