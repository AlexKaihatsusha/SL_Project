#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SL_HealthComponent.generated.h"
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);


UCLASS(meta = (BlueprintSpawnableComponent))
class USL_HealthComponent:public UActorComponent
{
	GENERATED_BODY()
public:
	USL_HealthComponent();
	//functions
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float HealthAmount);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);
	UFUNCTION(BlueprintPure)
	bool IsOwnerDead();
	//variables
	
	//UPROPERTY(BlueprintAssignable, Category = "Health")
	//FOnDeath OnDeath;
protected:
	
	virtual void BeginPlay() override;
private:
	void Death();
	
};
