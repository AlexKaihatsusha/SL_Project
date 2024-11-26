#include "SL_HealthComponent.h"

DEFINE_LOG_CATEGORY(SL_HealthComponent);
USL_HealthComponent::USL_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

void USL_HealthComponent::AddHealth(float HealthAmount)
{
	//return if owner is dead;
	if(HealthAmount <= 0.f || CurrentHealth <= 0.f)
	{
		return;
	}
	//add health
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthAmount, 0.f, MaxHealth);

	if(CurrentHealth <=0.f)
	{
		Death();
	}
}

void USL_HealthComponent::TakeDamage(float DamageAmount)
{
	//return if owner is dead;
	if(DamageAmount <= 0.f || CurrentHealth <= 0.f)
	{
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	if(CurrentHealth<=0.f)
	{
		Death();
	}
}

void USL_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USL_HealthComponent::Death()
{
	OnDeath.Broadcast();
}
