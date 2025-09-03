#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None	 UMETA(DisplayName = "None"),
	Generic	 UMETA(DisplayName = "Generic"),
	Usable	 UMETA(DisplayName = "Usable"),
	Weapon	 UMETA(DisplayName = "Weapon"),
	Resource UMETA(DisplayName = "Resource")
};
UCLASS(BlueprintType)
class UBaseItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UBaseItemData();

	UBaseItemData(
		const FText&					   ItemName,
		const FText&					   ItemDescription,
		const EItemType					   ItemType,
		const int32&					   Quantity,
		const FString&					   AssetName,
		const TSoftObjectPtr<UTexture2D>&  IconSoftRef,
		const TSoftObjectPtr<UStaticMesh>& ItemStaticMesh)
		: ItemName(ItemName), ItemType(ItemType), Quantity(Quantity),AssetName(AssetName), IconSoftRef(IconSoftRef), ItemStaticMesh(ItemStaticMesh) 
	{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	FText ItemName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	FText ItemDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	EItemType ItemType = EItemType::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	int32 Quantity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	FString AssetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	TSoftObjectPtr<UTexture2D> IconSoftRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemData")
	TSoftObjectPtr<UStaticMesh> ItemStaticMesh;
};