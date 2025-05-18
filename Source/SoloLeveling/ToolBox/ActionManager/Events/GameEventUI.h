#pragma once

#include "CoreMinimal.h"
#include "GameEvent.h"
#include "GameEventUI.generated.h"



UCLASS(BlueprintType, Blueprintable)

class SOLOLEVELING_API UGameEventUI : public UGameEvent
{
	GENERATED_BODY()
	UGameEventUI();
	//Need to assign PlayerController 
	UGameEventUI(TObjectPtr<APlayerController> PlayerController) : PlayerController(PlayerController) {};
	

public:
	virtual void  OnBegin_Implementation(bool bFirstTime) override;
	virtual void  OnUpdate_Implementation()override;
	virtual void  OnEnd_Implementation()override;
	virtual bool  IsDone_Implementation()override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "UI Event Data")
	TSubclassOf<UUserWidget> WidgetToCreate = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "UI Event Data")
	TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "UI Event Data")
	FString TextToDisplay = "None";
};