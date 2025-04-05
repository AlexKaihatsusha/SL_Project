// Fill out your copyright notice in the Description page of Project Settings.


#include "../ActionManager/EventHandler.h"
#include "Kismet/GameplayStatics.h"

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

DEFINE_LOG_CATEGORY(UEventHandlerLog)

UEventHandler::UEventHandler()
{
	UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is started"))
}
void UEventHandler::Tick(float DeltaTime)
{
	//UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is running"))
	UpdateEvents();
	DrawDebug();
}
bool UEventHandler::IsTickable() const
{
	return bActive;
}
bool UEventHandler::IsTickableInEditor() const
{
	return false;
}
bool UEventHandler::IsTickableWhenPaused() const
{
	return false;
}
TStatId UEventHandler::GetStatId() const
{
	return TStatId();
}
UWorld* UEventHandler::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UEventHandler::SetActive(bool bIsActive)
{
	bActive = bIsActive;
	UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler %s"), bIsActive ? TEXT("Activated") : TEXT("Deactivated"));
}

bool UEventHandler::IsActive() const
{
	return bActive;
}

void UEventHandler::PushEventByClass(TSubclassOf<USL_GameEventBehaviour> EventClass)
{
	if (EventClass)
	{
		UE_LOG(UEventHandlerLog, Log, TEXT("PushEventByClass call, with value"));

		//dynamically create an instance of the class
		USL_GameEventBehaviour* NewEvent = NewObject<USL_GameEventBehaviour>(this, EventClass);
		if (NewEvent)
		{
			UE_LOG(UEventHandlerLog, Log, TEXT("Created Event UGameEventBehaviour"));
			//Set current world for the event
			NewEvent->SetCurrentWorld(GetWorld());
			//wrap to TScriptInterface
			TScriptInterface<IEvent> ScriptEvent;
			ScriptEvent.SetObject(NewEvent);
			ScriptEvent.SetInterface(Cast<IEvent>(NewEvent));
			PushEvent(ScriptEvent);
			UE_LOG(UEventHandlerLog, Log, TEXT("Event Pushed to Handler"));
		}
		else
		{
			UE_LOG(UEventHandlerLog, Error, TEXT("Failed to create event of class"));
		}
	}
}

void UEventHandler::PushEvent(const TScriptInterface<IEvent>& evt)
{

	if (evt)
	{
		//already on Stack?
		eventStack.RemoveAll([evt](TScriptInterface<IEvent> e)
			{
				return e == evt;
			});

		//insert event
		eventStack.Insert(evt, 0);

		//reset current event?
		if (currentEvent && currentEvent != evt)
		{
			currentEvent = nullptr;
		}
		UE_LOG(UEventHandlerLog, Log, TEXT("PushEvent call"));
	}
}

void UEventHandler::UpdateEvents()
{
	if (eventStack.Num() == 0)
	{
		return;
	}

	//pick a new current event?
	if (!currentEvent || !currentEvent.GetObject())
	{
		//set current event
		currentEvent = eventStack[0];
		if (!currentEvent)
		{
			UE_LOG(UEventHandlerLog, Error, TEXT("Failed to set currentEvent. Invalid event in stack."));
			return;
		}
		bool bFirstTime = !startedEvents.Contains(currentEvent.GetObject());
		currentEvent->Execute_OnBegin(currentEvent.GetObject(), bFirstTime);
		startedEvents.Add(currentEvent.GetObject());
		UE_LOG(UEventHandlerLog, Log, TEXT("Set new event"));

		//did something affect the stack in the OnBegin()?
		if (!eventStack.IsEmpty())
		{
			if (eventStack.Num() > 0 && currentEvent != eventStack[0])
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
		if (eventStack.Num() > 0 && currentEvent == eventStack[0])
		{
			if (currentEvent->Execute_IsDone(currentEvent.GetObject()))
			{
				UE_LOG(UEventHandlerLog, Log, TEXT("Event is done"));
				eventStack.RemoveAt(0);
				currentEvent->Execute_OnEnd(currentEvent.GetObject());
				startedEvents.Remove(currentEvent.GetObject());
				currentEvent = nullptr;
			}
		}
	}
}

void UEventHandler::DrawDebug()
{
	if (CVarDebugCurrentEvent->GetBool() )
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
			DrawDebugString(GetWorld(), Offset, "Event: event is nullptr " , ControlledPawn, FColor::Red, 0.0f);
		}
	}
	if (CVarDebugEventStack->GetBool())
	{
		FVector Offset(0, -25.0f, 110.0f);
		APawn* ControlledPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		FVector StartLocation = ControlledPawn->GetActorLocation() + Offset;
		for (auto evt : eventStack)
		{
			if (evt != currentEvent && currentEvent)
			{
				FString EventNameString = evt.GetObject()->GetName();
				DrawDebugString(GetWorld(), Offset, "Event: " + EventNameString, ControlledPawn, FColor::Cyan, 0.0f);	
			}
		}
		
	}
}
