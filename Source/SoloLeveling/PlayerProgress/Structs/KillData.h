#pragma once

#include "CoreMinimal.h"
#include "KillData.generated.h"

USTRUCT(BlueprintType)
struct FKillData
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillData")
    AActor* Killer;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillData")
    int32 AmountOfDamage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillData")
    bool bHeadshot;

    // Default constructor
    FKillData() :Killer(nullptr), bHeadshot(false)
    {
    }
};