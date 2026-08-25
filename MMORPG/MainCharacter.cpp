#include "MainCharacter.h"
#include "MainController.h"
#include "ItemsContainer.h"

//Public
//----------------------------------------------------------------------------------------------------------------------------------------------------
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Update_Container_Slot_UI_Implementation(int32 index_update_slot, EContainerType container_type, FS_Item_Container item_info)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Reset_Container_Slot_UI_Implementation(int32 index_reset_slot, EContainerType container_type)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Update_Container_Slots_Value_UI_Implementation(EContainerType container_type, int32 curr_slots, int32 max_slots)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Add_New_Container_Slot_UI_Implementation(UItemsContainer* container)
{
	if (!container || !container->TryAddSlot())
	{
		return; 
	}

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		player_controller->Add_New_Container_Slot_UI(container->Container_Type);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Creature_Killed_Implementation(AActor* target)
{
	ACreature* cast_target = Cast<ACreature>(target);
	if (cast_target)
	{
		Creature_Bounty(cast_target);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Creature_Bounty_Implementation(ACreature* target)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Apply_Damage_Notify_Implementation(bool crit, float value, float curr_health, float max_health)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

//Protected
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilitySystemComponent))
	{
		// Задаем перменную при старте игры
		MainAttributeSet = AbilitySystemComponent->GetSet<UMainAttributeSet>();
		AttributeSetParameters = AbilitySystemComponent->GetSet<UAttributeSetParameters>();

		// Подписываемя на основнные атрибуты, для обработки событий в том числе на серверной стороне.
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetHealthAttribute()).AddUObject	(this, &AMainCharacter::HealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetManaAttribute()).AddUObject	(this, &AMainCharacter::ManaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetStaminaAttribute()).AddUObject	(this, &AMainCharacter::StaminaChanged);

		// Подписываемя на атрибуты, только на клиентах, так как нам не нужно обновлять виджеты на сервере. Экономим трафик и CPU. Атрибуты сверху подписываются на сервере, так как обрабатывают логику по типу: смерти, нулевой стамины и т.д.
		if (GetNetMode() != NM_DedicatedServer)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AMainCharacter::MaxHealthChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetMaxManaAttribute()).AddUObject(this, &AMainCharacter::MaxManaChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &AMainCharacter::MaxStaminaChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetRegenHealthAttribute()).AddUObject(this, &AMainCharacter::RegenHealthChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetRegenManaAttribute()).AddUObject(this, &AMainCharacter::RegenManaChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetRegenStaminaAttribute()).AddUObject(this, &AMainCharacter::RegenStaminaChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetAttackAttribute()).AddUObject(this, &AMainCharacter::AttackChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetAttackPhysicalAttribute()).AddUObject(this, &AMainCharacter::AttackPhysicalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetAttackMagicalAttribute()).AddUObject(this, &AMainCharacter::AttackMagicalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetAttackElementalAttribute()).AddUObject(this, &AMainCharacter::AttackElementalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetChanceCriticalStrikeAttribute()).AddUObject(this, &AMainCharacter::ChanceCriticalStrikeChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDamageCriticalStrikeAttribute()).AddUObject(this, &AMainCharacter::DamageCriticalStrikeChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDefenceAttribute()).AddUObject(this, &AMainCharacter::DefenceChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDefencePhysicalAttribute()).AddUObject(this, &AMainCharacter::DefencePhysicalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDefenceMagicalAttribute()).AddUObject(this, &AMainCharacter::DefenceMagicalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDefenceElementalAttribute()).AddUObject(this, &AMainCharacter::DefenceElementalChanged);

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetVitalityAttribute()).AddUObject(this, &AMainCharacter::VitalityChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetWisdomAttribute()).AddUObject(this, &AMainCharacter::WisdomChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetEnduranceAttribute()).AddUObject(this, &AMainCharacter::EnduranceChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetDexterityAttribute()).AddUObject(this, &AMainCharacter::DexterityChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetStrengthAttribute()).AddUObject(this, &AMainCharacter::StrengthChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetIntelligenceAttribute()).AddUObject(this, &AMainCharacter::IntelligenceChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetFaithAttribute()).AddUObject(this, &AMainCharacter::FaithChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetParameters->GetLuckAttribute()).AddUObject(this, &AMainCharacter::LuckChanged);

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDecreaseIncomingDamageAttribute()).AddUObject(this, &AMainCharacter::DecreaseIncomingDamageChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDecreaseManaCostAttribute()).AddUObject(this, &AMainCharacter::DecreaseManaCostChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetDecreaseStaminaCostAttribute()).AddUObject(this, &AMainCharacter::DecreaseStaminaCostChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetIncreaseSpeedAttribute()).AddUObject(this, &AMainCharacter::IncreaseSpeedChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetIncreaseAttackPhysicalAttribute()).AddUObject(this, &AMainCharacter::IncreaseAttackPhysicalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetIncreaseAttackMagicalAttribute()).AddUObject(this, &AMainCharacter::IncreaseAttackMagicalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetIncreaseAttackElementalAttribute()).AddUObject(this, &AMainCharacter::IncreaseAttackElementalChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetIncreaseCriticalChanceAttribute()).AddUObject(this, &AMainCharacter::IncreaseCriticalChanceChanged);

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetToxicityAttribute()).AddUObject(this, &AMainCharacter::ToxicityChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetMaxToxicityAttribute()).AddUObject(this, &AMainCharacter::MaxToxicityChanged);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	float health = Data.NewValue;
	UpdateHealth(health);
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::Health;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::ManaChanged(const FOnAttributeChangeData& Data)
{
	float mana = Data.NewValue;
	UpdateMana(mana);
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::Mana;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::StaminaChanged(const FOnAttributeChangeData& Data)
{
	float stamina = Data.NewValue;
	UpdateStamina(stamina);
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::Stamina;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::MaxHealth;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::MaxMana;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::MaxStamina;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::RegenHealthChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::RegenHealth;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::RegenManaChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::RegenMana;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::RegenStaminaChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::RegenStamina;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::AttackChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::Attack;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::AttackPhysicalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::AttackPhysical;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::AttackMagicalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::AttackMagical;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::AttackElementalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::AttackElemental;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::ChanceCriticalStrikeChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::CritChance;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DamageCriticalStrikeChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::CritDamage;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DefenceChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::Defence;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DefencePhysicalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::DefencePhysical;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DefenceMagicalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::DefenceMagical;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DefenceElementalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Type attribute_type = E_Attribute_Type::DefenceElemental;
		player_controller->Update_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::VitalityChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Vitality, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Vitality;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::WisdomChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Wisdom, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Wisdom;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::EnduranceChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Endurance, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Endurance;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DexterityChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Dexterity, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Dexterity;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::StrengthChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Strength, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Strength;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::IntelligenceChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Intelligence, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Intelligence;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::FaithChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Faith, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Faith;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::LuckChanged(const FOnAttributeChangeData& Data)
{
	Check_Perks(E_Parameter_Type::Luck, Data.NewValue);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Parameter_Type attribute_type = E_Parameter_Type::Luck;
		player_controller->Update_Parameter_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DecreaseIncomingDamageChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::DecreaseIncomingDamage;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DecreaseManaCostChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::DecreaseManaCost;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::DecreaseStaminaCostChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::DecreaseStaminaCost;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::IncreaseSpeedChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::IncreaseSpeed;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::IncreaseAttackPhysicalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::IncreaseAttackPhysical;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::IncreaseAttackMagicalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::IncreaseAttackMagical;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::IncreaseAttackElementalChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::IncreaseAttackElemental;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::IncreaseCriticalChanceChanged(const FOnAttributeChangeData& Data)
{
	float new_attribute = Data.NewValue;
	UpdateCritChance(new_attribute);

	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		E_Attribute_Parameter_Type attribute_type = E_Attribute_Parameter_Type::IncreaseCriticalChance;
		player_controller->Update_Parameter_Attribute_UI(attribute_type, new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::ToxicityChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		player_controller->Update_Toxicity_UI(new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::MaxToxicityChanged(const FOnAttributeChangeData& Data)
{
	if (AMainController* player_controller = Cast<AMainController>(GetController()))
	{
		float new_attribute = Data.NewValue;
		player_controller->Update_Max_Toxicity_UI(new_attribute);
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::Check_Perks_Implementation(E_Parameter_Type parameter_type, float parameter_value)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::UpdateCritChance_Implementation(const float NewCritChance)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::UpdateMana_Implementation(const float NewMana)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::UpdateHealth_Implementation(const float NewHealth)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void AMainCharacter::UpdateStamina_Implementation(const float NewStamina)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
int32 AMainCharacter::Get_Active_Gameplay_Effect_Level(FActiveGameplayEffectHandle EffectHandle) const
{
	// Проверяем валидность хендла
	if (!EffectHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("GetActiveGameplayEffectLevel: Invalid EffectHandle"));
		return 0;
	}

	// Используем существующую переменную AbilitySystemComponent
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetActiveGameplayEffectLevel: No AbilitySystemComponent"));
		return 0;
	}

	// Пытаемся получить активный эффект по хендлу
	const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(EffectHandle);
	if (!ActiveEffect)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetActiveGameplayEffectLevel: Active effect not found"));
		return 0;
	}

	// Возвращаем уровень из спецификации эффекта
	return ActiveEffect->Spec.GetLevel();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
