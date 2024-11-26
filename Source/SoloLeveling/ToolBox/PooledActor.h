
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"




UCLASS()
class SOLOLEVELING_API APooledActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APooledActor();


	void SetInUse(bool isInUse);

	bool GetIsInUse() { return IsInUse; }
	virtual void OnSetInUse() {};

protected:
	virtual void BeginPlay() override;	
	void ReturnToPool();
public:	
	virtual void Tick(float DeltaTime) override;
	
private:
	
	UPROPERTY(VisibleInstanceOnly)
	bool			IsInUse = false;


	UPROPERTY(EditDefaultsOnly, Category = "Object Pool Settings")
	float			TimeToLive = 0.f;
	FTimerHandle	TimeToLiveHandler;
};
