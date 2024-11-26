#pragma once

#include "CoreMinimal.h"
#include "SL_Shard.h"
#include "SL_HealthShard.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(SL_HealthShard, Log, All)
UCLASS()
class ASL_HealthShard : public ASL_Shard
{
	GENERATED_BODY()
public:
	ASL_HealthShard();

	UFUNCTION(BlueprintCallable, Category= "Health Shard")
	void SetHealthAmount(float Value);
	UFUNCTION(BlueprintCallable, Category= "Health Shard")
	float GetHealthAmount();
protected:
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;
private:
	UPROPERTY(EditDefaultsOnly, Category="Health Shard | Attributes")
	float HealthAmount = 10.f;
};
