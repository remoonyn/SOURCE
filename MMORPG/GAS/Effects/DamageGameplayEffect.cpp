#include "DamageGameplayEffect.h"
#include "MMORPG\GAS\Effects\Execution\DamageExecution.h"

UDamageGameplayEffect::UDamageGameplayEffect()
{
    // Говорим, что это мгновенный эффект (не с течением времени)
   DurationPolicy = EGameplayEffectDurationType::Instant;

    //// НАСТРАИВАЕМ EXECUTION - ЭТО ГЛАВНОЕ!
    FGameplayEffectExecutionDefinition ExecutionDef;
    ExecutionDef.CalculationClass = UDamageExecution::StaticClass(); // Ваш класс расчета
    Executions.Add(ExecutionDef);
}