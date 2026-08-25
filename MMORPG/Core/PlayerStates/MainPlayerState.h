#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MMORPG/Enumerations/MainEnumerations.h"
#include "MainPlayerState.generated.h"


UCLASS()
class MMORPG_API AMainPlayerState : public APlayerState
{
    GENERATED_BODY()

public:

    AMainPlayerState();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player") FName Account;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player") FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player") E_Player_Status_Type Status = E_Player_Status_Type::Adventurer;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player") int32 Carma = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency") int32 Gold = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency") int32 Diamond = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling") int32 Level_Character = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling") int32 Experience_Level_Character_Current = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling") int32 Experience_Level_Character_Nedeed = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling") int32 Parameters_Points_Current = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Level_Weapon_Skill_Points = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Weapon_Skill_Points_Current = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Weapon_Skill_Points_Nedeed = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Weapon_Skill_Points = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Level_Weapon_Sword = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Sword_Current = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Sword_Nedeed = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Level_Weapon_Rapier = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Rapier_Current = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Rapier_Nedeed = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Level_Weapon_Grimoire = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Grimoire_Current = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int32 Experience_Level_Grimoire_Nedeed = 0;
};