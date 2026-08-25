#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enumerations/MainEnumerations.h"
#include "Structures/MainStructures.h"
#include "Net/UnrealNetwork.h"
#include "ItemsContainer.generated.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup=(Container), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class MMORPG_API UItemsContainer : public UActorComponent
{
	GENERATED_BODY()

public:	

	UItemsContainer();
	// Репликация
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//Пытаемся увеличить количество слотов на один.
	bool TryAddSlot();
	//Геймпленое добавление предметов при различных активностях: фарм, сбор, крафт и т.д.
	UFUNCTION(BlueprintCallable, Category = "Container") void Add_Item(FS_Item_Container item);
	//Удаляем предмет из слота с обновление виджета.
	UFUNCTION(BlueprintCallable, Category = "Container") void Remove_Item(int32 index);
	//Вычитаем необходимое количество предметов. Для одного контейнера. Без проверки на нужное количество! Подразумевается предварительная проверка другим методом.
	UFUNCTION(BlueprintCallable, Category = "Container") void Remove_Items_Quantity(int32 index_item, int32 quantity_remove);
	//Вычитаем необходимое количество предметов. Для одного контейнера. С проверкой на необходимый грейд предмета.
	UFUNCTION(BlueprintCallable, Category = "Container") void Remove_Items_Quantity_With_Grade(int32 index_item, EGradeType grade_type, int32 quantity_remove);
	//Удаление требуемых ресурсов из инвентаря.
	UFUNCTION(BlueprintCallable, Category = "Container") void Remove_Required_Items(UItemsContainer* additional_container, TArray<FST_Item_Required> items_required);
	//Проверяем наличие предмета и его количества. Для одного контейнера.
	UFUNCTION(BlueprintCallable, Category = "Container") bool Check_Items_Quantity(int32 index_item, int32 qunatity_needed);
	//Проверка и трата ресурсов для: крафт, улучшения и прочего.
	UFUNCTION(BlueprintCallable, Category = "Container") bool Check_Required_Items(UItemsContainer* additional_container, TArray<FST_Item_Required> items_required);
	//Проверка наличия нужного количества пустых слотов для добавления нескольких предметов или предмета с количества больше размера пачки.
	UFUNCTION(BlueprintCallable, Category = "Container") bool Check_Empty_Slots(int32 slots_needed) const;
	//Перенос предмета при дабл клике на слоте контейнера, логика выбора контейнера вынесена в виджете "Inventory Slot".
	UFUNCTION(BlueprintCallable, Category = "Container") void Transfer_Item(UItemsContainer* target_container, int32 index_from);
	//Drag & Drop метод с логикой замены разных предметом местами и складыванимем в стопу одинаковых предметов. Для всех контейнеров кроме "Equipment".
	UFUNCTION(BlueprintCallable, Category = "Container") void Drag_And_Drop_Item(int32 index_target, int32 index_from, UItemsContainer* from_container);
	//Складываем два предмета. Если: одиниковые по индексу и стакуемые.
	UFUNCTION(BlueprintCallable, Category = "Container") void Stack_Item(int32 index_slot, int32 add_quantity);
	//Разделяем стак на два предмета в одном контейнере. Если: больше одного и есть пустые слоты.
	UFUNCTION(BlueprintCallable, Category = "Container") void Split_Stack(int32 index_slot);
	//Переносим все предметы из другого контейнера.
	UFUNCTION(BlueprintCallable, Category = "Container") void Move_All_Items(UItemsContainer* from_container);
	//Переносим все идентичные предметы из другого контейнера.
	UFUNCTION(BlueprintCallable, Category = "Container") void Move_Identical_Items(UItemsContainer* from_container);
	//Компилятор предложил сделал метод с const, так как он не изменяет члены данных класса
	UFUNCTION(BlueprintCallable, Category = "Container") void Find_Empty_Slot(int32& index_empty_slot, bool& find_empty_slot) const;
	//Поиск нужного предмета с полным стаком в инвентаре. Вспомогательный метод для основного метода Add_Item.
	UFUNCTION(BlueprintCallable, Category = "Container") void Find_Item_With_Space_In_Stack(int32 index_item, EGradeType grade_type, bool& find_item, int32& index_slot, int32& item_quantity);
	//Расчет количества слотов для добавления предметов.
	UFUNCTION(BlueprintCallable, Category = "Container") int32 Calc_Items(int32 item_quantity_in_stack, int32 item_stacksize) const;
	//Расчет занятых слотов в инвентаре. Например 37/75 слотов заняты предметами.
	UFUNCTION(BlueprintCallable, Category = "Container") void Calc_Slots_Value_UI();
	//Обновление предмета в слоте контейнера по типам.
	UFUNCTION(BlueprintCallable, Category = "Container") void Update_Slot_UI(int32 index_update_slot);
	//Сброс слота контейнера в состояние "пустой слот".
	UFUNCTION(BlueprintCallable, Category = "Container") void Reset_Slot_UI(int32 index_reset_slot);
	// Сортировка предметов по индексу. UPARAM(ref) - позволяет изменить массив прямо в методе. 
	UFUNCTION(BlueprintCallable, Category = "Container") static void Sort_Items_By_Index(UPARAM(ref) TArray<FS_Item_Container>& Items);

	//Массив предметов. По умолчанию все пустые.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Container") TArray<FS_Item_Container> Items_Container;
	//Используем чтобы определять с каким контейнером хотим взаимодействовать.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container") EContainerType Container_Type = EContainerType::None;
	//Максимально возможное количество слотов в контейнере.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container") int32 Max_Slots;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
