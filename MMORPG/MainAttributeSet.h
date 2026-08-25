#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MainAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MMORPG_API UMainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	// Репликация и условия репликации для атрибутов.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Логика перед применением эффекта.
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	// Логика обработки атрибутов после изменения: смерть при нулевом хп, клэмпинг и прочее. Только для instant эффектов.
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Логика обработки атрибутов после изменения. Для изменений любыми эффектами.
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	UFUNCTION() virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION() virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION() virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION() virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	UFUNCTION() virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	UFUNCTION() virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
	UFUNCTION() virtual void OnRep_RegenHealth(const FGameplayAttributeData& OldRegenHealth);
	UFUNCTION() virtual void OnRep_RegenMana(const FGameplayAttributeData& OldRegenMana);
	UFUNCTION() virtual void OnRep_RegenStamina(const FGameplayAttributeData& OldRegenStamina);
	UFUNCTION() virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);
	UFUNCTION() virtual void OnRep_AttackPhysical(const FGameplayAttributeData& OldAttackPhysical);
	UFUNCTION() virtual void OnRep_AttackMagical(const FGameplayAttributeData& OldAttackMagical);
	UFUNCTION() virtual void OnRep_AttackElemental(const FGameplayAttributeData& OldAttackElemental);
	UFUNCTION() virtual void OnRep_Defence(const FGameplayAttributeData& OldDefence);
	UFUNCTION() virtual void OnRep_DefencePhysical(const FGameplayAttributeData& OldDefencePhysical);
	UFUNCTION() virtual void OnRep_DefenceMagical(const FGameplayAttributeData& OldDefenceMagical);
	UFUNCTION() virtual void OnRep_DefenceElemental(const FGameplayAttributeData& OldDefenceElemental);
	UFUNCTION() virtual void OnRep_ChanceCriticalStrike(const FGameplayAttributeData& OldChanceCriticalStrike);
	UFUNCTION() virtual void OnRep_DamageCriticalStrike(const FGameplayAttributeData& OldDamageCriticalStrike);

	UFUNCTION() virtual void OnRep_DecreaseIncomingDamage(const FGameplayAttributeData& OldDecreaseIncomingDamage);
	UFUNCTION() virtual void OnRep_DecreaseManaCost(const FGameplayAttributeData& OldDecreaseManaCost);
	UFUNCTION() virtual void OnRep_DecreaseStaminaCost(const FGameplayAttributeData& OldDecreaseStaminaCost);
	UFUNCTION() virtual void OnRep_IncreaseSpeed(const FGameplayAttributeData& OldIncreaseSpeed);
	UFUNCTION() virtual void OnRep_IncreaseAttackPhysical(const FGameplayAttributeData& OldIncreaseAttackPhysical);
	UFUNCTION() virtual void OnRep_IncreaseAttackMagical(const FGameplayAttributeData& OldIncreaseAttackMagical);
	UFUNCTION() virtual void OnRep_IncreaseAttackElemental(const FGameplayAttributeData& OldIncreaseAttackElemental);
	UFUNCTION() virtual void OnRep_IncreaseCriticalChance(const FGameplayAttributeData& OldIncreaseCriticalChance);
	UFUNCTION() virtual void OnRep_Toxicity(const FGameplayAttributeData& OldToxicity);

	UFUNCTION() virtual void OnRep_MaxToxicity(const FGameplayAttributeData& OldMaxToxicity);






	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)						FGameplayAttributeData Health;					ATTRIBUTE_ACCESSORS(UMainAttributeSet, Health)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)				FGameplayAttributeData MaxHealth;				ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxHealth)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mana)					FGameplayAttributeData Mana;					ATTRIBUTE_ACCESSORS(UMainAttributeSet, Mana)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxMana)				FGameplayAttributeData MaxMana;					ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxMana)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)				FGameplayAttributeData Stamina;					ATTRIBUTE_ACCESSORS(UMainAttributeSet, Stamina)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)				FGameplayAttributeData MaxStamina;				ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxStamina)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_RegenHealth)			FGameplayAttributeData RegenHealth;				ATTRIBUTE_ACCESSORS(UMainAttributeSet, RegenHealth)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_RegenMana)				FGameplayAttributeData RegenMana;				ATTRIBUTE_ACCESSORS(UMainAttributeSet, RegenMana)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_RegenStamina)			FGameplayAttributeData RegenStamina;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, RegenStamina)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Attack)					FGameplayAttributeData Attack;					ATTRIBUTE_ACCESSORS(UMainAttributeSet, Attack)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPhysical)			FGameplayAttributeData AttackPhysical;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, AttackPhysical)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackMagical)			FGameplayAttributeData AttackMagical;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, AttackMagical)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackElemental)		FGameplayAttributeData AttackElemental;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, AttackElemental)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Defence)				FGameplayAttributeData Defence;					ATTRIBUTE_ACCESSORS(UMainAttributeSet, Defence)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DefencePhysical)		FGameplayAttributeData DefencePhysical;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, DefencePhysical)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DefenceMagical)			FGameplayAttributeData DefenceMagical;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, DefenceMagical)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DefenceElemental)		FGameplayAttributeData DefenceElemental;		ATTRIBUTE_ACCESSORS(UMainAttributeSet, DefenceElemental)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ChanceCriticalStrike)	FGameplayAttributeData ChanceCriticalStrike;	ATTRIBUTE_ACCESSORS(UMainAttributeSet, ChanceCriticalStrike)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DamageCriticalStrike)	FGameplayAttributeData DamageCriticalStrike;	ATTRIBUTE_ACCESSORS(UMainAttributeSet, DamageCriticalStrike)

		// Parameter Bonus
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DecreaseIncomingDamage)			FGameplayAttributeData DecreaseIncomingDamage;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, DecreaseIncomingDamage)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DecreaseManaCost)				FGameplayAttributeData DecreaseManaCost;				ATTRIBUTE_ACCESSORS(UMainAttributeSet, DecreaseManaCost)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DecreaseStaminaCost)			FGameplayAttributeData DecreaseStaminaCost;				ATTRIBUTE_ACCESSORS(UMainAttributeSet, DecreaseStaminaCost)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_IncreaseSpeed)					FGameplayAttributeData IncreaseSpeed;					ATTRIBUTE_ACCESSORS(UMainAttributeSet, IncreaseSpeed)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_IncreaseAttackPhysical)			FGameplayAttributeData IncreaseAttackPhysical;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, IncreaseAttackPhysical)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_IncreaseAttackMagical)			FGameplayAttributeData IncreaseAttackMagical;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, IncreaseAttackMagical)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_IncreaseAttackElemental)		FGameplayAttributeData IncreaseAttackElemental;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, IncreaseAttackElemental)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_IncreaseCriticalChance)			FGameplayAttributeData IncreaseCriticalChance;			ATTRIBUTE_ACCESSORS(UMainAttributeSet, IncreaseCriticalChance)

		// Others
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Toxicity) FGameplayAttributeData Toxicity; ATTRIBUTE_ACCESSORS(UMainAttributeSet, Toxicity)
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxToxicity) FGameplayAttributeData MaxToxicity; ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxToxicity)

};