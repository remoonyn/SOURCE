#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AttributeType.h"
#include "MainController.generated.h"


UCLASS()
class MMORPG_API AMainController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory") void Add_New_Container_Slot_UI(EContainerType container_type);

	UFUNCTION(BlueprintNativeEvent, Category = "Attribute") void Update_Attribute_UI(E_Attribute_Type attribute_type, float new_value);
	UFUNCTION(BlueprintNativeEvent, Category = "Attribute") void Update_Parameter_UI(E_Parameter_Type attribute_type, float new_value);
	UFUNCTION(BlueprintNativeEvent, Category = "Attribute") void Update_Parameter_Attribute_UI(E_Attribute_Parameter_Type attribute_type, float new_value);

	UFUNCTION(BlueprintNativeEvent, Category = "Toxicity") void Update_Toxicity_UI(float new_value);
	UFUNCTION(BlueprintNativeEvent, Category = "Toxicity") void Update_Max_Toxicity_UI(float new_value);
}; 