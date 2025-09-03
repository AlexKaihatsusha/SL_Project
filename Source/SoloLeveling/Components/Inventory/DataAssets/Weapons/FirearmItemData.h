#pragma once

#include "CoreMinimal.h"
#include "../BaseWeaponItemData.h"
#include "FirearmItemData.generated.h"

class UNiagaraSystem;

UCLASS(BlueprintType)
class UFirearmItemData : public UBaseWeaponItemData
{
	GENERATED_BODY()

public:
	UFirearmItemData();

public: // Firearm weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Firearm", EditConditionHides))
	int32 AmmoAmount = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Firearm", EditConditionHides))
	int32 MaxAmmoStackAmount = 30;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Firearm", EditConditionHides))
	int32 ClipsAmount = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Firearm", EditConditionHides))
	TSoftObjectPtr<USoundBase> FireSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Firearm", EditConditionHides))
	TSoftObjectPtr<USoundBase> ReloadSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Firearm", EditConditionHides))
	TSoftObjectPtr<UNiagaraSystem> MuzzleVisualNiagaraEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData",
		meta = (EditCondition = "WeaponItemType==EWeaponItemType::Firearm", EditConditionHides))
	TSoftObjectPtr<UNiagaraSystem> ImpactVisualNiagaraEffect;
};