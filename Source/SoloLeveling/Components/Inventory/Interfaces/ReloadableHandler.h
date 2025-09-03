#pragma once

#include "CoreMinimal.h"
#include "../Public/UObject/Interface.h"
#include "ReloadableHandler.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UReloadableHandler : public UInterface
{
	GENERATED_BODY()
};

/* Actual Interface declaration. */
class IReloadableHandler
{
	GENERATED_BODY()

public:
	/* A version of the React To Trigger function that can be implemented in C++ or Blueprint. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Reload Item Input")
	void OnReloadPressed();
	
};