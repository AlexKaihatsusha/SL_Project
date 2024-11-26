// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioMixerTrace.h"
#include "GameFramework/Actor.h"
#include "SL_HealthGrenade.generated.h"

class UStaticMeshComponent;
class ASL_HealthShard;
UCLASS()
class ASL_HealthGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASL_HealthGrenade();

protected:
	
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

public:	
	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Health Shard")
	TSubclassOf<ASL_HealthShard> HealthShardClass;

	UPROPERTY(EditAnywhere, Category = "Health Shard", meta=(ClampMin = "0"))
	int32 NumOfShards = 10;

	UPROPERTY(EditAnywhere, Category = "Health Shard", meta=(ClampMin = "0"))
	float MinHealth = 10.f;
	UPROPERTY(EditAnywhere, Category = "Health Shard", meta=(ClampMin = "0"))
	float MaxHealth = 30.f;
	UPROPERTY(EditAnywhere, Category = "Health Shard", meta=(ClampMin = "0"))
	float MinSpeed = 100.f;
	UPROPERTY(EditAnywhere, Category = "Health Shard", meta=(ClampMin = "0"))
	float MaxSpeed = 300.f;
	UPROPERTY(EditAnywhere, Category = "Health Shard", meta=(ClampMin = "0"))
	float Radius = 200.f;
	UPROPERTY(EditAnywhere, Category = "Health Shard", meta=(ClampMin = "0"))
	float ActivationDelay = 2.f;
	UFUNCTION(BlueprintCallable, Category= "Health Grenade")
	void UseGrenage();
private:
	UFUNCTION()
	void ActivateGrenade();

	FTimerHandle ActivationHandle;
};
