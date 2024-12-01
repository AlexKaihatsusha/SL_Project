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
	UEventHandler();
	
	void Tick(float DeltaTime) override;
	//required functions implementation for FTickableGameObject
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	UWorld* GetWorld() const override;
	//---------------------------------------------------------
	//EventHandler logic is below
	UFUNCTION(BlueprintCallable, Category = "Evenet Handler")
	//To enable or disable tick for Event Handler
	void SetActive(bool bIsActive);
	//getter
	UFUNCTION(BlueprintCallable, Category = "Evenet Handler")
	bool IsActive() const;


	//To push through Blueprint, since only GameEventBehaviour can be blueprintable and used there 
	UFUNCTION(BlueprintCallable, Category = "Event Handler")
	void PushEventByClass(TSubclassOf<UGameEventBehaviour> EventClass);
	
	void PushEvent(const TScriptInterface<IEvent>& evt);
private:

	//variables
	bool bActive = false;
	//TScriptInterface is a template that wraps two key components:
	//A UObject* pointer to the object that implements the interface.
	//A pointer to the actual interface(IEvent*).
	UPROPERTY()
	TArray<TScriptInterface<IEvent>>	eventStack;
	UPROPERTY()
	TSet<UObject*>						startedEvents;
	UPROPERTY()
	TScriptInterface<IEvent>			currentEvent = nullptr;
	//functions
	void UpdateEvents();


	//debug functions
	virtual void DrawDebug();
};
