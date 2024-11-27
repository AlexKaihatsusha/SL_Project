// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/UObject/Object.h"
#include "../Public/Tickable.h"
#include "../ActionManager/Event.h"
#include "../ActionManager/GameEventBehaviour.h"
#include "EventHandler.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(UEventHandlerLog, Log, All)

UCLASS()
class  UEventHandler : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
//base
public:
public:
	UEventHandler();
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	UWorld* GetWorld() const override;
	//EventHandler logic is below
	UFUNCTION(BlueprintCallable, Category = "Evenet Handler")
	void SetActive(bool bIsActive);
	UFUNCTION(BlueprintCallable, Category = "Evenet Handler")
	bool IsActive() const;
	UFUNCTION(BlueprintCallable, Category = "Event Handler")
	void PushEventByClass(TSubclassOf<UGameEventBehaviour> EventClass);

	UFUNCTION(BlueprintCallable, Category = "Event Handler")
	void PushEvent(const TScriptInterface<IEvent>& evt);
private:

	//variables
	bool bActive = false;
	UPROPERTY()
	TArray<TScriptInterface<IEvent>>	eventStack;
	UPROPERTY()
	TSet<UObject*>						startedEvents;
	UPROPERTY()
	TScriptInterface<IEvent>			currentEvent = nullptr;
	//functions
	void UpdateEvents();

};
