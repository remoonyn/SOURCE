#include "Profession.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
UProfession::UProfession()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UProfession::Check_Empty_Crafting_Slot(int32& index_empty_slot)
{
	for (int32 i = 0; i < Crafting_Slots.Num(); i++)
	{
		FS_Craft_Slot& curr_slot = Crafting_Slots[i];
		if (!curr_slot.Slot_Craft_Take)
		{
			index_empty_slot = i;
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UProfession::Check_Learning_Recipe(int32 index_recipe)
{
	if (Learning_Recipes.Num() == 0)
	{
		return false;
	}

	for (int32 i = 0; i < Learning_Recipes.Num(); i++)
	{
		FS_Learning_Recipe& curr_recipe = Learning_Recipes[i];
		if (curr_recipe.Index_Recipe == index_recipe && curr_recipe.Learned)
		{
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------