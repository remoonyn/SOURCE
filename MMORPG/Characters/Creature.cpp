#include "Creature.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	MainAttributeSet = CreateDefaultSubobject<UMainAttributeSet>(TEXT("MainAttributeSet"));
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(AbilitySystemComponent))
		{
			//Задаем перменную при старте игры
			MainAttributeSet = AbilitySystemComponent->GetSet<UMainAttributeSet>();

			// Подписываемя на статы. Делегаты при изменении атрибутов в атрибут сете
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetHealthAttribute()).AddUObject(this, &ACreature::Health_Changed);
		}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ACreature::Health_Changed(const FOnAttributeChangeData& Data)
{
	float health = Data.NewValue;
	Update_Health(health);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ACreature::Update_Health_Implementation(const float NewHealth)
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------