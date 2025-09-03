#pragma once

#include "CoreMinimal.h"
#include "BaseItemData.h"
#include "BaseUsableItemData.generated.h"
class UNiagaraSystem;
UENUM(BlueprintType)
enum class EUsableItemType : uint8
{
	None         UMETA(DisplayName = "None"),	
	Consumable	 UMETA(DisplayName = "Consumable"),
	Throwable	 UMETA(DisplayName = "Throwable"),
	Placeable	 UMETA(DisplayName = "Placeable"),
};

UCLASS(BlueprintType)
class UBaseUsableItemData : public UBaseItemData
{
	GENERATED_BODY()

public:
	UBaseUsableItemData();

	UBaseUsableItemData(
		const EUsableItemType					UsableItemType,
		const float&							UseCooldown,
		const int32&							MaxUses,
		const float&							EffectAmount,
		const TSoftObjectPtr<USoundBase>&		UseSound,
		const TSoftObjectPtr<UNiagaraSystem>&	VisualNiagaraEffect)
		: 
		UsableItemType(UsableItemType), 
		UseCooldown(UseCooldown), 
		MaxUses(MaxUses), 
		EffectAmount(EffectAmount),
		UseSound(UseSound), 
		VisualNiagaraEffect(VisualNiagaraEffect) {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|UsableData")
	EUsableItemType UsableItemType = EUsableItemType::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|UsableData")
	float UseCooldown = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|UsableData")
	int32 MaxUses = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|UsableData", 
		meta = (EditCondition = "UsableItemType==EUsableItemType::Consumable", EditConditionHides))
	float EffectAmount = 20.0f; //Heal, shield amount etc.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|UsableData")
	TSoftObjectPtr<USoundBase> UseSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|UsableData")
	TSoftObjectPtr<UNiagaraSystem> VisualNiagaraEffect;
};