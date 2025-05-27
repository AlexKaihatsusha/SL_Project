// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/UObject/Object.h"
#include "../Public/Tickable.h"
#include "../ActionManager/Events/Base/Event.h"
#include "../ActionManager/Events/GameEvent.h"
#include "EventHandlerSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(UEventHandlerLog, Log, All)

UCLASS()
class UEventHandlerSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	// base
public:
	UEventHandlerSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}
	//---------------------------------------------------------

	// To push through Blueprint, since only GameEventBehaviour can be blueprintable and used there
	UFUNCTION(BlueprintCallable, Category = "Event Handler")
	void PushEventByClass(TSubclassOf<UGameEvent> EventClass);
	UFUNCTION(BlueprintCallable, Category = "Event Handler")
	void PushParallelEventByClass(TSubclassOf<UGameEvent> EventClass);

private:
	void PushEvent(const TScriptInterface<IEvent>& evt);
	void PushParallelEvent(const TScriptInterface<IEvent>& evt);
	// variables

	// TScriptInterface is a template that wraps two key components:
	// A UObject* pointer to the object that implements the interface.
	// A pointer to the actual interface(IEvent*).
	// main events
	UPROPERTY()
	TArray<TScriptInterface<IEvent>> mainEventsInterfaceStack;
	UPROPERTY()
	TSet<UObject*> startedEvents;
	UPROPERTY()
	TScriptInterface<IEvent> currentEvent{ nullptr };

	// parallel events
	UPROPERTY()
	TArray<TScriptInterface<IEvent>> parallelEvents{ nullptr };
	UPROPERTY()
	TSet<UObject*> startedParallelEvents;

	// functions
	void UpdateEvents();
	void UpdateParallelEvents();

	// debug functions
	virtual void DrawDebug();
};
