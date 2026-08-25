#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enumerations/MainEnumerations.h"
#include "PrimaryDataAssetItem.generated.h"

UCLASS(BlueprintType, EditInlineNew) class MMORPG_API UPrimaryDataAssetItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ItemID = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 StackSize = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Price = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float Weight = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Name;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Description;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemType ItemType = EItemType::None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EResourceType ResourceType = EResourceType::None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EWeaponType WeaponType = EWeaponType::None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EArmorType ArmorType = EArmorType::None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EJewelryType JewelryType = EJewelryType::None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EConsumableType ConsumableType = EConsumableType::None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftClassPtr<AActor> ItemClassRef = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UTexture2D> ItemIcon = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) bool Stackable = false;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) bool Tradeable = false;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) bool Improveable = false;
};
