// Fill out your copyright notice in the Description page of Project Settings.
#include "../Actors/SL_HealthGrenade.h"
#include "../Actors/SL_HealthShard.h"
#include "Kismet/GameplayStatics.h"
#include "../ToolBox/ActorPool.h"
#include "../SoloLevelingCharacter.h"
// Sets default values
ASL_HealthGrenade::ASL_HealthGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->OnComponentHit.AddDynamic(this, &ASL_HealthGrenade::OnComponentHit);
}

// Called when the game starts or when spawned
void ASL_HealthGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASL_HealthGrenade::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor && OtherActor->ActorHasTag("Ground"))
	{
		//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 20.f, 12, FColor::Magenta,false, 2.f);
		GetWorldTimerManager().SetTimer(ActivationHandle, this, &ASL_HealthGrenade::ActivateGrenade, ActivationDelay, false);
	}
}

// Called every frame
void ASL_HealthGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASL_HealthGrenade::UseGrenage()
{
	FVector Direction = GetActorForwardVector()*1000.f;
	Mesh->AddImpulse(Direction, NAME_None, true);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+Direction, FColor::Blue, false, 4.f, 0,2.0f);
	
}

void ASL_HealthGrenade::ActivateGrenade()
{
	FVector Origin = GetActorLocation();
	ASoloLevelingCharacter* Character = Cast<ASoloLevelingCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	UActorPool* ActorPoolRef = Character->FindComponentByClass<UActorPool>();
	if (ActorPoolRef == nullptr)
	{
		
		return;
	}
	for(int32 i = 0; i<NumOfShards; ++i)
	{
		
		ASL_HealthShard* SpawnedShard = Cast<ASL_HealthShard>
			(
			ActorPoolRef->SpawnActorFromPool(FTransform(FRotator::ZeroRotator, Origin, FVector(0.1f,0.1f, 0.1f)))
			);
		if(SpawnedShard)
		{
			//UE_LOG(LogTemp, Warning, TEXT("shard is spawned "));

			float RandomHealth = FMath::RandRange(MinHealth, MaxHealth);
			float RandomSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
			SpawnedShard->SetHealthAmount(RandomHealth);
			SpawnedShard->SetVelocity(RandomSpeed);

			FVector RandomDirection = FMath::VRand();
			RandomDirection.Z = FMath::Abs(RandomDirection.Z);
			FVector Impulse = RandomDirection*RandomSpeed;
			SpawnedShard->Mesh->AddImpulse(Impulse, NAME_None, true);
			//DrawDebugLine(GetWorld(), Origin, Origin + Impulse, FColor::Green, false, 2.0f, 0, 1.0f);

		}
	}
	Destroy();
}

