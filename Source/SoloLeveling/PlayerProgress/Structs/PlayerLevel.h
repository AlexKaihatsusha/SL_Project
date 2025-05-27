#pragma once

#include "CoreMinimal.h"
#include "PlayerLevel.generated.h"

USTRUCT(BlueprintType)
struct FPlayerLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerLevel")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerLevel")
	float CurrentXP;
	// Default constructor
	FPlayerLevel()
		: Level(0), CurrentXP(0.f)
	{
	}
};
