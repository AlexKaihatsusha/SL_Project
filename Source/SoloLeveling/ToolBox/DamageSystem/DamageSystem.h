#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../DamageSystem/Structs/DamageData.h"
#include "../DamageSystem/Enums/EResponseDamageType.h"
#include "DamageSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlocked, bool, CanBeParried);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageResponse, EResponseDamageType, ResponseDamageType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageReceived, float, currentHealth);




DECLARE_LOG_CATEGORY_EXTERN(UDamageSystemLog, Log, All)

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
/* Actual Interface declaration. */
class UDamageSystem: public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageSystem();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions")
	float Heal(float HealAmount);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions")
	bool  TakeDamage(FDamageData DamageData);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions")
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageSystem|Functions")
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, Category = "DamageSystem|Functions")
	void ApplyDamage(float DamageAmount);

	UFUNCTION(BlueprintPure, Category = "DamageSystem|Functions")
	bool IsOwnerDead() const;

	//Getters
	UFUNCTION(BlueprintPure, Category = "DamageSystem|Functions|Getters")
	bool GetIsDead() const { return IsDead;}

	//Setters
	UFUNCTION(BlueprintCallable, Category = "DamageSystem|Functions|Setters")
	void SetIsDead(bool Dead);

	//Delegates
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "DamageSystem|Delegates")
	FOnDeath OnDeath;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "DamageSystem|Delegates")
	FOnBlocked OnBlocked;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "DamageSystem|Delegates")
	FOnDamageResponse OnDamageResponse;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "DamageSystem|Delegates")
	FOnDamageReceived OnDamageReceived;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsBlocking = false;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsInterruptible = false;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsInvincible = false;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsParring = false;
	UPROPERTY(BlueprintReadWrite, Category = "DamageSystem|Variables|States")
	bool IsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSystem|Variables|")
	bool IsDamageReceived = false;
	//bool IsOwnerDead() const;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSystem|Variables|Health")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSystem|Variables|Health")
	float CurrentHealth = 0.f;
	
private:
	
};