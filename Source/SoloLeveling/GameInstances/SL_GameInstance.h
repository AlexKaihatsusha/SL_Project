// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <SoloLeveling/ToolBox/ActionManager/EventHandler.h>
#include "SL_GameInstance.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(USL_GameInstanceLog, Log, All)
UCLASS()
class SOLOLEVELING_API USL_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Events")
	UEventHandler* EventHandler = nullptr;

	virtual void Init() override;
	virtual void Shutdown() override;
};
