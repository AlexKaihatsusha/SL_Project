#pragma once

#include "CoreMinimal.h"
#include "../Public/UObject/Interface.h"
#include "BaseInputItemHandler.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UBaseInputItemHandler : public UInterface
{
	GENERATED_BODY()
};

/* Actual Interface declaration. */
class IBaseInputItemHandler
{
	GENERATED_BODY()

public:
	/* A version of the React To Trigger function that can be implemented in C++ or Blueprint. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Input")
	void OnPrimaryActionPressed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Input")
	void OnPrimaryActionReleased();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Input")
	void OnSecondaryActionPressed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Input")
	bool OnSecondaryActionReleased();
};