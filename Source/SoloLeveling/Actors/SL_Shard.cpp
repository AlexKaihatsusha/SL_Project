#include "SL_Shard.h"
#include "Components/StaticMeshComponent.h"

ASL_Shard::ASL_Shard()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(false);

}

float ASL_Shard::GeVelocity()
{
	return Velocity;
}

void ASL_Shard::SetVelocity(float Value)
{
	Velocity = Value;
}

void ASL_Shard::OnSetInUse()
{
	if (GetIsInUse())
	{
		Mesh->SetSimulatePhysics(true);
	}
	else
	{
		Mesh->SetSimulatePhysics(false);
	}
}

void ASL_Shard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASL_Shard::BeginPlay()
{
	Super::BeginPlay();
}
