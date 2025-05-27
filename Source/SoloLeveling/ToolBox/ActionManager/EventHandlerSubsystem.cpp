// Fill out your copyright notice in the Description page of Project Settings.

#include "../ActionManager/EventHandlerSubsystem.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../../../../GameEngines/UnrealEngine/UE_5.5/Engine/Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/WaveformEditorStyle.h"

DEFINE_LOG_CATEGORY(UEventHandlerLog)

// register console command for debugging
static TAutoConsoleVariable<bool> CVarDebugCurrentEvent(
	TEXT("EventHandler.DebugCurrentEvent"),
	false,
	TEXT("displays the current Event - True(show), false(Hide)"),
	ECVF_Default);
static TAutoConsoleVariable<bool> CVarDebugEventStack(
	TEXT("EventHandler.DebugEventStack"),
	false,
	TEXT("displays the event stack list - True(show), false(Hide)"),
	ECVF_Default);

UEventHandlerSubsystem::UEventHandlerSubsystem()
{
	UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is started"))
	UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is running"))
}
void UEventHandlerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UEventHandlerSubsystem::Tick(float DeltaTime)
{
	// UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is running"))

	// update main events
	UpdateEvents();
	// update parallel events
	UpdateParallelEvents();
	// Draw debug data
	DrawDebug();
}
void UEventHandlerSubsystem::Deinitialize()
{
	UE_LOG(UEventHandlerLog, Log, TEXT("UEventHandler::Deinitialize()"));
}

void UEventHandlerSubsystem::PushEventByClass(TSubclassOf<UGameEvent> EventClass)
{
	if (!GetWorld())
		return;
	if (EventClass)
	{

		UGameEvent* NewEvent = NewObject<UGameEvent>(this, EventClass);
		UE_LOG(UEventHandlerLog, Log, TEXT("PushEventByClass call for event %s, Main event: %s "), *EventClass->GetName(), NewEvent->bIsMainEvent ? TEXT("true") : TEXT("false"));

		if (NewEvent)
		{
			UE_LOG(UEventHandlerLog, Log, TEXT("NewEvent as new object is created"));
			// init world ref for event
			NewEvent->Init(GetWorld());

			// wrap interface and GameEventBehaviour Object
			TScriptInterface<IEvent> event;
			event.SetObject(NewEvent);
			event.SetInterface(Cast<IEvent>(NewEvent));
			UE_LOG(UEventHandlerLog, Log, TEXT("Created a wrapper for new event"));
			// push event to the class
			if (NewEvent->bIsMainEvent)
			{
				PushEvent(event);
			}
			else
			{
				PushParallelEvent(event);
			}

			UE_LOG(UEventHandlerLog, Log, TEXT("PushEvent called"));
		}
		else
		{
			UE_LOG(UEventHandlerLog, Error, TEXT("Failed to create event of class"));
		}
	}
	else
	{
		UE_LOG(UEventHandlerLog, Error, TEXT("PushEventByClass failed"));
	}
}

void UEventHandlerSubsystem::PushParallelEventByClass(TSubclassOf<UGameEvent> EventClass)
{
	if (!GetWorld())
		return;
	if (EventClass)
	{
		UE_LOG(UEventHandlerLog, Log, TEXT("PushParallelEventByClass call for class %s"), *EventClass->GetName());
		UGameEvent* NewEvent = NewObject<UGameEvent>(this, EventClass);

		if (NewEvent && !NewEvent->bIsMainEvent)
		{
			UE_LOG(UEventHandlerLog, Log, TEXT("new parallel event as new object is created"));
			// init world ref for event
			NewEvent->Init(GetWorld());

			// wrap interface and GameEventBehaviour Object
			TScriptInterface<IEvent> event;
			event.SetObject(NewEvent);
			event.SetInterface(Cast<IEvent>(NewEvent));
			UE_LOG(UEventHandlerLog, Log, TEXT("Created a wrapper for new parallel event"));
			// push event to the class
			PushParallelEvent(event);
			UE_LOG(UEventHandlerLog, Log, TEXT("PushParallelEvent called"));
		}
		else
		{
			UE_LOG(UEventHandlerLog, Error, TEXT("Failed to create event of class"));
		}
	}
	else
	{
		UE_LOG(UEventHandlerLog, Error, TEXT("PushParallelEventByClass failed"));
	}
}

void UEventHandlerSubsystem::PushEvent(const TScriptInterface<IEvent>& evt)
{
	// early return of event is nullptr
	if (!evt)
	{
		return;
	}
	// already on Stack?
	if (mainEventsInterfaceStack.Contains(evt))
	{
		UE_LOG(UEventHandlerLog, Warning, TEXT("%s - Trying to push event that is already on stack"), *evt.GetObject()->GetName());
		return;
	}

	// insert event
	mainEventsInterfaceStack.Insert(evt, 0);

	// reset current event?
	if (currentEvent && currentEvent != evt)
	{
		currentEvent = nullptr;
	}
	UE_LOG(UEventHandlerLog, Log, TEXT("PushEvent call"));
}

