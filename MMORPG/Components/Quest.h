#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enumerations/MainEnumerations.h"
#include "Structures/MainStructures.h"
#include "Net/UnrealNetwork.h"
#include "Quest.generated.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class E_Quest_Type : uint8
{
    None        UMETA(DisplayName = "None"),
    Story       UMETA(DisplayName = "Story"),
    Side        UMETA(DisplayName = "Side"),
    Daily       UMETA(DisplayName = "Daily"),
    Weekly      UMETA(DisplayName = "Weekly")
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class E_Quest_Target_Type : uint8
{
    None        UMETA(DisplayName = "None"),
    Talk        UMETA(DisplayName = "Talk"),
    Resource    UMETA(DisplayName = "Resource"),
    Kill        UMETA(DisplayName = "Kill")
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FS_Quest_Item
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") int32 Index_Item = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") int32 Quantity = 0;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FS_Quest_Target
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FName> Names_NPC;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FS_Quest_Item> Required_Items;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TMap<FName, int32> Required_Monsters;
 
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FS_Quest_Bounty
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") int32 Gold = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") int32 Exp = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FS_Quest_Item> Bounty_Items;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FS_Quest_Kill_Progress
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FName Monster;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") int32 Current = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") int32 Needed = 0;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FS_Quest_Talk_Progress
{
   GENERATED_BODY()

public:
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FName Name_NPC;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FName Selected_Line_Branch;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") bool Complete = false;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FST_Quest : public FTableRowBase
{
    GENERATED_BODY()

public:
    // Имя квеста в таблице
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FText Quest_Title;
    // Описание квеста
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FText Quest_Description;
    // Тип квеста
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") E_Quest_Type Quest_Type = E_Quest_Type::None;
    // Тип цели квеста для разделения логики выполнения
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") E_Quest_Target_Type Quest_Target_Type = E_Quest_Target_Type::None;
    // Структура цели квеста
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FS_Quest_Target Quest_Target;
    // Структура награды квеста
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FS_Quest_Bounty Quest_Bounty;
    // Требования к уровню игрока для взятия квеста
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FName Player_Level_Condition;
    // Требования к выполненому ранее квесту
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FName Quest_Completed_Condition;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FS_Quest_Active_Progress
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") FName Index_Name_Quest;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FS_Quest_Talk_Progress> Quests_Talk_Progress;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest") TArray<FS_Quest_Kill_Progress> Quests_Kill_Progress;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup=(Quest), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class MMORPG_API UQuest : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UQuest();

    // Наследумемый метод репликации перменных с условиями
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
  
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Quest") TArray<FName> Quest_Active;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Quest") TArray<FName> Quest_Completed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Quest") TArray<FName> Quest_Completed_Daily;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Quest") TArray<FName> Quest_Completed_Weakly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Quest") TArray<FS_Quest_Active_Progress> Quest_Active_Progress;


};
//----------------------------------------------------------------------------------------------------------------------------------------------------