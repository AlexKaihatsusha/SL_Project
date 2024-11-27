
#include "../ActionManager/GameEventBehaviour.h"

void UGameEventBehaviour::OnBegin_Implementation(bool bFirstTime)
{
}

void UGameEventBehaviour::OnUpdate_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("UGameEventBehaviour OnUpdate_Implementation() call "));
}

void UGameEventBehaviour::OnEnd_Implementation()
{
}

bool UGameEventBehaviour::IsDone_Implementation()
{
	return true;
}
