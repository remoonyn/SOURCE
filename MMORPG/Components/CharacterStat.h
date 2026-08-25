#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStat.generated.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup=(CharacterStat), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class MMORPG_API UCharacterStat : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion") float Chance_Potion_T5 = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion") float Chance_Potion_T4 = 5.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion") float Chance_Potion_T3 = 10.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion") float Chance_Potion_T2 = 20.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food") float Chance_Food_T5 = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food") float Chance_Food_T4 = 5.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food") float Chance_Food_T3 = 10.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food") float Chance_Food_T2 = 20.0;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------