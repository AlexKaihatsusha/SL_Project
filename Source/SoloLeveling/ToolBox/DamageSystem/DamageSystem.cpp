#include "../DamageSystem/DamageSystem.h"

DEFINE_LOG_CATEGORY(UDamageSystemLog);

UDamageSystem::UDamageSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}
void UDamageSystem::BeginPlay()
{
	Super::BeginPlay();

}
float UDamageSystem::Heal(float HealAmount)
{
	if (IsDead)
		return CurrentHealth;
	//add health
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.f, MaxHealth);

	if (CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
	return CurrentHealth;
}

bool UDamageSystem::TakeDamage(FDamageData DamageData)
{
	DamageReceived = false;
	//return if owner is dead;
	if (IsDead)
		return DamageReceived;
	//take damage
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageData.Amount, 0.0f, MaxHealth);
	DamageReceived = true;
	//if after taking damage owner is dead, then call delegate
	if (IsOwnerDead())
		OnDeath.Broadcast();


	UScriptStruct* DataToText = DamageData.StaticStruct();
	FString tempString = TEXT("");
	DataToText->ExportText(tempString, &DamageData, nullptr, this, (PPF_ExportsNotFullyQualified | PPF_Copy | PPF_Delimited | PPF_IncludeTransient), nullptr);
	UE_LOG(UDamageSystemLog, Log, TEXT("[Receiver: %s;\tDamageData: %s;\tCurrentHealth: %f;\tDeath: %s;]"),*GetOwner()->GetName(), *FString(tempString), CurrentHealth, IsDead ? TEXT("true") : TEXT("false"));
	
	return DamageReceived;
}

float UDamageSystem::GetMaxHealth()
{
	return MaxHealth;
}

float UDamageSystem::GetCurrentHealth()
{
	return CurrentHealth;
}
bool UDamageSystem::IsOwnerDead()
{
	if (CurrentHealth <= 0.f)
	{
		SetIsDead(true);
		return IsDead;
	}
	else if (CurrentHealth >= 0.f)
	{
		SetIsDead(false);
		return false;
	}
	return false;
}

void UDamageSystem::SetIsDead(bool Dead)
{
	IsDead = Dead;
}



