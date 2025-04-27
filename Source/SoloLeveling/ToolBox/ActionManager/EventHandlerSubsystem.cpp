// Fill out your copyright notice in the Description page of Project Settings.


#include "../ActionManager/EventHandlerSubsystem.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(UEventHandlerLog)

//register console command for debugging
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
void UEventHandlerSubsystem::Tick(float DeltaTime)
{
	//UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is running"))
	UpdateEvents();
	DrawDebug();
}
void UEventHandlerSubsystem::Deinitialize()
{
	UE_LOG(UEventHandlerLog, Log, TEXT("UEventHandler::Deinitialize()"));

}
bool UEventHandlerSubsystem::IsTickable() const
{
	return true;
}
bool UEventHandlerSubsystem::IsTickableInEditor() const
{
	return false;
}
bool UEventHandlerSubsystem::IsTickableWhenPaused() const
{
	return false;
}
TStatId UEventHandlerSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UEventHandlerSubsystem, STATGROUP_Tickables);
}


void UEventHandlerSubsystem::PushEventByClass(TSubclassOf<USL_GameEventBehaviour> EventClass)
{
	if (!GetWorld())
		return;
	if (EventClass)
	{
		UE_LOG(UEventHandlerLog, Log, TEXT("PushEventByClass call for class %s"), *EventClass->GetName());

		USL_GameEventBehaviour* NewEvent = NewObject<USL_GameEventBehaviour>(this, EventClass);
		
		if (NewEvent)
		{
			UE_LOG(UEventHandlerLog, Log, TEXT("NewEvent as new object is created"));
			//init world ref for event
			NewEvent->Init(GetWorld());

			//wrap interface and GameEventBehaviour Object
			TScriptInterface<IEvent> event;
			event.SetObject(NewEvent);
			event.SetInterface(Cast<IEvent>(NewEvent));
			UE_LOG(UEventHandlerLog, Log, TEXT("Created a wrapper for new event"));
			//push event to the class
			PushEvent(event);
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

void UEventHandlerSubsystem::PushEvent(const TScriptInterface<IEvent>& evt)
{
	//early return of event is nullptr
	if (!evt)
	{
		return;
	}
	//already on Stack?
	if (eventInterfaceStack.Contains(evt))
	{	
		UE_LOG(UEventHandlerLog, Warning, TEXT("%s - Trying to push event that is already on stack - return from PushEvent function"), *evt.GetObject()->GetName());
		return;
	}

	//insert event
	eventInterfaceStack.Insert(evt, 0);

	//reset current event?
	if (currentEvent && currentEvent != evt)
	{
		currentEvent = nullptr;
	}
	UE_LOG(UEventHandlerLog, Log, TEXT("PushEvent call"));

}

void UEventHandlerSubsystem::UpdateEvents()
{
	//is there any events on stack
	if (eventInterfaceStack.Num() == 0)
	{
		return;
	}

	//pick a new current event?
	if (!currentEvent)
	{
		//set current event
		currentEvent = eventInterfaceStack[0];
		if (!currentEvent)
		{
			UE_LOG(UEventHandlerLog, Error, TEXT("Failed to set currentEvent. Invalid event in stack."));
			return;
		}
		bool bFirstTime = !startedEvents.Contains(currentEvent.GetObject());
		startedEvents.Add(currentEvent.GetObject());
		currentEvent->Execute_OnBegin(currentEvent.GetObject(), bFirstTime);
		

		//current event debug
		UE_LOG(UEventHandlerLog, Log, TEXT("Set new event"));
		FString currentEventText = [&]() -> FString{
				USL_GameEventBehaviour* tempRef = Cast<USL_GameEventBehaviour>(currentEvent.GetObject());
				if(tempRef)
					return tempRef->text;
				return "None";
			}();
			
		UE_LOG(UEventHandlerLog, Log, TEXT("Current event is object: %s text: %s"),*currentEvent.GetObject()->GetName(), *currentEventText);


		//did something affect the stack in the OnBegin()?
		if (!eventInterfaceStack.IsEmpty())
		{
			if (eventInterfaceStack.Num() > 0 && currentEvent != eventInterfaceStack[0])
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
		if (eventInterfaceStack.Num() > 0 && currentEvent == eventInterfaceStack[0])
		{
			if (currentEvent->Execute_IsDone(currentEvent.GetObject()))
			{
				UE_LOG(UEventHandlerLog, Log, TEXT("Event is done"));
				eventInterfaceStack.RemoveAt(0);
				currentEvent->Execute_OnEnd(currentEvent.GetObject());
				startedEvents.Remove(currentEvent.GetObject());
				currentEvent = nullptr;
			}
		}
	}
}

void UEventHandlerSubsystem::DrawDebug()
{
	if (CVarDebugCurrentEvent->GetBool())
	{
		FVector Offset(0, -25.0f, 100.0f);
		APawn* ControlledPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		FVector StartLocation = ControlledPawn->GetActorLocation() + Offset;
		if (currentEvent != nullptr)
		{
			FString EventNameString = currentEvent.GetObject()->GetName();
			DrawDebugString(GetWorld(), Offset, "Event: " + EventNameString, ControlledPawn, FColor::Cyan, 0.0f);
		}
		else
		{
			DrawDebugString(GetWorld(), Offset, "Event: event is nullptr ", ControlledPawn, FColor::Red, 0.0f);
		}
	}
	if (CVarDebugEventStack->GetBool())
	{
		FVector Offset(0, -25.0f, 110.0f);
		APawn* ControlledPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		FVector StartLocation = ControlledPawn ? ControlledPawn->GetActorLocation() + Offset : FVector::ZeroVector;
		for (auto evt : eventInterfaceStack)
		{
			if (evt != currentEvent && currentEvent)
			{
				FString EventNameString = evt.GetObject()->GetName();
				DrawDebugString(GetWorld(), Offset, "Event: " + EventNameString, ControlledPawn, FColor::Cyan, 0.0f);
			}
		}

	}
}
