
#include "SL_HealthShard.h"
#include "../Components/SL_HealthComponent.h"
DEFINE_LOG_CATEGORY(SL_HealthShard)
ASL_HealthShard::ASL_HealthShard() : Super::ASL_Shard()
{
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASL_HealthShard::OnComponentBeginOverlap);
}

void ASL_HealthShard::SetHealthAmount(float Value)
{
	HealthAmount = Value;
}

float ASL_HealthShard::GetHealthAmount()
{
	return HealthAmount;
}

void ASL_HealthShard::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//nothing for now
}

void ASL_HealthShard::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		USL_HealthComponent* HealthComponent = OtherActor->FindComponentByClass<USL_HealthComponent>();
		if (HealthComponent)
		{
			UE_LOG(SL_HealthShard, Log, TEXT("Shard overlap with %s "), *OtherActor->GetName());
			HealthComponent->AddHealth(HealthAmount);
			ReturnToPool();
		}
	}

}

