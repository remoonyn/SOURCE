#pragma once

#include "CoreMinimal.h"
#include "MainEnumerations.generated.h"


UENUM(BlueprintType) enum class EGradeType : uint8
{
    Common      UMETA(DisplayName = "Common"),
    Uncommon    UMETA(DisplayName = "Uncommon"),
    Rare        UMETA(DisplayName = "Rare"),
    Epic        UMETA(DisplayName = "Epic"),
    Legendary   UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType) enum class EContainerType : uint8
{
    None        UMETA(DisplayName = "None"),
    Backpack    UMETA(DisplayName = "Backpack"),
    Storage     UMETA(DisplayName = "Storage"),
    Equipment   UMETA(DisplayName = "Equipment"),
    Trade       UMETA(DisplayName = "Trade"),
    Hotbar      UMETA(DisplayName = "Hotbar")
};

UENUM(BlueprintType) enum class EEquipmentType : uint8
{
    None        UMETA(DisplayName = "None"),
    WeaponOne   UMETA(DisplayName = "WeaponOne"),
    WeaponTwo   UMETA(DisplayName = "WeaponTwo"),
    WeaponThree UMETA(DisplayName = "WeaponThree"),
    Helmet      UMETA(DisplayName = "Helmet"),
    Chest       UMETA(DisplayName = "Chest"),
    Gloves      UMETA(DisplayName = "Gloves"),
    Pants       UMETA(DisplayName = "Pants"),
    Boots       UMETA(DisplayName = "Boots"),
    Belt        UMETA(DisplayName = "Belt"),
    Necklace    UMETA(DisplayName = "Necklace"),
    Bracelet    UMETA(DisplayName = "Bracelet"),
    RingOne     UMETA(DisplayName = "RingOne"),
    RingTwo     UMETA(DisplayName = "RingTwo"),
    EarringOne  UMETA(DisplayName = "EarringOne"),
    EarringTwo  UMETA(DisplayName = "EarringTwo")
};

//Item Asset Types

UENUM(BlueprintType) enum class EItemType : uint8
{
    None        UMETA(DisplayName = "None"),
    Resource    UMETA(DisplayName = "Resource"),
    Weapon      UMETA(DisplayName = "Weapon"),
    Armor       UMETA(DisplayName = "Armor"),
    Jewelry     UMETA(DisplayName = "Jewelry"),
    Consumable  UMETA(DisplayName = "Consumable"),
    Trophy      UMETA(DisplayName = "Trophy")
};
UENUM(BlueprintType) enum class EResourceType : uint8
{
    None        UMETA(DisplayName = "None"),
    Material    UMETA(DisplayName = "Material"),
    Animal      UMETA(DisplayName = "Animal"),
    Fuel        UMETA(DisplayName = "Fuel"),
    Feed        UMETA(DisplayName = "Feed"),
    Seed        UMETA(DisplayName = "Seed"),
    Fertilizer  UMETA(DisplayName = "Fertilizer"),
    Dust        UMETA(DisplayName = "Dust"),
    Core        UMETA(DisplayName = "Core"),
    Rune        UMETA(DisplayName = "Rune"),
    Gem         UMETA(DisplayName = "Gem")
};
UENUM(BlueprintType) enum class EWeaponType : uint8
{
    None        UMETA(DisplayName = "None"),
    Gauntlet    UMETA(DisplayName = "Gauntlet"),
    Sword       UMETA(DisplayName = "Sword"),
    Rapier      UMETA(DisplayName = "Rapier"),
    Bow         UMETA(DisplayName = "Bow"),
    Grimoire    UMETA(DisplayName = "Grimoire")
};
UENUM(BlueprintType) enum class EArmorType : uint8
{
    None        UMETA(DisplayName = "None"),
    Helmet      UMETA(DisplayName = "Helmet"),
    Chest       UMETA(DisplayName = "Chest"),
    Gloves      UMETA(DisplayName = "Gloves"),
    Pants       UMETA(DisplayName = "Pants"),
    Boots       UMETA(DisplayName = "Boots"),
    Belt        UMETA(DisplayName = "Belt")
};
UENUM(BlueprintType) enum class EJewelryType : uint8
{
    None        UMETA(DisplayName = "None"),
    Necklace    UMETA(DisplayName = "Necklace"),
    Bracelet    UMETA(DisplayName = "Bracelet"),
    Ring        UMETA(DisplayName = "Ring"),
    Earring     UMETA(DisplayName = "Earring")
};
UENUM(BlueprintType) enum class EConsumableType : uint8
{
    None        UMETA(DisplayName = "None"),
    Potion      UMETA(DisplayName = "Potion"),
    Food        UMETA(DisplayName = "Food")
};

