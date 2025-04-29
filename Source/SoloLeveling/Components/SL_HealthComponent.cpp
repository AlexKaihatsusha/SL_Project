#include "SL_HealthComponent.h"

//DEFINE_LOG_CATEGORY(SL_HealthComponent);
USL_HealthComponent::USL_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	//CurrentHealth = MaxHealth;
}

void USL_HealthComponent::AddHealth(float HealthAmount)
{
	float MaxHealth = 10;
	if (IsOwnerDead())
		return;
	//add health
	float CurrentHealth = 0.f;
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthAmount, 0.f, MaxHealth);

	if(CurrentHealth <=0.f)
	{
		Death();
	}
}

void USL_HealthComponent::TakeDamage(float DamageAmount)
{
	float MaxHealth = 10;
	//return if owner is dead;
	if (IsOwnerDead())
		return;
	//take damage
	float CurrentHealth = 0.f;
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);

	//if after taking damage owner is dead, then call delegate
	if(IsOwnerDead())
		Death();
	
}

void USL_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USL_HealthComponent::Death()
{
	//OnDeath.Broadcast();
}

bool USL_HealthComponent::IsOwnerDead()
{
	float CurrentHealth = 0.f;
	if (CurrentHealth <= 0.f)
	{
		return true;
	}
	else if (CurrentHealth >= 0.f)
	{
		return false;
	}
	return false;
}
