#pragma once

#include "CoreMinimal.h"
#include "EResponseDamageType.generated.h"


UENUM(BlueprintType)
enum class EResponseDamageType : uint8
{
    None        UMETA(DisplayName = "None"),
    Stun        UMETA(DisplayName = "Stun"),
    Hit         UMETA(DisplayName = "Hit"),
    Bleeding    UMETA(DisplayName = "Bleeding"),
    Knock       UMETA(DisplayName = "Knock")
};