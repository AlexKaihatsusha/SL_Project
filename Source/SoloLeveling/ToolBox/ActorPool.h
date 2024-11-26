// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../ToolBox/PooledActor.h"
#include "ActorPool.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(UActorPoolLog, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOLOLEVELING_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActorPool();
	APooledActor* FindFirstAvailableActor();
	APooledActor* SpawnActorFromPool(FTransform transform);

protected:
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void	InitializePool();
	UPROPERTY(EditDefaultsOnly, Category = "Object Pool Settings")
	int PoolSize = 0;
	UPROPERTY(EditDefaultsOnly, Category ="Object Pool Settings")
	TSubclassOf<APooledActor> PoolActorClass = nullptr;
	UPROPERTY(VisibleInstanceOnly)
	TArray<APooledActor*> ObjectPool = {nullptr};
};
