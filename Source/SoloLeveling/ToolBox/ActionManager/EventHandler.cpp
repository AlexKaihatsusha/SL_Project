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
	return true;
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

void UEventHandler::PushEvent(TScriptInterface<IEvent> evt)
{
	if (evt != nullptr)
	{
		//already on Stack?
		eventStack.RemoveAll([evt](TScriptInterface<IEvent> e)
			{
				return e == evt;
			});
		
		//insert event
		eventStack.Insert(evt, 0);
		
		//reset current event?
		if (currentEvent != nullptr && currentEvent != evt)
		{
			currentEvent = nullptr;
		}

	}
}

void UEventHandler::UpdateEvents()
{
	if (eventStack.Num() == 0)
	{
		return;
	}

	//pick a new current event?
	if (currentEvent == nullptr)
	{
		//set current event
		currentEvent = eventStack[0];
		bool bFirstTime = !startedEvents.Contains(currentEvent.GetObject());
		currentEvent->Execute_OnBegin(currentEvent.GetObject());
		startedEvents.Add(currentEvent.GetObject());

		//did something affect the stack in the OnBegin()?
		if (!eventStack.IsEmpty())
		{
			if (eventStack.Num() > 0 && currentEvent != eventStack[0])
			{
				currentEvent = nullptr;
				UpdateEvents();
			}
		}

	}
	if (currentEvent != nullptr)
	{
		currentEvent->Execute_OnUpdate(currentEvent.GetObject());
		if (eventStack.Num() > 0 && currentEvent == eventStack[0])
		{
			if (currentEvent->IsDone())
			{
				eventStack.RemoveAt(0);
				currentEvent->Execute_OnEnd(currentEvent.GetObject());
				startedEvents.Remove(currentEvent.GetObject());
				currentEvent = nullptr;
			}
		}
	}
}
