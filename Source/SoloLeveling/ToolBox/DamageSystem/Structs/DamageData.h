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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData|Enums")
    EDamageType DamageType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData|Enums")
    EResponseDamageType ResponseDamageType;

    // Default constructor
    FDamageData()
        : Amount(0), DamageType(EDamageType::None), ResponseDamageType(EResponseDamageType::None)
    {
    }
};