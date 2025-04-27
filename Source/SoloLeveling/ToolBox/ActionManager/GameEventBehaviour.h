#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Public/Tickable.h"
#include "../ActionManager/Event.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameEventBehaviour.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(UGameEventBehaviourLog, Log, All)
/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class UGameEventBehaviour : public UObject, public FTickableGameObject, public IEvent
{
	GENERATED_BODY()
public:
	UGameEventBehaviour();
	//FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override { return bTickEnabled; }
	//-----------------------------

	//IEvent interface
	UFUNCTION()
	virtual void  OnBegin_Implementation(bool bFirstTime) override;
	UFUNCTION()
	virtual void  OnUpdate_Implementation()override;
	UFUNCTION()
	virtual void  OnEnd_Implementation()override;
	UFUNCTION()
	virtual bool  IsDone_Implementation()override;
	//----------------



	UFUNCTION(BlueprintCallable)
	void Init(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "World")
	virtual UWorld* GetWorld() const override;
	
protected:
	bool bTickEnabled = false;
	UPROPERTY()
	TObjectPtr<UWorld> WorldRef;
};
