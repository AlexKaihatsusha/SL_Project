#pragma once
#include "CoreMinimal.h"
#include "../Public/UObject/Interface.h"
#include "../DamageSystem/Structs/DamageData.h"
#include "Damageable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/* Actual Interface declaration. */
class IDamageable
{
	GENERATED_BODY()

public:
	/* A version of the React To Trigger function that can be implemented in C++ or Blueprint. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions|Interface")
	float Heal(float HealAmount);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions|Interface")
	bool TakeDamage(FDamageData DamageData);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions|Interface")
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions|Interface")
	float GetCurrentHealth();
};