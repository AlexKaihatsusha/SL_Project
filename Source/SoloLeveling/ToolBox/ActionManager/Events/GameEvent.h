// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Events/Base/GameEventBehaviour.h"
#include "GameEvent.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SOLOLEVELING_API UGameEvent : public UGameEventBehaviour
{
	GENERATED_BODY()
protected:

public:
	virtual void  OnBegin_Implementation(bool bFirstTime) override;
	virtual void  OnUpdate_Implementation()override;
	virtual void  OnEnd_Implementation()override;
	virtual bool  IsDone_Implementation()override;
	
	FString DebugText = "None";

	//Main, means that it has to interrupt the current event stack
	UPROPERTY(BlueprintReadWrite, Category = "Event")
	bool bIsMainEvent = true;
};
