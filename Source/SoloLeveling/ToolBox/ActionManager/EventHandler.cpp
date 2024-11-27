// Fill out your copyright notice in the Description page of Project Settings.


#include "../ActionManager/EventHandler.h"

DEFINE_LOG_CATEGORY(UEventHandlerLog)

UEventHandler::UEventHandler()
{
	UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is started"))
}
void UEventHandler::Tick(float DeltaTime)
{
	//UE_LOG(UEventHandlerLog, Log, TEXT("Event Handler is running"))
	UpdateEvents();
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

void UEventHandler::PushEventByClass(TSubclassOf<UGameEventBehaviour> EventClass)
{
	if (EventClass)
	{
		UE_LOG(UEventHandlerLog, Log, TEXT("PushEventByClass call, with value"));

		//dynamically create an instance of the class
		UGameEventBehaviour* NewEvent = NewObject<UGameEventBehaviour>(this, EventClass);
		if(NewEvent)
		{
			UE_LOG(UEventHandlerLog, Log, TEXT("Created Event UGameEventBehaviour"));

			//wrap to ScriptInterface
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
