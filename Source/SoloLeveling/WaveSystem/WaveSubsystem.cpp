#include "WaveSubsystem.h"

DEFINE_LOG_CATEGORY(UWaveSubsystemLog);


UWaveSubsystem::UWaveSubsystem()
{
}

void UWaveSubsystem::Deinitialize()
{
}

void UWaveSubsystem::StartNewWave(FWaveData NewWaveData)
{
	//I don't want to start new Wave if current still in progress
	if (bWaveInProgress)
		return;
	currentWave = NewWaveData;
	WaveTimer.Invalidate();
	
	GetWorld()->GetTimerManager().SetTimer(WaveTimer, this, &UWaveSubsystem::EndWave, currentWave.DurationTime, false, false);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this, &UWaveSubsystem::SpawnEnemy, currentWave.SpawnInterval, true, true);
	//delegate call
	OnWaveStarted.Broadcast(currentWave);

	UE_LOG(UWaveSubsystemLog, Log, TEXT("Wave is started %s"), *currentWave.Description);

}

void UWaveSubsystem::EndWave()
{
	UE_LOG(UWaveSubsystemLog, Log, TEXT("Wave is finished %s"), *currentWave.Description);
	bWaveInProgress = false;
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	GetWorld()->GetTimerManager().ClearTimer(WaveTimer);
	OnWaveFinished.Broadcast();

}

void UWaveSubsystem::SpawnEnemy()
{
	UE_LOG(UWaveSubsystemLog, Log, TEXT("SpawnEnemy call"));
}


