// ItemDataFunctionLibrary.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructUtils/InstancedStruct.h"
#include "Structures/MainStructures.h"
#include "ItemDataFunctionLibrary.generated.h"

// НЕ ОБЪЯВЛЯЙТЕ структуры здесь, если они уже есть в других файлах!
// Просто подключите заголовки с вашими структурами


// Если структуры лежат в разных файлах, подключите их все
// #include "Structures/ItemData/ItemQuantityStruct.h"
// #include "Structures/ItemData/ItemAttributeStruct.h"

UCLASS()
class MMORPG_API UItemDataFunctionLibrary : public UBlueprintFunctionLibrary
{
   GENERATED_BODY()

public:
   // ============================================================
   // 1. Функции для СОЗДАНИЯ InstancedStruct (НОВЫЙ СИНТАКСИС!)
   // ============================================================

   UFUNCTION(BlueprintCallable, Category = "Item Data|Create", 
      meta = (DisplayName = "Make InstancedStruct from Quantity"))
   static FInstancedStruct MakeInstancedStructFromQuantity(const FS_Item_Quantity& Data);

   UFUNCTION(BlueprintCallable, Category = "Item Data|Create", 
      meta = (DisplayName = "Make InstancedStruct from Attribute"))
   static FInstancedStruct MakeInstancedStructFromWeapon(const FS_Item_Attribute& Data);

   // ============================================================
   // 2. Функции для ПРОВЕРКИ типа
   // ============================================================

   UFUNCTION(BlueprintPure, Category = "Item Data|Check", 
      meta = (DisplayName = "Is InstancedStruct Quantity"))
   static bool IsInstancedStructQuantity(const FInstancedStruct& InstancedStruct);

   UFUNCTION(BlueprintPure, Category = "Item Data|Check", 
      meta = (DisplayName = "Is InstancedStruct Atrribute"))
   static bool IsInstancedStructAttribute(const FInstancedStruct& InstancedStruct);

   // ============================================================
   // 3. Функции для ПОЛУЧЕНИЯ данных (распаковка)
   // ============================================================

   UFUNCTION(BlueprintCallable, Category = "Item Data|Get", 
      meta = (DisplayName = "Get Quantity from InstancedStruct", 
         ExpandEnumAsExecs = "ReturnValue"))
   static bool GetQuantityFromInstancedStruct(const FInstancedStruct& InstancedStruct, 
      FS_Item_Quantity& OutData);

   UFUNCTION(BlueprintCallable, Category = "Item Data|Get", 
      meta = (DisplayName = "Get Attribute from InstancedStruct", 
         ExpandEnumAsExecs = "ReturnValue"))
   static bool GetAttributeFromInstancedStruct(const FInstancedStruct& InstancedStruct, 
      FS_Item_Attribute& OutData);

   // ============================================================
   // 4. Вспомогательная функция для получения типа как строки
   // ============================================================

   //UFUNCTION(BlueprintPure, Category = "Item Data|Check", 
   //   meta = (DisplayName = "Get InstancedStruct Type Name"))
   //static FString GetInstancedStructTypeName(const FInstancedStruct& InstancedStruct);
};