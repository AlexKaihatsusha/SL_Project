#pragma once

#include "CoreMinimal.h"
#include "../Enums/EDamageType.h" 
#include "../Enums/EResponseDamageType.h"
#include "DamageData.generated.h"

USTRUCT(BlueprintType)
struct FDamageData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
    float Amount;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
    bool bHeadshot;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData|Enums")
    EDamageType DamageType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData|Enums")
    EResponseDamageType ResponseDamageType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
    bool bForceAnimationInterrupt;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
    bool bDoInvincibleDamage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
    bool bCanBeBlocked;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
    bool bCanBeParried;

    // Default constructor
    FDamageData()
        :Amount(0), 
        bHeadshot(false),
        DamageType(EDamageType::None),
        ResponseDamageType(EResponseDamageType::None),
        bForceAnimationInterrupt(false),
        bDoInvincibleDamage(false),
        bCanBeBlocked(false),
        bCanBeParried(false)
    {}
};