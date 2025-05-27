#pragma once

#include "CoreMinimal.h"
#include "EDamageType.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None	   UMETA(DisplayName = "None"),
	Projectile UMETA(DisplayName = "Projectile"),
	Explosion  UMETA(DisplayName = "Explosion"),
	Melee	   UMETA(DisplayName = "Melee")
};