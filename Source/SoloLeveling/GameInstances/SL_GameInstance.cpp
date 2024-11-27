// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameInstances/SL_GameInstance.h"

DEFINE_LOG_CATEGORY(USL_GameInstanceLog)
void USL_GameInstance::Init()
{
	Super::Init();
	EventHandler = NewObject<UEventHandler>(this);
	EventHandler->AddToRoot();//prevent garbage collection
	EventHandler->SetActive(true);
	UE_LOG(USL_GameInstanceLog, Log, TEXT("Event Handler created in Game Instance"));
}

void USL_GameInstance::Shutdown()
{
	Super::Shutdown();
	if (EventHandler && EventHandler->IsRooted())
	{
		EventHandler->RemoveFromRoot();
		UE_LOG(USL_GameInstanceLog, Log, TEXT("Event Handler removed from root and cleaned up."));
	}

	EventHandler = nullptr;
}
