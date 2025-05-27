#pragma once

#include "GameFramework/PlayerController.h"
#include "SL_PlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewCurrentHealth);

UCLASS(Blueprintable, BlueprintType)
class SOLOLEVELING_API ASL_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASL_PlayerController();
	//for health bar 
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnHealthChanged OnHealthChanged;
};