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
public:
	virtual void  OnBegin_Implementation(bool bFirstTime) override;
	virtual void  OnUpdate_Implementation()override;
	virtual void  OnEnd_Implementation()override;
	virtual bool  IsDone_Implementation()override;
};
