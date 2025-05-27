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
float UDamageSystem::Heal_Implementation(float HealAmount)
{
	if (IsDead)
		return CurrentHealth;
	// add health
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.f, MaxHealth);

	if (CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
	return CurrentHealth;
}

bool UDamageSystem::TakeDamage_Implementation(FDamageData DamageData)
{
	//----DEBUG-----
	UScriptStruct* DataToText = DamageData.StaticStruct();
	FString		   tempString = TEXT("");
	DataToText->ExportText(tempString, &DamageData, nullptr, this,
		(PPF_ExportsNotFullyQualified | PPF_Copy | PPF_Delimited | PPF_IncludeTransient), nullptr);
	UE_LOG(UDamageSystemLog, Log, TEXT("[Receiver: %s;\tDamageData: %s;\tCurrentHealth: %f;\tDeath: %s;]"),
		*GetOwner()->GetName(), *FString(tempString), CurrentHealth, IsDead ? TEXT("true") : TEXT("false"));

	return IsDamageReceived;
}

float UDamageSystem::GetMaxHealth_Implementation()
{
	return MaxHealth;
}

float UDamageSystem::GetCurrentHealth_Implementation()
{
	return CurrentHealth;
}
bool UDamageSystem::IsOwnerDead() const
{
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

void UDamageSystem::ApplyDamage(float DamageAmount)
{
	// take damage
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	OnDamageReceived.Broadcast(CurrentHealth);
	//---------------
	if (IsOwnerDead())
	{
		IsDead = true;
		OnDeath.Broadcast();
	}
}

void UDamageSystem::SetIsDead(bool Dead)
{
	IsDead = Dead;
}