UENUM(BlueprintType) enum class E_Profession_Type : uint8
{
    None        UMETA(DisplayName = "None"),
    Blacksmith  UMETA(DisplayName = "Blacksmith"),
    Enchanter   UMETA(DisplayName = "Enchanter"),
    Tinker      UMETA(DisplayName = "Tinker"),
    Alchemist   UMETA(DisplayName = "Alchemist"),
    Cook        UMETA(DisplayName = "Cook"),
    Lumberjack  UMETA(DisplayName = "Lumberjack"),
    Miner       UMETA(DisplayName = "Miner"),
    Hunter      UMETA(DisplayName = "Hunter"),
    Fisherman   UMETA(DisplayName = "Fisherman"),
    Gatherer    UMETA(DisplayName = "Gatherer"),
    Gardener    UMETA(DisplayName = "Gardener"),
    Breeder     UMETA(DisplayName = "Breeder")
};

UENUM(BlueprintType) enum class E_Player_Status_Type : uint8
{
    None         UMETA(DisplayName = "None"),
    Adventurer   UMETA(DisplayName = "Adventurer"), 
    Murderer     UMETA(DisplayName = "Murderer"),
    BountyHunter UMETA(DisplayName = "BountyHunter"),
    Defender     UMETA(DisplayName = "Defender"),
    Robber       UMETA(DisplayName = "Robber"),
    Protector    UMETA(DisplayName = "Protector"),
    Assaulter    UMETA(DisplayName = "Assaulter"),
    Mercenary    UMETA(DisplayName = "Mercenary")
};

UENUM(BlueprintType) enum class E_Attribute_Equip_Type : uint8
{
    None         UMETA(DisplayName = "None"),
    Base         UMETA(DisplayName = "Base"),
    Prefix       UMETA(DisplayName = "Prefix"),
    Suffix       UMETA(DisplayName = "Suffix"),
    Special      UMETA(DisplayName = "Special"),
    Set          UMETA(DisplayName = "Set")
};

UENUM(BlueprintType) enum class E_Recipe_Effect : uint8
{
   None         UMETA(DisplayName = "None"),
   Duration     UMETA(DisplayName = "Duration"),
   Required     UMETA(DisplayName = "Required"),
   Price        UMETA(DisplayName = "Price")

};

UENUM(BlueprintType) enum class E_Line_Type : uint8
{
   None         UMETA(DisplayName = "None"),
   Welcome      UMETA(DisplayName = "Welcome"),
   Auto         UMETA(DisplayName = "Auto"),
   Reply        UMETA(DisplayName = "Reply"),
   Accept       UMETA(DisplayName = "Accept"),
   Reject       UMETA(DisplayName = "Reject"),
   Remove       UMETA(DisplayName = "Remove"),
   Branch       UMETA(DisplayName = "Branch"),
   Complete     UMETA(DisplayName = "Complete"),
   Trade        UMETA(DisplayName = "Trade"),
   Leave        UMETA(DisplayName = "Leave")
};

UENUM(BlueprintType) enum class E_Dialog_Type : uint8
{
   None         UMETA(DisplayName = "None"),
   Common       UMETA(DisplayName = "Common"),
   Quest        UMETA(DisplayName = "Quest"),
   Trade        UMETA(DisplayName = "Trade"),
   Leave        UMETA(DisplayName = "Leave")
};

UENUM(BlueprintType) enum class E_Combat_Skill_Keys : uint8
{
   None           UMETA(DisplayName = "None"),
   LBM            UMETA(DisplayName = "LBM"),
   RBM            UMETA(DisplayName = "RBM"),
   TAB            UMETA(DisplayName = "TAB"),
   Q              UMETA(DisplayName = "Q"),
   E              UMETA(DisplayName = "E"),
   F              UMETA(DisplayName = "F"),
   Z              UMETA(DisplayName = "Z"),
   X              UMETA(DisplayName = "X"),
   C              UMETA(DisplayName = "C"),
   V              UMETA(DisplayName = "V"),
   W_LBM          UMETA(DisplayName = "W+LBM"),
   W_RBM          UMETA(DisplayName = "W+RBM"),
   W_Q            UMETA(DisplayName = "W+Q"),
   W_E            UMETA(DisplayName = "W+E"),
   W_F            UMETA(DisplayName = "W+F"),
   S_LBM          UMETA(DisplayName = "S+LBM"),
   S_RBM          UMETA(DisplayName = "S+RBM"),
   S_Q            UMETA(DisplayName = "S+Q"),
   S_E            UMETA(DisplayName = "S+E"),
   S_F            UMETA(DisplayName = "S+F"),
   Shift_LBM      UMETA(DisplayName = "Shift+LBM"),
   Shift_RBM      UMETA(DisplayName = "Shift+RBM"),
   Shift_Q        UMETA(DisplayName = "Shift+Q"),
   Shift_E        UMETA(DisplayName = "Shift+E"),
   Shift_F        UMETA(DisplayName = "Shift+F"),
   Shift_Z        UMETA(DisplayName = "Shift+Z"),
   Shift_X        UMETA(DisplayName = "Shift+X"),
   Shift_C        UMETA(DisplayName = "Shift+C"),
   Shift_V        UMETA(DisplayName = "Shift+V"),
   Shift_Space    UMETA(DisplayName = "Shift+Space")
};