#pragma once

#include "CoreMinimal.h"
#include "../Public/UObject/Interface.h"
#include "AimableHandler.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UAimableHandler : public UInterface
{
	GENERATED_BODY()
};

/* Actual Interface declaration. */
class IAimableHandler
{
	GENERATED_BODY()

public:
	/* A version of the React To Trigger function that can be implemented in C++ or Blueprint. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Aim Item Input")
	void OnAimPressed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Aim Item Input")
	void OnAimReleased();
	
};