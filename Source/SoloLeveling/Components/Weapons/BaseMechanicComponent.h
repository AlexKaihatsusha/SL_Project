#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMechanicComponent.generated.h"


UCLASS()
class UBaseMechanicComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseMechanicComponent();

	UFUNCTION(BlueprintCallable)
	virtual void EquipItem(AActor* ActorToEquip);
	
	UFUNCTION(BlueprintCallable)
	virtual void UnequipItem();

public:

	//TODO: Sockets names for different types of weapons
	//TODO: BasicEquipLogic to use as base implementation
	//etc.
};