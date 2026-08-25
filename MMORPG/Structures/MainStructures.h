#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "StructUtils/InstancedStruct.h"
#include "Enumerations/MainEnumerations.h"
#include "Enumerations/AttributeType.h"
#include "MainStructures.generated.h"
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Container Item Attribute
USTRUCT(BlueprintType) struct FS_Item_Attribute
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute") E_Attribute_Type AttributeType = E_Attribute_Type::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute") E_Attribute_Equip_Type AttributeEquipType = E_Attribute_Equip_Type::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute") float Value = 0.0f;
};

// Container Item
USTRUCT(BlueprintType) struct FS_Item_Container
{
    GENERATED_BODY()   

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Index = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Quantity = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Stacksize = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Experience = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Level = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") EGradeType Grade = EGradeType::Common;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") TArray<FS_Item_Attribute> Attributes;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") bool Blocked = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") bool Crafted = false;
};

// Items Quantity
USTRUCT(BlueprintType) struct FS_Item_Quantity
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Index = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Quantity = 0;
};

// Required Item
USTRUCT(BlueprintType) struct FST_Item_Required
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Index = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Quantity = 0;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
// General Profession Points
USTRUCT(BlueprintType) struct FS_Profession_Points
{
   GENERATED_BODY()

public:
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Prof_Point_Level = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Prof_Points_Exp_Curr = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Prof_Points_Exp_Nedeed = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Prof_Points_Left = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession") int32 Prof_Points_All = 0;
};

// Recipe Levels
USTRUCT(BlueprintType) struct FS_Recipe_Effect
{
   GENERATED_BODY()

public:
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Required_Crafts = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") E_Recipe_Effect Effect_Type = E_Recipe_Effect::None;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") float Effect_Value = 0;
};


// Recipe
USTRUCT(BlueprintType) struct FST_Item_Recipe : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Index_Item = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Quantity = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") int32 Experience = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") float Time = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") E_Profession_Type Recipe_Type = E_Profession_Type::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") TArray<FS_Recipe_Effect> Recipe_Effects;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe") TArray<FST_Item_Required> Required_Items;
};

// None Playable Character
USTRUCT(BlueprintType) struct FST_NPC : public FTableRowBase
{
    GENERATED_BODY()

public:
    // Имя НПС
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") FText Name_NPC;
    // Приветственные фразы, которые НПС произносит при взаимодействии
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") TArray<FName> Lines_Welcome;
    // Обычные стартовые фразы для обычных диалогов
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") TArray<FName> Lines_Common;
    // Стартовые фразы для квестов
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") TArray<FName> Lines_Quests_Available;
    // Стартовые фразы для активных квестов
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") TArray<FName> Lines_Quests_Active;
    // Стартовые фразы для завершения квестов
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") TArray<FName> Lines_Quests_Complete;
    // Фраза для торговли с НПС
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") FName Line_Trade;
    // Фраза для завершения диалога и ухода
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC") FName Line_Leave;
};

// Структура для таблицы реплик
USTRUCT(BlueprintType) struct FST_Line : public FTableRowBase
{
   GENERATED_BODY()

public:
   // Имя из таблицы для следующей реплики 
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FName Next_Line;  
   // Определение того кто говорит: Индекс 0 - игрок, остальные - НПС
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FName Name_Speaker;  
   // Индекс 0 - отсутствие квестов, остальное это имена из таблицы квестов
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FName Name_Quest;
   // Ветвление диалога через варианты ответа, пишем сюда имена из таблицы
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") TArray<FName> Reply_Player; 
   // Короткая смысловая реплика диалога для игрока, для реплик НПС - пустая
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FText Line_Button;
   // Текст диалога
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FText Line_Dialog; 
   // Для удобства дальнейшего заполнения таблицы НПС, чтобы понимать какие фразы являются стартовыми для диалогов
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") bool Start; 
   // Завершает ли текущая реплика диалог? Ставим обязательно.
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") bool Finish; 
   // Тип строки
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") E_Line_Type Line_Type = E_Line_Type::None; 
   // Тип диалог
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") E_Dialog_Type Dialog_Type = E_Dialog_Type::None; 
   // Озвучка диалога
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") TSoftObjectPtr<USoundBase> Audio_Dialogue;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Структура случайного дропа без учета грейда или уровня предмета
USTRUCT(BlueprintType) struct FST_Drop_Harvest_Item
{
   GENERATED_BODY()

public:
   // Имя из таблицы для следующей реплики 
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Index_Item;
   // Минимальное количество возможных предметов
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Quantity_Min;
   // Максимальное количество возможных предметов
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Quantity_Max;
   // Минимальный опыт за получение предмет, для добывающих профессий
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Exp_Min;
   // Максимальный опыт за получение предмета, для добывающих профессий
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Exp_Max;
   // Шанс выпадения предмета, от 0.0(1) до 1.0. Еденица для предметов со 100% шансом выпадения.
   UPROPERTY(EditAnywhere, BlueprintReadWrite) float Chance_Drop;

};

// Для таблицы сбора ресурсов
USTRUCT(BlueprintType) struct FST_Drop_Harvest : public FTableRowBase
{
   GENERATED_BODY()

public:
   // Опыт в уровень за итерацию
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Prof_Lvl_Exp;
   // Опыт в навыки за итерацию
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Prof_Points_Exp;
   // Массив возможных получаемых предметов, минимальное и максимальное количество и шансы
   UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FST_Drop_Harvest_Item> Harvest_Drops;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Структура случайного дропа без учета грейда или уровня предмета для мобов
USTRUCT(BlueprintType) struct FST_Drop_Enemy_Item
{
   GENERATED_BODY()

public:
   // Имя из таблицы для следующей реплики 
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Index_Item;
   // Минимальное количество возможных предметов
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Quantity_Min;
   // Максимальное количество возможных предметов
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Quantity_Max;
   // Шанс выпадения предмета, от 0.0(1) до 1.0. Еденица для предметов со 100% шансом выпадения.
   UPROPERTY(EditAnywhere, BlueprintReadWrite) float Chance_Drop;
};

// Для таблицы дропа с мобов
USTRUCT(BlueprintType) struct FST_Drop_Enemy : public FTableRowBase
{
   GENERATED_BODY()

public:
   // Опыт в уровень за убийство
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Enemy_Exp;
   // Карма за убийство
   UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Enemy_Carma;
   // Массив возможных получаемых предметов, минимальное и максимальное количество и шансы
   UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FST_Drop_Enemy_Item> Enemy_Drops;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
// TESTContainer Item
USTRUCT(BlueprintType) struct FS_TEST_Item_Container
{
   GENERATED_BODY()   

public:
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Index = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Quantity = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Stacksize = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Experience = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") int32 Level = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") EGradeType Grade = EGradeType::Common;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") TArray<FS_Item_Attribute> Attributes;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") bool Blocked = false;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") bool Crafted = false;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") FInstancedStruct ItemData;

};
//----------------------------------------------------------------------------------------------------------------------------------------------------
