#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MMORPG/Enumerations/MainEnumerations.h"
#include "MMORPG/Structures/MainStructures.h"
#include "AbilitySystemComponent.h"
#include "Profession.generated.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
// Learning Recipe
USTRUCT(BlueprintType) struct FS_Learning_Recipe
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Index_Recipe = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Current_Crafts = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") bool Learned = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") bool Mastered = false;

};
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Crafting Slot
USTRUCT(BlueprintType) struct FS_Craft_Slot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Index_Recipe = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") bool Slot_Craft_Take = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") bool Slot_Craft_Ready = 0;

	// Есть какие-то тонкости с репликацией handle effect, но я пока не разобрался. Поэтому NotReplicated.
	UPROPERTY(NotReplicated, BlueprintReadWrite, Category = "Profession") FActiveGameplayEffectHandle CraftingEffectHandle;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Profession Skill
USTRUCT(BlueprintType) struct FS_Learning_Profession_Skill
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Index_Prof_Skill = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Level_Prof_Skill = 0;

};
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Profession Skill
USTRUCT(BlueprintType) struct FST_Profession_Skill : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") FText Skill_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TMap<int32, int32> Required_Prof_Points;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TSubclassOf<UGameplayEffect> EffectClass;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup=(Profession), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType) 
class MMORPG_API UProfession : public UActorComponent
{
	GENERATED_BODY()

public:	

	UProfession();

	UFUNCTION(BlueprintCallable, Category = "Crafting") bool Check_Empty_Crafting_Slot(int32& index_empty_slot);
	UFUNCTION(BlueprintCallable, Category = "Crafting") bool Check_Learning_Recipe(int32 index_recipe);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") E_Profession_Type Profession = E_Profession_Type::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Level_Profession = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Current_Experience = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Needed_Experience = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TArray<FS_Learning_Recipe> Learning_Recipes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TArray<FS_Craft_Slot> Crafting_Slots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TArray<FS_Learning_Profession_Skill> Profession_Skills;


};
//----------------------------------------------------------------------------------------------------------------------------------------------------
