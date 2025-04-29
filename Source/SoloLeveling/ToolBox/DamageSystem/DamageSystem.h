#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../DamageSystem/Structs/DamageData.h"
#include "DamageSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlocking,)




DECLARE_LOG_CATEGORY_EXTERN(UDamageSystemLog, Log, All);

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
/* Actual Interface declaration. */
class UDamageSystem: public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageSystem();
	UFUNCTION(BlueprintCallable, Category = "DamageSystem|Functions")
	float Heal(float HealAmount);
	UFUNCTION(BlueprintCallable, Category = "DamageSystem|Functions")
	bool  TakeDamage(FDamageData DamageData);
	UFUNCTION(BlueprintCallable, Category = "DamageSystem|Functions")
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "DamageSystem|Functions")
	float GetCurrentHealth();
	
	//Getters
	UFUNCTION(BlueprintPure, Category = "DamageSystem|Functions|Getters")
	bool GetIsDead() const { return IsDead;}

	//Setters
	UFUNCTION(BlueprintCallable, Category = "DamageSystem|Functions|Setters")
	void SetIsDead(bool Dead);

	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "DamageSystem|Delegates")
	FOnDeath OnDeath;

protected:
	bool IsOwnerDead();
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsBlocking = false;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsInvincible = false;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsParring = false;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsDead = false;
	//bool IsOwnerDead() const;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSystem|Variables|Health")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSystem|Variables|Health")
	float CurrentHealth = 0.f;
private:
	bool DamageReceived = false;
};