void UEventHandlerSubsystem::PushParallelEvent(const TScriptInterface<IEvent>& evt)
{
	if (!evt)
	{
		return;
	}
	if (parallelEvents.Contains(evt))
	{
		UE_LOG(UEventHandlerLog, Warning, TEXT("%s - Trying to push parallel event that is already on stack"), *evt.GetObject()->GetName());
		return;
	}

	parallelEvents.Add(evt);
	// I want to start this event immediately
	evt->Execute_OnBegin(evt.GetObject(), true);
}

void UEventHandlerSubsystem::UpdateEvents()
{
	// is there any events on stack
	if (mainEventsInterfaceStack.Num() == 0)
	{
		return;
	}

	// pick a new current event?
	if (!currentEvent)
	{
		// set current event
		currentEvent = mainEventsInterfaceStack[0];
		if (!currentEvent)
		{
			UE_LOG(UEventHandlerLog, Error, TEXT("Failed to set currentEvent. Invalid event in stack."));
			return;
		}
		bool bFirstTime = !startedEvents.Contains(currentEvent.GetObject());
		startedEvents.Add(currentEvent.GetObject());
		currentEvent->Execute_OnBegin(currentEvent.GetObject(), bFirstTime);

		// current event debug
		UE_LOG(UEventHandlerLog, Log, TEXT("Set new event"));
		FString currentEventText = [&]() -> FString {
			UGameEvent* tempRef = Cast<UGameEvent>(currentEvent.GetObject());
			if (tempRef)
				return tempRef->DebugText;
			return "None";
		}();

		UE_LOG(UEventHandlerLog, Log, TEXT("Current event is object: %s text: %s"), *currentEvent.GetObject()->GetName(), *currentEventText);

		// did something affect the stack in the OnBegin()?
		if (!mainEventsInterfaceStack.IsEmpty())
		{
			if (mainEventsInterfaceStack.Num() > 0 && currentEvent != mainEventsInterfaceStack[0])
			{
				UE_LOG(UEventHandlerLog, Log, TEXT("Set new event"));

				currentEvent = nullptr;
				UpdateEvents();
			}
		}
	}
	if (currentEvent)
	{
		currentEvent->Execute_OnUpdate(currentEvent.GetObject());
		if (mainEventsInterfaceStack.Num() > 0 && currentEvent == mainEventsInterfaceStack[0])
		{
			if (currentEvent->Execute_IsDone(currentEvent.GetObject()))
			{
				UE_LOG(UEventHandlerLog, Log, TEXT("Event is done"));
				mainEventsInterfaceStack.RemoveAt(0);
				currentEvent->Execute_OnEnd(currentEvent.GetObject());
				startedEvents.Remove(currentEvent.GetObject());
				currentEvent = nullptr;
			}
		}
	}
}

void UEventHandlerSubsystem::UpdateParallelEvents()
{
	// Early return if there is no events
	if (parallelEvents.IsEmpty())
	{
		return;
	}
	// just update all parallel events, in reverse loop to avoid index shift or crash
	for (int32 e = parallelEvents.Num() - 1; e >= 0; --e)
	{

		const auto& evt = parallelEvents[e];
		// Event is nullptr?
		if (!evt)
		{
			parallelEvents.RemoveAt(e);
			continue;
		}

		evt->Execute_OnUpdate(evt.GetObject());

		if (evt->Execute_IsDone(evt.GetObject()))
		{
			// call on End
			evt->Execute_OnEnd(evt.GetObject());
			// Remove it from the array
			parallelEvents.RemoveAt(e);
		}
	}
}

void UEventHandlerSubsystem::DrawDebug()
{
	if (CVarDebugCurrentEvent->GetBool())
	{
		FVector			   Offset(0, -25.0f, 100.0f);
		APlayerController* Controller = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Controller)
		{
			FVector StartLocation = Controller->GetPawn()->GetActorLocation() + Offset;
			if (currentEvent != nullptr)
			{
				FString EventNameString = currentEvent.GetObject()->GetName();
				DrawDebugString(GetWorld(), Offset, "Event: " + EventNameString, Controller->GetParentActor(), FColor::Cyan, 0.0f);
			}
			else
			{
				DrawDebugString(GetWorld(), Offset, "Event: event is nullptr ", Controller->GetParentActor(), FColor::Red, 0.0f);
			}
		}
	}
	if (CVarDebugEventStack->GetBool())
	{
		FVector Offset(0, -25.0f, 110.0f);
		APawn*	ControlledPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (ControlledPawn)
		{
			FVector StartLocation = ControlledPawn->GetActorLocation() + Offset;
			for (auto evt : mainEventsInterfaceStack)
			{
				if (evt != currentEvent && currentEvent && evt)
				{
					FString EventNameString = evt.GetObject()->GetName();
					DrawDebugString(GetWorld(), Offset, "Event: " + EventNameString, ControlledPawn, FColor::Cyan, 0.0f);
				}
			}
		}
	}
}
