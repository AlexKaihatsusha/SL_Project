#include "GameFramework/Actor.h"
#include "../ActionManager/GameEventBehaviour.h"


DEFINE_LOG_CATEGORY(UGameEventBehaviourLog)

UGameEventBehaviour::UGameEventBehaviour()
{
	//no need to tick, since we already have our own OnUpdate which called from EventHandler
	bTickEnabled = false;
}

UWorld* UGameEventBehaviour::GetWorld() const
{
	if (WorldRef)
	{
		return WorldRef;
	}
	//Return null if the called from the CDO, or if the outer is being destroyed
	if (!HasAnyFlags(RF_ClassDefaultObject) && !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		//Try to get the world from the owning actor if we have one
		AActor* Outer = GetTypedOuter<AActor>();
		if (Outer != nullptr)
		{
			return Outer->GetWorld();
		}
	}
	//Else return null - the latent action will fail to initialize
	return nullptr;
}


void UGameEventBehaviour::Init(UWorld* InWorld)
{
	if(InWorld)
	{
		WorldRef = InWorld;
		UE_LOG(UGameEventBehaviourLog, Log, TEXT("Init World Success. Event: %s"), *GetName())

	}
	else
	{
		UE_LOG(UGameEventBehaviourLog, Error, TEXT("Init world ref is nullptr. Event: %s"), *GetName())
	}
}

void UGameEventBehaviour::Tick(float DeltaTime)
{
	//we do not execute the tick, since we just use its own onUpdate, which called from EventHandler
}

TStatId UGameEventBehaviour::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGameEventBehaviour, STATGROUP_Tickables);
}

void UGameEventBehaviour::OnBegin_Implementation(bool bFirstTime)
{
}

void UGameEventBehaviour::OnUpdate_Implementation()
{
	UE_LOG(UGameEventBehaviourLog, Log, TEXT("UGameEventBehaviour OnUpdate_Implementation() call "));
}

void UGameEventBehaviour::OnEnd_Implementation()
{
}

bool UGameEventBehaviour::IsDone_Implementation()
{
	return true;
}
