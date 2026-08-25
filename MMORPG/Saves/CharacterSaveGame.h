#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Components/Profession.h"
#include "Enumerations/MainEnumerations.h"
#include "Components/Quest.h"
#include "CharacterSaveGame.generated.h"

// Структура для сохранения крафтовых слотов
USTRUCT(BlueprintType) struct FS_Save_Profession_Craft_Slot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Index_Recipe = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") bool Slot_Craft_Take = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") bool Slot_Craft_Ready = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") float Left_Duration = 0.0;
};

// Общая структура для сохранения информации о конкретной профессии
USTRUCT(BlueprintType) struct FS_Save_Profession
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") E_Profession_Type Profession_Type = E_Profession_Type::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Level_Profession = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Current_Experience = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Needed_Experience = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TArray<FS_Learning_Recipe> Learning_Recipes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TArray<FS_Learning_Profession_Skill> Profession_Skills;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TArray<FS_Save_Profession_Craft_Slot> Crafting_Slots;
};

// Структура эффектов зелий
USTRUCT(BlueprintType) struct FS_Save_Consumable_Effect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Consume_Index_Item = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Consume_Level_Effect = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") float Consume_Left_Duration = 0.0;
};

UCLASS()
class MMORPG_API UCharacterSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// Сохранение успешно?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save") bool Success_Save = false;
	// Мертв ли персонаж?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character") bool Dead = false;
	// Время сохранения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save") FDateTime Save_Time;
	// Очки навыков профессии
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") FS_Profession_Points Profession_Points;
	// Массив всех профессии
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") TArray<FS_Save_Profession> Professions;
	// Массив всех активных зелий
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion") TArray<FS_Save_Consumable_Effect> Potions;
	// Массив всех активных блюд
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food") TArray<FS_Save_Consumable_Effect> Foods;
	// Параметры
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters") TMap<E_Parameter_Type, float> Parameters;
	// Активные квесты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FName> Quest_Active;
	// Завершенные квесты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FName> Quest_Completed;
	// Завершенные ежедневные квесты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FName> Quest_Completed_Daily;
	// Завершенные еженедельные квесты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FName> Quest_Completed_Weakly;
	// Прогресс в квестах
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FS_Quest_Active_Progress> Quest_Active_Progress;
};
