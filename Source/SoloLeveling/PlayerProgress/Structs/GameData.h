#pragma once

#include "CoreMinimal.h"
#include "../Structs/KillData.h"
#include "GameData.generated.h"

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data")
    int32 CompletedLevels;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data|Statistics")
    int32 Kills;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data|Statistics")
    int32 DamageCaused;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data|Statistics")
    int32 Headshots;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data|Statistics")
    int32 SolvedPuzzles;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data|Statistics")
    int32 Deaths;
    
    //add KillData
    void operator+=(const FKillData& killData)
    {
        ++Kills;
        DamageCaused += killData.AmountOfDamage;
        killData.bHeadshot ? ++Headshots : Headshots;
    }
    
    // Default constructor
    FGameData() :CompletedLevels(0), Kills(0), Headshots(0), SolvedPuzzles(0), Deaths(0)
    {
    }
};