#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetParameters.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// Атрибуты параметров персонажа / Бонусы параметров персонажа / Очки параметров
	
UCLASS()
class MMORPG_API UAttributeSetParameters : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION() virtual void OnRep_Vitality		(const FGameplayAttributeData& OldVitality);
	UFUNCTION() virtual void OnRep_Wisdom		(const FGameplayAttributeData& OldWisdom);
	UFUNCTION() virtual void OnRep_Endurance	(const FGameplayAttributeData& OldEndurance);
	UFUNCTION() virtual void OnRep_Dexterity	(const FGameplayAttributeData& OldDexterity);
	UFUNCTION() virtual void OnRep_Strength		(const FGameplayAttributeData& OldStrength);
	UFUNCTION() virtual void OnRep_Intelligence	(const FGameplayAttributeData& OldIntelligence);
	UFUNCTION() virtual void OnRep_Faith		(const FGameplayAttributeData& OldFaith);
	UFUNCTION() virtual void OnRep_Luck			(const FGameplayAttributeData& OldLuck);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Vitality)			FGameplayAttributeData Vitality;			ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Vitality)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Wisdom)				FGameplayAttributeData Wisdom;				ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Wisdom)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Endurance)			FGameplayAttributeData Endurance;			ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Endurance)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Dexterity)			FGameplayAttributeData Dexterity;			ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Dexterity)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Strength)			FGameplayAttributeData Strength;			ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Strength)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Intelligence)		FGameplayAttributeData Intelligence;		ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Intelligence)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Faith)				FGameplayAttributeData Faith;				ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Faith)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Luck)				FGameplayAttributeData Luck;				ATTRIBUTE_ACCESSORS(UAttributeSetParameters, Luck)
};
