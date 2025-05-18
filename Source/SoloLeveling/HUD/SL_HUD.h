#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SL_HUD.generated.h"


UCLASS(Blueprintable, BlueprintType)
class SOLOLEVELING_API USL_HUD :public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
};