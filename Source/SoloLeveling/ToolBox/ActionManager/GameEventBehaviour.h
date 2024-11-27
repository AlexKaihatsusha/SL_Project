#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ActionManager/Event.h"
#include "GameEventBehaviour.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class UGameEventBehaviour : public UObject, public IEvent
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void  OnBegin_Implementation(bool bFirstTime) override;
	UFUNCTION()
	virtual void  OnUpdate_Implementation()override;
	UFUNCTION()
	virtual void  OnEnd_Implementation()override;
	UFUNCTION()
	virtual bool  IsDone_Implementation()override;
};
