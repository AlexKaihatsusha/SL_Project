
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ToolBox/PooledActor.h"
#include "SL_Shard.generated.h"

UCLASS(Abstract)
class ASL_Shard : public APooledActor
{
	GENERATED_BODY()
public:
	ASL_Shard();
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh = nullptr;

	//Getters
	UFUNCTION(BlueprintCallable, Category="Shard")
	float GeVelocity();
	UFUNCTION(BlueprintCallable, Category="Shard")
	void SetVelocity(float Value);
	virtual void OnSetInUse() override;
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
private:
	float Velocity = 0.f;
};
