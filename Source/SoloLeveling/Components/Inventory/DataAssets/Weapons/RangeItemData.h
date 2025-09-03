#pragma once

#include "CoreMinimal.h"
#include "../BaseWeaponItemData.h"
#include "RangeItemData.generated.h"

class UNiagaraSystem;

UCLASS(BlueprintType)
class URangeItemData : public UBaseWeaponItemData
{
	GENERATED_BODY()

public:
	URangeItemData();

public: // Range weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Range", EditConditionHides))
	int32 ProjectilesAmount = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Range", EditConditionHides))
	int32 MaxProjectilesStackAmount = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Range", EditConditionHides))
	TSoftObjectPtr<USoundBase> ShootSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Range", EditConditionHides))
	TSoftObjectPtr<UNiagaraSystem> ShootVisualNiagaraEffect;

};