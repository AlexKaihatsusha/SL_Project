#pragma once

#include "CoreMinimal.h"
#include "BaseItemData.h"
#include "BaseWeaponItemData.generated.h"

class UNiagaraSystem;
UENUM(BlueprintType)
enum class EWeaponItemType : uint8
{
	None		UMETA(DisplayName = "None"),
	Firearm		UMETA(DisplayName = "Firearm"),
	Range		UMETA(DisplayName = "Range"),
	Melee		UMETA(DisplayName = "Melee"),
};

UCLASS(BlueprintType)
class UBaseWeaponItemData : public UBaseItemData
{
	GENERATED_BODY()

public:
	UBaseWeaponItemData();

	UBaseWeaponItemData(const EWeaponItemType WeaponItemType, const float& DamageAmount)
		: WeaponItemType(WeaponItemType), DamageAmount(DamageAmount) {};
	
public://General Weapon Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData")
	EWeaponItemType WeaponItemType = EWeaponItemType::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|WeaponData")
	float DamageAmount = 20;

};