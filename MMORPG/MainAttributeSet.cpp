#include "MainAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MainCharacter.h"
#include "Net/UnrealNetwork.h"


//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Health,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxHealth,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Mana,					COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxMana,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Stamina,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxStamina,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, RegenHealth,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, RegenMana,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, RegenStamina,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Attack,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, AttackPhysical,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, AttackMagical,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, AttackElemental,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Defence,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DefencePhysical,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DefenceMagical,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DefenceElemental,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, ChanceCriticalStrike, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DamageCriticalStrike, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DecreaseIncomingDamage,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DecreaseManaCost,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DecreaseStaminaCost,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, IncreaseSpeed,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, IncreaseAttackPhysical,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, IncreaseAttackMagical,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, IncreaseAttackElemental,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, IncreaseCriticalChance,	COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Toxicity,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxToxicity, COND_None, REPNOTIFY_Always);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UMainAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return true;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	// Обработка текущего здоровья. В будущем, когда у мобов будут другие атрибут сеты изменить логику в этом блоке.
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		float health = GetHealth();

		if (health <= 0.0f)
		{
			const FGameplayEffectSpec& effect_spec = Data.EffectSpec; // Получаем спецификацию эффекта 
			AActor* instigator = effect_spec.GetContext().GetInstigator(); // Получаем из контекста указатель на источник эффекта.
			AMainCharacter* character = Cast<AMainCharacter>(instigator);

			if (character)
			{
				if (AActor* target = Data.Target.GetOwner())
				{
					character->Creature_Killed(target);
				}
			}
		}
	}

	// Обработка текущей маны
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}

	// Обработка текущей выносливости
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	// Обработка максимального здоровья
	if (Attribute == GetMaxHealthAttribute())
	{
		float delta = NewValue - OldValue;
		if (delta > 0)
		{
			SetHealth(GetHealth() + delta);
		}

		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	// Обработка максимальной маны
	if (Attribute == GetMaxManaAttribute())
	{
		float delta = NewValue - OldValue;
		if (delta > 0)
		{
			SetMana(GetMana() + delta);
		}

		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}

	// Обработка максимальной маны
	if (Attribute == GetMaxStaminaAttribute())
	{
		float delta = NewValue - OldValue;
		if (delta > 0)
		{
			SetStamina(GetStamina() + delta);
		}

		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Health, OldHealth);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MaxHealth, OldMaxHealth);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Mana, OldMana);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MaxMana, OldMaxMana);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Stamina, OldStamina);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MaxStamina, OldMaxStamina);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_RegenHealth(const FGameplayAttributeData& OldRegenHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, RegenHealth, OldRegenHealth);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_RegenMana(const FGameplayAttributeData& OldRegenMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, RegenMana, OldRegenMana);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_RegenStamina(const FGameplayAttributeData& OldRegenStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, RegenStamina, OldRegenStamina);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Attack, OldAttack);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_AttackPhysical(const FGameplayAttributeData& OldAttackPhysical)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, AttackPhysical, OldAttackPhysical);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_AttackMagical(const FGameplayAttributeData& OldAttackMagical)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, AttackMagical, OldAttackMagical);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_AttackElemental(const FGameplayAttributeData& OldAttackElemental)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, AttackElemental, OldAttackElemental);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_Defence(const FGameplayAttributeData& OldDefence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Defence, OldDefence);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_DefencePhysical(const FGameplayAttributeData& OldDefencePhysical)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DefencePhysical, OldDefencePhysical);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_DefenceMagical(const FGameplayAttributeData& OldDefenceMagical)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DefenceMagical, OldDefenceMagical);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_DefenceElemental(const FGameplayAttributeData& OldDefenceElemental)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DefenceElemental, OldDefenceElemental);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_ChanceCriticalStrike(const FGameplayAttributeData& OldChanceCriticalStrike)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, ChanceCriticalStrike, OldChanceCriticalStrike);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_DamageCriticalStrike(const FGameplayAttributeData& OldDamageCriticalStrike)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DamageCriticalStrike, OldDamageCriticalStrike);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_DecreaseIncomingDamage(const FGameplayAttributeData& OldDecreaseIncomingDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DecreaseIncomingDamage, OldDecreaseIncomingDamage);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_DecreaseManaCost(const FGameplayAttributeData& OldDecreaseManaCost)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DecreaseManaCost, OldDecreaseManaCost);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_DecreaseStaminaCost(const FGameplayAttributeData& OldDecreaseStaminaCost)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DecreaseStaminaCost, OldDecreaseStaminaCost);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_IncreaseSpeed(const FGameplayAttributeData& OldIncreaseSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, IncreaseSpeed, OldIncreaseSpeed);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_IncreaseAttackPhysical(const FGameplayAttributeData& OldIncreaseAttackPhysical)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, IncreaseAttackPhysical, OldIncreaseAttackPhysical);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_IncreaseAttackMagical(const FGameplayAttributeData& OldIncreaseAttackMagical)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, IncreaseAttackMagical, OldIncreaseAttackMagical);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_IncreaseAttackElemental(const FGameplayAttributeData& OldIncreaseAttackElemental)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, IncreaseAttackElemental, OldIncreaseAttackElemental);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_IncreaseCriticalChance(const FGameplayAttributeData& OldIncreaseCriticalChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, IncreaseCriticalChance, OldIncreaseCriticalChance);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_Toxicity(const FGameplayAttributeData& OldToxicity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Toxicity, OldToxicity);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UMainAttributeSet::OnRep_MaxToxicity(const FGameplayAttributeData& OldMaxToxicity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MaxToxicity, OldMaxToxicity);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
