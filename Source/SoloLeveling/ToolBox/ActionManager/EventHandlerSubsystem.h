// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/UObject/Object.h"
#include "../Public/Tickable.h"
#include "../ActionManager/Events/Base/Event.h"
#include "../ActionManager/Events/GameEvent.h"
#include "EventHandlerSubsystem.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(UEventHandlerLog, Log, All)

UCLASS()
class  UEventHandlerSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
//base
public:
	UEventHandlerSubsystem();

	void Tick(float DeltaTime) override;

	virtual void Deinitialize() override;
	//required functions implementation for FTickableGameObject
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	//---------------------------------------------------------
	


	//To push through Blueprint, since only GameEventBehaviour can be blueprintable and used there 
	UFUNCTION(BlueprintCallable, Category = "Event Handler")
	void PushEventByClass(TSubclassOf<UGameEvent> EventClass);
	UFUNCTION(BlueprintCallable, Category = "Event Handler")
	void PushParallelEventByClass(TSubclassOf<UGameEvent> EventClass);
	
private:
	void PushEvent(const TScriptInterface<IEvent>& evt);
	void PushParallelEvent(const TScriptInterface<IEvent>& evt);
	//variables
	
	//TScriptInterface is a template that wraps two key components:
	//A UObject* pointer to the object that implements the interface.
	//A pointer to the actual interface(IEvent*).
	//main events
	UPROPERTY()
	TArray<TScriptInterface<IEvent>>		mainEventsInterfaceStack;
	UPROPERTY()
	TSet<UObject*>							startedEvents;
	UPROPERTY()
	TScriptInterface<IEvent>				currentEvent{nullptr};



	//parallel events
	UPROPERTY()
	TArray<TScriptInterface<IEvent>>				parallelEvents{ nullptr };
	UPROPERTY()
	TSet<UObject*>									startedParallelEvents;
	
	//functions
	void UpdateEvents();
	void UpdateParallelEvents();


	//debug functions
	virtual void DrawDebug();
};
