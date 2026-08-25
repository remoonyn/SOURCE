#pragma once

#include "CoreMinimal.h"
#include "AttributeType.generated.h"

UENUM(BlueprintType)
enum class E_Attribute_Type : uint8
{
	//Main
	None								UMETA(DisplayName = "None"),
	Health								UMETA(DisplayName = "Health"),
	Mana								UMETA(DisplayName = "Mana"),
	Stamina								UMETA(DisplayName = "Stamina"),
	MaxHealth							UMETA(DisplayName = "Max Health"),
	MaxMana								UMETA(DisplayName = "Max Mana"),
	MaxStamina							UMETA(DisplayName = "Max Stamina"),
	RegenHealth							UMETA(DisplayName = "Regen Health"),
	RegenMana							UMETA(DisplayName = "Regen Mana"),
	RegenStamina						UMETA(DisplayName = "Regen Stamina"),

	//Attacking
	Attack								UMETA(DisplayName = "Attack"),
	AttackPhysical						UMETA(DisplayName = "Attack Physical"),
	AttackMagical						UMETA(DisplayName = "Attack Magical"),
	AttackElemental						UMETA(DisplayName = "Attack Elemental"),
	CritChance							UMETA(DisplayName = "Crit Chance"),
	CritDamage							UMETA(DisplayName = "Crit Damage"),

	//Defence 
	Defence								UMETA(DisplayName = "Defence"),
	DefencePhysical						UMETA(DisplayName = "Defence Physical"),
	DefenceMagical						UMETA(DisplayName = "Defence Magical"),
	DefenceElemental					UMETA(DisplayName = "Defence Elemental")

};

UENUM(BlueprintType)
enum class E_Parameter_Type : uint8
{
	None								UMETA(DisplayName = "None"),
	Vitality							UMETA(DisplayName = "Vitality"),
	Wisdom								UMETA(DisplayName = "Wisdom"),
	Endurance							UMETA(DisplayName = "Endurance"),
	Dexterity							UMETA(DisplayName = "Dexterity"),
	Strength							UMETA(DisplayName = "Strength"),
	Intelligence						UMETA(DisplayName = "Intelligence"),
	Faith								UMETA(DisplayName = "Faith"),
	Luck								UMETA(DisplayName = "Luck")
};

UENUM(BlueprintType)
enum class E_Attribute_Parameter_Type : uint8
{
	None								UMETA(DisplayName = "None"),
	DecreaseIncomingDamage				UMETA(DisplayName = "Decrease Incoming Damage"),
	DecreaseManaCost					UMETA(DisplayName = "Decrease Mana Cost"),
	DecreaseStaminaCost					UMETA(DisplayName = "Decrease Stamina Cost"),
	IncreaseSpeed						UMETA(DisplayName = "Increase Speed"),
	IncreaseAttackPhysical				UMETA(DisplayName = "Increase Attack Physical"),
	IncreaseAttackMagical				UMETA(DisplayName = "Increase Attack Magical"),
	IncreaseAttackElemental				UMETA(DisplayName = "Increase Attack Elemental "),
	IncreaseCriticalChance				UMETA(DisplayName = "Increase Critical Chance")
};




//SpecialDamage						UMETA(DisplayName = "Special Damage"),
//ElementalDamageReaction				UMETA(DisplayName = "Elemental Damage Reaction"),
//StatusEffectChance					UMETA(DisplayName = "Status Effect Chance"),
//StatusEffectPower					UMETA(DisplayName = "Status Effect Power"),
//DecreaseCriticalChance				UMETA(DisplayName = "Decrease Critical Chance Received"),
//DecreaseCriticalDamage				UMETA(DisplayName = "Decrease Critical Damage"),
//DecreaseElementalDamageReaction		UMETA(DisplayName = "Decrease Elemental Damage Reaction"),
//DecreaseStatusEffectChance			UMETA(DisplayName = "Decrease Status Effect Chance"),
//DecreaseStatusEffectPower			UMETA(DisplayName = "Decrease Status Effect Power"),
////Resis
//StunResist							UMETA(DisplayName = "Stun Resist"),
//WeakeningResist						UMETA(DisplayName = "Weakening Resist"),
//KnockdownResist						UMETA(DisplayName = "Knockdown Resist"),
//DisplacementResist					UMETA(DisplayName = "Displacement Resist"),
//SlowdownResist						UMETA(DisplayName = "Slowdown Resist"),
//IgnoreStunResist					UMETA(DisplayName = "Ignore Stun Resist"),
//IgnoreWeakeningResist				UMETA(DisplayName = "Ignore Weakening Resist"),
//IgnoreKnockdownResist				UMETA(DisplayName = "Ignore Knockdown Resist"),
//IgnoreDisplacementResist			UMETA(DisplayName = "Ignore Displacement Resist"),
//IgnoreSlowdownResist				UMETA(DisplayName = "Ignore Slowdown Resist"),
////Speed
//AttackSpeed							UMETA(DisplayName = "Attack Speed"),
//MovementSpeed						UMETA(DisplayName = "Movement Speed"),
////Parameters

////Parameters bonuses
//IncreaseHealth						UMETA(DisplayName = "Increase Health"),
//DamageResistance					UMETA(DisplayName = "Damage Resistance"),
//IncreaseMana						UMETA(DisplayName = "Increase Mana"),
//DecreaseManaCost					UMETA(DisplayName = "Decrease Mana Cost"),
//IncreaseStamina						UMETA(DisplayName = "Increase Stamina"),
//StaminaCostMultiplier				UMETA(DisplayName = "Stamina Cost Multiplier"),
//IncreaseAttackSpeed					UMETA(DisplayName = "Increase Attack Speed"),
//IncreaseMovementSpeed				UMETA(DisplayName = "Increase Movement Speed"),
//IncreasePhysicalAttack				UMETA(DisplayName = "Increase Physical Attack"),
//IncreaseMagicalAttack				UMETA(DisplayName = "Increase Magical Attack"),
//IncreaseElementalDamage				UMETA(DisplayName = "Increase Elemental Damage"),
//IncreaseCriticalChance				UMETA(DisplayName = "Increase Critical Chance"),
////Percentage
//BoostAttack							UMETA(DisplayName = "Boost Attack"),
//BoostAttackPhysical					UMETA(DisplayName = "Boost Attack Physical"),
//BoostAttackMagical					UMETA(DisplayName = "Boost Attack Magical"),
//BoostAttackElemental				UMETA(DisplayName = "Boost Attack Elemental"),
//BoostDefence						UMETA(DisplayName = "Boost Defence"),
//BoostDefencePhysical				UMETA(DisplayName = "Boost Defence Physical"),
//BoostDefenceMagical					UMETA(DisplayName = "Boost Defence Magical"),
//BoostDefenceElemental				UMETA(DisplayName = "Boost Defence Elemental")