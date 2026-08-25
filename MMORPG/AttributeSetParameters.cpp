#include "AttributeSetParameters.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Vitality,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Wisdom,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Endurance,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Dexterity,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Strength,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Intelligence,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Faith,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetParameters, Luck,			COND_None, REPNOTIFY_Always);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Vitality(const FGameplayAttributeData& OldVitality)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Vitality, OldVitality);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Wisdom, OldWisdom);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Endurance(const FGameplayAttributeData& OldEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Endurance, OldEndurance);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Dexterity, OldDexterity);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Strength, OldStrength);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Intelligence, OldIntelligence);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Faith(const FGameplayAttributeData& OldFaith)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Faith, OldFaith);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UAttributeSetParameters::OnRep_Luck(const FGameplayAttributeData& OldLuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetParameters, Luck, OldLuck);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
