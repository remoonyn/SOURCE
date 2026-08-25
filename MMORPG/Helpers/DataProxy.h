#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enumerations/MainEnumerations.h"
#include "Structures/MainStructures.h"
#include "DataProxy.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MMORPG_API UEquipItemDataProxy : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool Equip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EEquipmentType Equipment_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FS_Item_Attribute> Attributes;
};