// ItemDataFunctionLibrary.cpp
#include "ItemDataFunctionLibrary.h"

// ============================================================
// 1. СОЗДАНИЕ InstancedStruct (НОВЫЙ СИНТАКСИС!)
// ============================================================

FInstancedStruct UItemDataFunctionLibrary::MakeInstancedStructFromQuantity(const FS_Item_Quantity& Data)
{
   // В UE 5.1+ используем FInstancedStruct::Make<T>()
   return FInstancedStruct::Make<FS_Item_Quantity>(Data);
}

FInstancedStruct UItemDataFunctionLibrary::MakeInstancedStructFromWeapon(const FS_Item_Attribute& Data)
{
   return FInstancedStruct::Make<FS_Item_Attribute>(Data);
}

// ============================================================
// 2. ПРОВЕРКА ТИПА
// ============================================================

bool UItemDataFunctionLibrary::IsInstancedStructQuantity(const FInstancedStruct& InstancedStruct)
{
   // Проверяем, содержит ли InstancedStruct данные типа FS_Item_Quantity
   return InstancedStruct.GetPtr<FS_Item_Quantity>() != nullptr;
}

bool UItemDataFunctionLibrary::IsInstancedStructAttribute(const FInstancedStruct& InstancedStruct)
{
   return InstancedStruct.GetPtr<FS_Item_Attribute>() != nullptr;
}

// ============================================================
// 3. ПОЛУЧЕНИЕ ДАННЫХ (распаковка)
// ============================================================

bool UItemDataFunctionLibrary::GetQuantityFromInstancedStruct(const FInstancedStruct& InstancedStruct, 
   FS_Item_Quantity& OutData)
{
   if (const FS_Item_Quantity* Data = InstancedStruct.GetPtr<FS_Item_Quantity>())
   {
      OutData = *Data;
      return true;
   }

   // Если тип не совпадает, возвращаем дефолтные значения
   OutData = FS_Item_Quantity();
   return false;
}

bool UItemDataFunctionLibrary::GetAttributeFromInstancedStruct(const FInstancedStruct& InstancedStruct, 
   FS_Item_Attribute& OutData)
{
   if (const FS_Item_Attribute* Data = InstancedStruct.GetPtr<FS_Item_Attribute>())
   {
      OutData = *Data;
      return true;
   }

   OutData = FS_Item_Attribute();
   return false;
}

// ============================================================
// 4. ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ
// ============================================================

//FString UItemDataFunctionLibrary::GetInstancedStructTypeName(const FInstancedStruct& InstancedStruct)
//{
//   if (!InstancedStruct.IsValid())
//   {
//      return TEXT("Invalid");
//   }
//
//   // Получаем имя типа
//   const UScriptStruct* ScriptStruct = InstancedStruct.GetStruct();
//   if (ScriptStruct)
//   {
//      return ScriptStruct->GetName();
//   }
//
//   return TEXT("Unknown");
//}