#pragma once
#include "CoreMinimal.h"
#include "../Public/UObject/Interface.h"
#include "Event.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UEvent : public UInterface
{
	GENERATED_BODY()
};

/* Actual Interface declaration. */
class IEvent
{
	GENERATED_BODY()

public:
	/* A version of the React To Trigger function that can be implemented in C++ or Blueprint. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IEvent")
	void OnBegin(bool bFirstTime);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IEvent")
	void OnUpdate();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IEvent")
	void OnEnd();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IEvent")
	bool IsDone();

};