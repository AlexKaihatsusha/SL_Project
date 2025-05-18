// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Public/UObject/Object.h"
#include "WaveData.h"
#include "TimerManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WaveSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStarted, const FWaveData&, CurrentWaveData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveFinished);
DECLARE_LOG_CATEGORY_EXTERN(UWaveSubsystemLog, Log, All)

UCLASS(Blueprintable, BlueprintType)
class  UWaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	//base
public:
	UWaveSubsystem();

	virtual void Deinitialize() override;

	UPROPERTY(BlueprintAssignable, Category = "Wave Subsystem | Delegates")
	FOnWaveStarted OnWaveStarted;
	UPROPERTY(BlueprintAssignable, Category = "Wave Subsystem | Delegates")
	FOnWaveFinished OnWaveFinished;


	UFUNCTION(BlueprintCallable)
	void StartNewWave(FWaveData NewWaveData);

	UFUNCTION(BlueprintPure)
	bool GetIsCurrentWaveInProgress() { return bWaveInProgress; }
	
	FWaveData GetCurrentWaveData() { return currentWave; }

private:

	FTimerHandle WaveTimer;
	FTimerHandle SpawnTimer;


	UPROPERTY(VisibleAnywhere, Category = "Wave System")
	FWaveData currentWave;

	UPROPERTY(VisibleAnywhere, Category = "Wave System")
	bool bWaveInProgress = false;

	void EndWave();
	void SpawnEnemy();
};
