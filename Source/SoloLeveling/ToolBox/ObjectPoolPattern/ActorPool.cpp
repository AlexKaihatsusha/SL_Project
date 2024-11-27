// Fill out your copyright notice in the Description page of Project Settings.
#include "../ObjectPoolPattern/ActorPool.h"


DEFINE_LOG_CATEGORY(UActorPoolLog);

UActorPool::UActorPool()
{

	PrimaryComponentTick.bCanEverTick = true;

}

APooledActor* UActorPool::FindFirstAvailableActor()
{
	if (ObjectPool.IsEmpty())
	{
		return nullptr;
	}
	APooledActor* pooledActor = nullptr;
	for (int i = 0; i < ObjectPool.Num(); ++i)
	{
		pooledActor = ObjectPool[i];
		
		if (pooledActor && pooledActor->GetIsInUse() == false)
		{
			UE_LOG(UActorPoolLog, Warning, TEXT("AvailableActor is found"), PoolSize);
			return pooledActor;
		}

	}
	UE_LOG(UActorPoolLog, Warning, TEXT("Pool is empty"), PoolSize);

	return nullptr;
}

APooledActor* UActorPool::SpawnActorFromPool(FTransform transform)
{
	APooledActor* actor = FindFirstAvailableActor();
	if (actor == nullptr)
	{
		return nullptr;
	}

	actor->SetActorTransform(transform, false, nullptr, ETeleportType::ResetPhysics);
	actor->SetInUse(true);
	return actor;
}


void UActorPool::BeginPlay()
{
	Super::BeginPlay();

	//initialize pool
	InitializePool();
}

void UActorPool::InitializePool()
{
	//get world
	UWorld* World = GetWorld();

	if (World == nullptr)
		return;

	//reserve the memory for the objects in array(allocate memory for pool)
	ObjectPool.Reserve(PoolSize);
	UE_LOG(UActorPoolLog, Log, TEXT("Pool size - [%i]"), PoolSize);
	UE_LOG(UActorPoolLog, Log, TEXT("Allocated memory - [%zu] bytes"), ObjectPool.GetAllocatedSize());

	for (int i = 0; i < PoolSize; i++)
	{

		//Spawn pool actor
		APooledActor* SpawnedPoolActor = World->SpawnActor<APooledActor>(PoolActorClass, FVector::ZeroVector, FRotator::ZeroRotator);

		//double check 
		if (SpawnedPoolActor != nullptr)
		{
			ObjectPool.AddUnique(SpawnedPoolActor);
			SpawnedPoolActor->SetInUse(false);
		}
	}
	UE_LOG(UActorPoolLog, Log, TEXT("Object Pool Initialized"));

}


void UActorPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


