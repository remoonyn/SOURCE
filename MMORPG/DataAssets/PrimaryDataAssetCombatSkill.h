#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimMontage.h"
#include "Enumerations/MainEnumerations.h"
#include "PrimaryDataAssetCombatSkill.generated.h"

UCLASS(BlueprintType, EditInlineNew) class MMORPG_API UPrimaryDataAssetCombatSkill : public UPrimaryDataAsset
{
   GENERATED_BODY()

public:
   UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Skill_Index;
   UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Skill_Name;
   UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Skill_Description;
   UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UTexture2D> Skill_Icon = nullptr;
   UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UAnimMontage> Skill_Montage = nullptr;


};
