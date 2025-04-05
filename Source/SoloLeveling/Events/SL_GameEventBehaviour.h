// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ToolBox/ActionManager/GameEventBehaviour.h"
#include "SL_GameEventBehaviour.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SOLOLEVELING_API USL_GameEventBehaviour : public UGameEventBehaviour
{
	GENERATED_BODY()
protected:
	//to make event able to access the current world, and able to work with current world;
	UPROPERTY(BlueprintReadOnly, Category = "SL_GameEventBehaviour")
	UWorld* WorldContext;
public:
	//to init the world
	void SetCurrentWorld(UWorld* CurrentWorld) { WorldContext = CurrentWorld; }
	//To push through Blueprint, since only GameEventBehaviour can be blueprintable and used there 
	UFUNCTION(BlueprintPure, Category = "SL_GameEventBehaviour")
	UWorld* GetCurrentWorld() const { return WorldContext; }
	virtual void  OnBegin_Implementation(bool bFirstTime) override;
	virtual void  OnUpdate_Implementation()override;
	virtual void  OnEnd_Implementation()override;
	virtual bool  IsDone_Implementation()override;
};
