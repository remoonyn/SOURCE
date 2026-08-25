
#include "ItemsContainer.h"
#include "MainCharacter.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
UItemsContainer::UItemsContainer()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UItemsContainer, Items_Container, COND_OwnerOnly);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UItemsContainer::TryAddSlot()
{
	if (Items_Container.Num() < Max_Slots)
	{
		Items_Container.SetNum(Items_Container.Num() + 1);
		Calc_Slots_Value_UI();
		return true;
	}
	else
	{
		FString string = FString::Printf(TEXT("Достигнуто максимальное количество слотов = %d. Дальнейшее увеличение невозможно!"), Max_Slots);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, string);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
		return false;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Add_Item(FS_Item_Container item)
{
	bool find_empty_slot;
	int32 index_empty_slot;
	int32 index_item = item.Index;
	int32 quantity = item.Quantity;
	int32 stacksize = item.Stacksize;
	EGradeType item_grade_type = item.Grade;

	FS_Item_Container add_item = item;

	if (stacksize > 0 && quantity <= stacksize)
	{
		bool found_item = false;
		int32 found_item_index_slot = 0;
		int32 found_item_quantity = 0;

		// Памятка новичку. Цикл while прерывается с помощью break при необходимости. В данном случае если мы не находим одиниковых предметов для "складывания" в одну пачку мы выходим из цикла.
		while (quantity > 0)
		{
			Find_Item_With_Space_In_Stack(index_item, item_grade_type, found_item, found_item_index_slot, found_item_quantity);
			if (!found_item)
			{
				if (quantity <= stacksize)
				{
					item.Quantity = quantity;
					break;
				}
			}

			if (found_item_quantity + quantity <= stacksize)
			{
				Stack_Item(found_item_index_slot, quantity);
				return;
			}

			else if (found_item_quantity + quantity > stacksize)
			{
				int32 left_to_stack_quantity = stacksize - found_item_quantity;
				quantity = quantity - left_to_stack_quantity;
				Stack_Item(found_item_index_slot, left_to_stack_quantity);
			}
		}
	}

	Find_Empty_Slot(index_empty_slot, find_empty_slot);
	if (find_empty_slot)
	{
		// Памятка новичку. Array[index] - задаем новый элемент массива по индексу.
		Items_Container[index_empty_slot] = item;
		Update_Slot_UI(index_empty_slot);
	}
	else 
	{
		// В будущем вывести виджет уведомления о том что нет слотов!
		FString string = FString::Printf(TEXT("No empty slots available! Container is full."));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, string);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
	}
	Calc_Slots_Value_UI();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Remove_Item(int32 index)
{
	Items_Container[index] = FS_Item_Container();
	Reset_Slot_UI(index);
	Calc_Slots_Value_UI();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UItemsContainer::Check_Required_Items(UItemsContainer* additional_container, TArray<FST_Item_Required> items_required)
{
	TArray<bool> all_items_found;
	
	//Проверяем каждый требуемый предмет в обоих контейнерах.
	for (int32 i = 0; i < items_required.Num(); i++)
	{
		FST_Item_Required curr_required_item = items_required[i];
		int32 needed_quantity = curr_required_item.Quantity;
		int32 sum_quantity = 0;

		//Проверяем требуемый предмет в текущем контейнере.
		for (int32 y = 0; y < Items_Container.Num(); y++)
		{
			FS_Item_Container& container_item = Items_Container[y];
			if (curr_required_item.Index == container_item.Index)
			{
				sum_quantity += container_item.Quantity;

				if (sum_quantity >= needed_quantity)
				{
					break;
				}
			}
		}

		//Проверка требуемого предмета в дополнительном контейнере.
		if (sum_quantity < needed_quantity && additional_container != nullptr)
		{
			TArray<FS_Item_Container>& add_containers = additional_container->Items_Container;

			for (int32 p = 0; p < add_containers.Num(); p++)
			{
				FS_Item_Container& additional_item = add_containers[p];
				if (curr_required_item.Index == additional_item.Index)
				{
					sum_quantity += additional_item.Quantity;

					if (sum_quantity >= needed_quantity)
					{
						break;
					}
				}
			}
		}

		// Если после всех проверок не хватает - возвращаем false
		if (sum_quantity < needed_quantity)
		{
			return false;
		}
	}

	return true;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UItemsContainer::Check_Empty_Slots(int32 slots_needed) const
{
	int32 empty_slots_count = 0;
	int32 index_empty_slot = 0;
	bool find_empty_slot = false;

	for (int32 i = 0; i <= Items_Container.Num(); i++)
	{
		Find_Empty_Slot(index_empty_slot, find_empty_slot);
		if (find_empty_slot)
		{
			empty_slots_count++;
			if (empty_slots_count >= slots_needed)
			{
				return true;
			}
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Remove_Required_Items(UItemsContainer* additional_container, TArray<FST_Item_Required> items_required)
{
	// Обрабатываем каждый требуемый предмет
	for (int32 i = 0; i < items_required.Num(); i++)
	{
		FST_Item_Required curr_required_item = items_required[i];
		int32 needed_quantity = curr_required_item.Quantity;
		int32 remaining_to_remove = needed_quantity;

		// Сначала вычитаем из текущего контейнера
		for (int32 y = 0; y < Items_Container.Num() && remaining_to_remove > 0; y++)
		{
			FS_Item_Container& container_item = Items_Container[y];
			if (curr_required_item.Index == container_item.Index)
			{
				int32 available_in_slot = container_item.Quantity;

				if (available_in_slot <= remaining_to_remove)
				{
					// Обнуляем слот при нулевом остатке
					remaining_to_remove -= available_in_slot;
					Remove_Item(y);
				}
				else
				{
					// Уменьшаем количество в слоте
					container_item.Quantity -= remaining_to_remove;
					Update_Slot_UI(y); // Обновляем UI после изменения количества
					remaining_to_remove = 0;
					break;
				}
			}
		}

		// Если осталось что-то вычесть - вычитаем из дополнительного контейнера
		if (remaining_to_remove > 0 && additional_container != nullptr)
		{
			TArray<FS_Item_Container>& add_containers = additional_container->Items_Container;

			for (int32 p = 0; p < add_containers.Num() && remaining_to_remove > 0; p++)
			{
				FS_Item_Container& additional_item = add_containers[p];
				if (curr_required_item.Index == additional_item.Index && additional_item.Quantity > 0)
				{
					int32 available_in_slot = additional_item.Quantity;

					if (available_in_slot <= remaining_to_remove)
					{
						// Удаляем весь слот из дополнительного контейнера
						remaining_to_remove -= available_in_slot;
						additional_container->Remove_Item(p);
					}
					else
					{
						// Уменьшаем количество в слоте
						additional_item.Quantity -= remaining_to_remove;
						additional_container->Update_Slot_UI(p); // Обновляем UI дополнительного контейнера
						remaining_to_remove = 0;
						break;
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UItemsContainer::Check_Items_Quantity(int32 index_item, int32 quantity_remove)
{
	int32 total_quantity = 0;

	for (int32 i = 0; i < Items_Container.Num(); i++)
	{
		FS_Item_Container& item = Items_Container[i];
		if (item.Index == index_item)
		{
			total_quantity += item.Quantity;

			// Как только набрали достаточно - возвращаем true
			if (total_quantity >= quantity_remove)
			{
				return true;
			}
		}
	}

	// Прошли все слоты, но сумма меньше нужного количества
	return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Remove_Items_Quantity(int32 index_item, int32 quantity_remove)
{
	if (quantity_remove <= 0 || index_item <= 0) return;

	int32 remaining_to_remove = quantity_remove;

	for (int32 i = 0; i < Items_Container.Num(); i++)
	{
		FS_Item_Container& item = Items_Container[i];
		if (item.Index == index_item && remaining_to_remove > 0)
		{
			if (item.Quantity > remaining_to_remove)
			{
				item.Quantity -= remaining_to_remove;
				Update_Slot_UI(i);
				return;
			}

			else
			{
				remaining_to_remove -= item.Quantity;
				Remove_Item(i);
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Remove_Items_Quantity_With_Grade(int32 index_item, EGradeType grade_type, int32 quantity_remove)
{
	if (quantity_remove <= 0 || index_item <= 0) return;

	int32 remaining_to_remove = quantity_remove;

	for (int32 i = 0; i < Items_Container.Num(); i++)
	{
		FS_Item_Container& item = Items_Container[i];
		if (item.Index == index_item && remaining_to_remove > 0 && item.Grade == grade_type)
		{
			if (item.Quantity > remaining_to_remove)
			{
				item.Quantity -= remaining_to_remove;
				Update_Slot_UI(i);
				return;
			}

			else
			{
				remaining_to_remove -= item.Quantity;
				Remove_Item(i);
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Transfer_Item(UItemsContainer* target_container, int32 index_from)
{
	int32 index_empty_slot;
	bool find_empty_slot;

	if (target_container)
	{
		target_container->Find_Empty_Slot(index_empty_slot, find_empty_slot);
	}

	if (find_empty_slot)
	{
		FS_Item_Container add_item = Items_Container[index_from];
		target_container->Add_Item(add_item);
		Remove_Item(index_from);
		Calc_Slots_Value_UI();
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Drag_And_Drop_Item(int32 index_drop, int32 index_from, UItemsContainer* from_container)
{
	FS_Item_Container& item_new = Items_Container[index_drop];
	FS_Item_Container& item_ref = from_container->Items_Container[index_from];
	
	// Сразу отсекаем бессмысленные варианты попыток переноса пустых слотов и предмета в тот же слот
	if (item_ref.Index != 0 && index_drop != index_from)
	{
		// Переносим предмет в целевой пустой слот с удалением предмета из старого контейнера и обновляем UI.
		if (item_new.Index == 0)
		{
			item_new = item_ref;
			Update_Slot_UI(index_drop);
			from_container->Remove_Item(index_from);
			Calc_Slots_Value_UI();
			return;
		}

		// Меняем местами разные предметы если они: 1. Разные по индексу. 2. Разные по грейду. 3. Или если они одинаковые по индексу но при этом лимит стаков для них 1, то есть они не стакаются. Меньше или равно 1 - это защита от дизайнерской ошибки, когда в данных предмета указывается размер стака 0 или 1, что по сути означает что предмет не стакается.
		if (item_new.Index != item_ref.Index || item_new.Grade != item_ref.Grade || (item_new.Index == item_ref.Index && item_ref.Stacksize <= 1))
		{
			FS_Item_Container item_save = item_ref;
			item_ref = item_new;
			item_new = item_save;
			Update_Slot_UI(index_drop);
			from_container->Update_Slot_UI(index_from);
			Calc_Slots_Value_UI();
			return;
		}

		// Складываем одинаковые предметы если предметы могут складываться
		if (item_new.Index == item_ref.Index && item_ref.Stacksize > 1)
		{
			int32 left_quantity_to_stack = item_new.Stacksize - item_new.Quantity;
			
			if (item_ref.Quantity <= left_quantity_to_stack)
			{
				item_new.Quantity += item_ref.Quantity;
				Update_Slot_UI(index_drop);
				from_container->Remove_Item(index_from);
				Calc_Slots_Value_UI();
				return;
			}

			if (item_ref.Quantity > left_quantity_to_stack)
			{
				item_ref.Quantity -= left_quantity_to_stack;
				item_new.Quantity = item_new.Stacksize;
				Update_Slot_UI(index_drop);
				from_container->Update_Slot_UI(index_from);
				Calc_Slots_Value_UI();
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Stack_Item(int32 index_slot, int32 add_quantity)
{
	// Памятка новичку. Символ & работает как ссылка на объект. Изменяя в коде значения они автоматически изменяются в объекте. Не нужно копировать и перезаписывать объект. Следовательно отсутвие накладных расходов на копирование.
	FS_Item_Container& stacking_item = Items_Container[index_slot];
	stacking_item.Quantity = stacking_item.Quantity + add_quantity;
	Update_Slot_UI(index_slot);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Split_Stack(int32 index_slot)
{
	bool find_empty_slot = false;
	int32 index_empty_slot = -1;

	Find_Empty_Slot(index_empty_slot, find_empty_slot);
	if (find_empty_slot)
	{
		FS_Item_Container& item_to_split = Items_Container[index_slot];
		int32 quantity_original = item_to_split.Quantity;
		int32 quantity_to_move = quantity_original / 2;

		if (quantity_original > 1 && quantity_to_move > 0)
		{
			// Делаем копию оригинально предмета с оригинальным количество
			Items_Container[index_empty_slot] = item_to_split;
			// Задаем новому предмету значение остатка 
			Items_Container[index_empty_slot].Quantity = quantity_to_move;
			// Вычитаем из оригинального предмета количество
			item_to_split.Quantity -= quantity_to_move;
			Update_Slot_UI(index_slot);
			Update_Slot_UI(index_empty_slot);
			Calc_Slots_Value_UI();
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Move_All_Items(UItemsContainer* from_container)
{
	if (!IsValid(from_container))
	{
		return;
	}

	TArray<FS_Item_Container>& items_ref = from_container->Items_Container;
	for (int32 i = 0; i < items_ref.Num(); i++)
	{
		FS_Item_Container& item_ref = items_ref[i];
		if (item_ref.Index != 0)
		{
			bool find_empty_slot = false;
			int32 index_empty_slot = 0;
			Find_Empty_Slot(index_empty_slot, find_empty_slot);
			if (find_empty_slot)
			{
				Add_Item(item_ref);
				from_container->Remove_Item(i);
			}
			else
			{
				break;
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Move_Identical_Items(UItemsContainer* from_container)
{
	if (!IsValid(from_container))
	{
		return;
	}
	TArray<FS_Item_Container>& items_ref = from_container->Items_Container;
	for (int32 i = 0; i < items_ref.Num(); i++)
	{
		FS_Item_Container& item_ref = items_ref[i];
		if (item_ref.Index != 0)
		{
			for (int32 y = 0; y < Items_Container.Num(); y++)
			{
				FS_Item_Container& item_target = Items_Container[y];

				bool found_identical_item = false;
				if (item_ref.Index == item_target.Index)
				{
					found_identical_item = true;
				}
				if (found_identical_item)
				{
					bool find_empty_slot = false;
					int32 index_empty_slot = 0;
					Find_Empty_Slot(index_empty_slot, find_empty_slot);
					if (find_empty_slot)
					{
						Add_Item(item_ref);
						from_container->Remove_Item(i);
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Find_Empty_Slot(int32& index_empty_slot, bool& find_empty_slot) const
{
	index_empty_slot = -1;
	find_empty_slot = false;
	TArray<FS_Item_Container> slots = this->Items_Container;

	for (int32 array_index = 0; array_index < slots.Num(); array_index++)
	{
		const FS_Item_Container& array_element = slots[array_index];

		if (array_element.Index == 0)
		{
			index_empty_slot = array_index;
			find_empty_slot = true;
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Find_Item_With_Space_In_Stack(int32 index_item, EGradeType grade_type, bool& find_item, int32& index_slot, int32& item_quantity)
{
	find_item = false;
	index_slot = 0;
	item_quantity = 0;
	EGradeType item_grade_item = grade_type;

	for (int32 array_index = 0; array_index < Items_Container.Num(); array_index++)
	{
		const FS_Item_Container& array_element = Items_Container[array_index];

		if (array_element.Index == index_item && array_element.Quantity < array_element.Stacksize && array_element.Grade == item_grade_item)
		{
			find_item = true;
			item_quantity = array_element.Quantity;
			index_slot = array_index;
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
int32 UItemsContainer::Calc_Items(int32 item_quantity_in_stack, int32 item_stacksize) const
{
	if (item_stacksize <= 0) return 0;
	return (item_quantity_in_stack + item_stacksize - 1) / item_stacksize;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Calc_Slots_Value_UI()
{
	if (Container_Type == EContainerType::Backpack || Container_Type == EContainerType::Storage)
	{
		int32 curr_slots = 0;

		// Используем const& чтобы избежать копирования.
		const TArray<FS_Item_Container>& slots = this->Items_Container;

		// Если не нужен индекс. Так называемый range-based for loop.
		for (const auto& item : slots)
		{
			curr_slots += (item.Index != 0);
		}
		AActor* actor_owner = GetOwner();
		AMainCharacter* character_owner = Cast<AMainCharacter>(actor_owner);
		character_owner->Update_Container_Slots_Value_UI(Container_Type, curr_slots, slots.Num());
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Update_Slot_UI(int32 index_update_slot)
{
	AActor* actor_owner = GetOwner();
	AMainCharacter* character_owner = Cast<AMainCharacter>(actor_owner);
	character_owner->Update_Container_Slot_UI(index_update_slot, Container_Type, Items_Container[index_update_slot]);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Reset_Slot_UI(int32 index_reset_slot)
{
	AActor* actor_owner = GetOwner();
	AMainCharacter* character_owner = Cast<AMainCharacter>(actor_owner);
	character_owner->Reset_Container_Slot_UI(index_reset_slot, Container_Type);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UItemsContainer::Sort_Items_By_Index(UPARAM(ref)TArray<FS_Item_Container>& Items)
{
	Items.Sort([](const FS_Item_Container& A, const FS_Item_Container& B)
		{
			// Если A — пустой слот (Index == 0), а B — нет, то A должен идти ПОСЛЕ B
			if (A.Index == 0 && B.Index != 0) return false;
			// Если B — пустой слот, а A — нет, то A должен идти ПЕРЕД B
			if (A.Index != 0 && B.Index == 0) return true;
			// Если оба непустые (или оба пустые) — сортируем по возрастанию индекса
			return A.Index < B.Index;
		});
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
