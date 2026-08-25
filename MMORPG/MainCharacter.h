#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainAttributeSet.h"
#include "AttributeSetParameters.h"
#include "Structures/MainStructures.h"
#include "AbilitySystemComponent.h"
#include "MMORPG/Characters/Creature.h"
#include "MainCharacter.generated.h"

class UItemsContainer;

UCLASS()
class MMORPG_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintNativeEvent, Category = "Container") void Update_Container_Slot_UI(int32 index_update_slot, EContainerType container_type, FS_Item_Container item_info);
	UFUNCTION(BlueprintNativeEvent, Category = "Container") void Reset_Container_Slot_UI(int32 index_reset_slot, EContainerType container_type);
	UFUNCTION(BlueprintNativeEvent, Category = "Container") void Update_Container_Slots_Value_UI(EContainerType container_type, int32 curr_slots, int32 max_slots);
	// Метод вызываемый из контроллера при попытке увеличеть слоты в контейнере.
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Container") void Add_New_Container_Slot_UI(UItemsContainer* container);
	// Получение награды за убийство монстра: опыт, дроп и прочее.
	UFUNCTION(Server, Reliable, Category = "Combat") void Creature_Killed(AActor* target);
	UFUNCTION(BlueprintNativeEvent, Category = "Combat") void Creature_Bounty(ACreature* target);
	// Уведомление о нанесенном уроне
	UFUNCTION(BlueprintNativeEvent, Category = "Combat") void Apply_Damage_Notify(bool crit, float value, float curr_health, float max_health);


protected:
	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);

	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void RegenHealthChanged(const FOnAttributeChangeData& Data);
	virtual void RegenManaChanged(const FOnAttributeChangeData& Data);
	virtual void RegenStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void AttackChanged(const FOnAttributeChangeData& Data);
	virtual void AttackPhysicalChanged(const FOnAttributeChangeData& Data);
	virtual void AttackMagicalChanged(const FOnAttributeChangeData& Data);
	virtual void AttackElementalChanged(const FOnAttributeChangeData& Data);
	virtual void ChanceCriticalStrikeChanged(const FOnAttributeChangeData& Data);
	virtual void DamageCriticalStrikeChanged(const FOnAttributeChangeData& Data);
	virtual void DefenceChanged(const FOnAttributeChangeData& Data);
	virtual void DefencePhysicalChanged(const FOnAttributeChangeData& Data);
	virtual void DefenceMagicalChanged(const FOnAttributeChangeData& Data);
	virtual void DefenceElementalChanged(const FOnAttributeChangeData& Data);

	virtual void VitalityChanged(const FOnAttributeChangeData& Data);
	virtual void WisdomChanged(const FOnAttributeChangeData& Data);
	virtual void EnduranceChanged(const FOnAttributeChangeData& Data);
	virtual void DexterityChanged(const FOnAttributeChangeData& Data);
	virtual void StrengthChanged(const FOnAttributeChangeData& Data);
	virtual void IntelligenceChanged(const FOnAttributeChangeData& Data);
	virtual void FaithChanged(const FOnAttributeChangeData& Data);
	virtual void LuckChanged(const FOnAttributeChangeData& Data);

	virtual void DecreaseIncomingDamageChanged(const FOnAttributeChangeData& Data);
	virtual void DecreaseManaCostChanged(const FOnAttributeChangeData& Data);
	virtual void DecreaseStaminaCostChanged(const FOnAttributeChangeData& Data);
	virtual void IncreaseSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void IncreaseAttackPhysicalChanged(const FOnAttributeChangeData& Data);
	virtual void IncreaseAttackMagicalChanged(const FOnAttributeChangeData& Data);
	virtual void IncreaseAttackElementalChanged(const FOnAttributeChangeData& Data);
	virtual void IncreaseCriticalChanceChanged(const FOnAttributeChangeData& Data);

	virtual void ToxicityChanged(const FOnAttributeChangeData& Data);
	virtual void MaxToxicityChanged(const FOnAttributeChangeData& Data);


	UFUNCTION(BlueprintNativeEvent, Category = "Attribute") void UpdateCritChance(const float NewCritChance);

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")  void UpdateHealth(const float NewHealth);
	UFUNCTION(BlueprintNativeEvent, Category = "Combat")  void UpdateMana(const float NewMana);
	UFUNCTION(BlueprintNativeEvent, Category = "Combat")  void UpdateStamina(const float NewStamina);
	// Проверка параметров на получение перка
	UFUNCTION(BlueprintNativeEvent, Category = "Perks")  void Check_Perks(E_Parameter_Type parameter_type, float parameter_value);
	// Получение уровня эффекта из active gameplay effect handle.
	UFUNCTION(BlueprintCallable, Category = "Effect") int32 Get_Active_Gameplay_Effect_Level(FActiveGameplayEffectHandle EffectHandle) const;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes") UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes") const UMainAttributeSet* MainAttributeSet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes") const UAttributeSetParameters* AttributeSetParameters;

};