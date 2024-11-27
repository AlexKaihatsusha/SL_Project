

#include "../ObjectPoolPattern/PooledActor.h"
#include "Kismet/KismetSystemLibrary.h"

APooledActor::APooledActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//set boolean on spawn
	SetInUse(false);
}

void APooledActor::SetInUse(bool isInUse)
{
	//Set actor visibility, collision, tick according whether the actor is in use or not
	IsInUse = isInUse;
	SetActorEnableCollision(IsInUse);
	SetActorHiddenInGame(!IsInUse);
	SetActorTickEnabled(IsInUse);
	OnSetInUse();
	//reset TimerHandler
	if(IsInUse == true)
		GetWorld()->GetTimerManager().SetTimer(TimeToLiveHandler, this, &APooledActor::ReturnToPool, TimeToLive);
}



void APooledActor::BeginPlay()
{
	Super::BeginPlay();
	

}

void APooledActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledActor::ReturnToPool()
{
	TimeToLiveHandler.Invalidate();
	SetInUse(false);
}

