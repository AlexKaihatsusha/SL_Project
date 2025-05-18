#pragma once

#include "CoreMinimal.h"
#include "WaveData.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data", meta = (ClampMin = 0.0f))
    float DurationTime;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data", meta = (ClampMin = 0.0f))
    float SpawnInterval;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
    TArray<TSubclassOf<AActor>> Enemies;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
    TArray<TObjectPtr<AActor>> SpawnPoints;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
    FString Description;

    // Default constructor
    FWaveData() : DurationTime(0.0f), SpawnInterval(1.0f)
    {
    }
};



