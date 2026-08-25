#include "DamageExecution.h"
#include "MainAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "MainCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"

UDamageExecution::UDamageExecution()
{
    // Указываем какие атрибуты мы будем захватывать для расчетов (в будущем криты, шансы статуса, бонусы к урону и т.д.)
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetAttackAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetAttackPhysicalAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetAttackMagicalAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetAttackElementalAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetChanceCriticalStrikeAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetDamageCriticalStrikeAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetIncreaseAttackPhysicalAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetIncreaseAttackMagicalAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetIncreaseAttackElementalAttribute(), EGameplayEffectAttributeCaptureSource::Source, false));

    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetDefenceAttribute(), EGameplayEffectAttributeCaptureSource::Target, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetDefencePhysicalAttribute(), EGameplayEffectAttributeCaptureSource::Target, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetDefenceMagicalAttribute(), EGameplayEffectAttributeCaptureSource::Target, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetDefenceElementalAttribute(), EGameplayEffectAttributeCaptureSource::Target, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetDecreaseIncomingDamageAttribute(), EGameplayEffectAttributeCaptureSource::Target, false));

    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetMaxHealthAttribute(), EGameplayEffectAttributeCaptureSource::Target, false));
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(UMainAttributeSet::GetHealthAttribute(), EGameplayEffectAttributeCaptureSource::Target, false));
}

void UDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    // Получаем Source и Target Ability System (для будущей логики)
    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    if (!SourceASC || !TargetASC) return;

    // Получаем акторов "источник" и "цель"
    AActor* source_actor = SourceASC ? SourceASC->GetAvatarActor_Direct() : nullptr;
    AActor* target_actor = TargetASC ? TargetASC->GetAvatarActor_Direct() : nullptr;

    // Получаем Attribute Sets
    const UMainAttributeSet* source_attributes = ExecutionParams.GetSourceAbilitySystemComponent()->GetSet<UMainAttributeSet>();
    const UMainAttributeSet* target_attributes = ExecutionParams.GetTargetAbilitySystemComponent()->GetSet<UMainAttributeSet>();

    if (!source_attributes || !target_attributes) return;

    // Проверка на жив/мертв цель
    float health = 0.0f;
    float max_health = 0.0f;

    // Переменная для получения атрибутов
    FAggregatorEvaluateParameters eval_params;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(target_attributes->GetMaxHealthAttribute(), EGameplayEffectAttributeCaptureSource::Target, false), eval_params, max_health);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(target_attributes->GetHealthAttribute(), EGameplayEffectAttributeCaptureSource::Target, false), eval_params, health);

    if (health <= 0.0f)
    {
        FString dead_message = FString::Printf(TEXT("[DamageExecution C++] Character already dead!"));
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, dead_message);
        UE_LOG(LogTemp, Warning, TEXT("%s"), *dead_message);
        return;
    }

    // Читаем базовый урон из GameplayEffect (передан через SetByCaller). Нужен tag "Data.Health". Делением на 100 - делаем мультипликатор.
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    float base_damage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Health")), false, 0.0f) / 100;


    // Задаем локальные переменные с базовым значением, на случай ошибки в попытке достать их из атрибутов позднее
    float attack = 0.0f;
    float attack_physical = 0.0f;
    float attack_magical = 0.0f;
    float attack_elemental = 0.0f;
    float crit_chance = 0.0f;
    float crit_damage = 0.0f;
    float inc_attack_physical = 0.0f;
    float inc_attack_magical = 0.0f;
    float inc_attack_elemental = 0.0f;

    float defence = 0.0f;
    float defence_phisycal = 0.0f;
    float defence_magical = 0.0f;
    float defence_elemental = 0.0f;
    float dec_damage_income = 0.0f;

 

    // Задаем параметры для следующих функций (пока пустые)
    

    // Получаем атрибуты у источника
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetAttackAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, attack);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetAttackPhysicalAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, attack_physical);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetAttackMagicalAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, attack_magical);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetAttackElementalAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, attack_elemental);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetChanceCriticalStrikeAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, crit_chance);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetDamageCriticalStrikeAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, crit_damage);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetIncreaseAttackPhysicalAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, inc_attack_physical);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetIncreaseAttackMagicalAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, inc_attack_magical);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(source_attributes->GetIncreaseAttackElementalAttribute(),EGameplayEffectAttributeCaptureSource::Source, false), eval_params, inc_attack_elemental);

    // Получаем атрибуты у цели
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(target_attributes->GetDefenceAttribute(),EGameplayEffectAttributeCaptureSource::Target, false), eval_params, defence);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(target_attributes->GetDefencePhysicalAttribute(),EGameplayEffectAttributeCaptureSource::Target, false), eval_params, defence_phisycal);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(target_attributes->GetDefenceMagicalAttribute(),EGameplayEffectAttributeCaptureSource::Target, false), eval_params, defence_magical);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(target_attributes->GetDefenceElementalAttribute(),EGameplayEffectAttributeCaptureSource::Target, false), eval_params, defence_elemental);
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(target_attributes->GetDecreaseIncomingDamageAttribute(),EGameplayEffectAttributeCaptureSource::Target, false), eval_params, dec_damage_income);

    // Проверка на крит удар
    float random_crit_roll = UKismetMathLibrary::RandomFloatInRange(0.0f, 100.0f);
    float crit_multiplier = 1.0f;

    bool is_critical_strike = (random_crit_roll <= crit_chance);

    if (is_critical_strike)
    {
        crit_multiplier = 1.0f + (crit_damage / 100.0f);
    }

    // Преобразуем снижение урона в множитель
    float damage_reduction = 1.0f - (dec_damage_income / 100.0f);
    float reduction_multiplier = FMath::Clamp(damage_reduction, 0.0f, 1.0f);
    
    // Пред расчеты для финального урона
    float damage = FMath::Max(0.0f, (attack - defence));
    float physical_multipiler = 1.0f + (inc_attack_physical / 100.0f);
    float magical_multipiler = 1.0f + (inc_attack_magical / 100.0f);
    float elemental_multipiler = 1.0f + (inc_attack_elemental / 100.0f);
    float physical_damage = FMath::Max(0.0f, (attack_physical * physical_multipiler - defence_phisycal));
    float magical_damage = FMath::Max(0.0f, (attack_magical * magical_multipiler - defence_magical));
    float elemental_damage = FMath::Max(0.0f, (attack_elemental * elemental_multipiler - defence_elemental));
    damage = FMath::Max(1.0f, (damage + physical_damage + magical_damage + elemental_damage));


    // Расчет итогового урона
    float final_damage = damage * base_damage * crit_multiplier * damage_reduction;

    // Уведомление об уроне
    if (source_actor && source_actor->IsA(AMainCharacter::StaticClass()))
    {
        if (AMainCharacter* char_source = Cast<AMainCharacter>(source_actor))
        {
            char_source->Apply_Damage_Notify(is_critical_strike, final_damage, health, max_health);
        }
    }

    // Применяем итоговый урон к "Здоровью" цели
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(target_attributes->GetHealthAttribute(),EGameplayModOp::Additive, -final_damage));

    // Логирование
    FString calc_damage_message = FString::Printf(TEXT("[DamageExecution C++] Damage Taken: %.1f | Target Health: %.1f/%.1f | Attack & Defence: %.1f/%.1f | Physical: %.1f | Magical: %.1f | Elemental: %.1f"),
    final_damage, health - final_damage, max_health, attack, defence, physical_damage, magical_damage, elemental_damage);
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, calc_damage_message);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *calc_damage_message);
}

