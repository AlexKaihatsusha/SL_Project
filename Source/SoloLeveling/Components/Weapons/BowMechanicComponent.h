#pragma once

#include "CoreMinimal.h"
#include "BaseMechanicComponent.h"
#include "BowMechanicComponent.generated.h"

UCLASS()
class UBowMechanicComponent : public UBaseMechanicComponent
{
	GENERATED_BODY()

public:
	UBowMechanicComponent();

	virtual void EquipItem(AActor* ActorToEquip) override;
	virtual void UnequipItem() override;
};