#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Creature.generated.h"

UCLASS()
class MMORPG_API ACreature : public ACharacter
{
	GENERATED_BODY()

public:
	ACreature();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void Health_Changed(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")  void Update_Health(const float NewHealth);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes") UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes") const UMainAttributeSet* MainAttributeSet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Creature_Name;
};
