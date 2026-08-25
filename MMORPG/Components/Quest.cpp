#include "Quest.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
UQuest::UQuest()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void UQuest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(UQuest, Quest_Active,           COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UQuest, Quest_Completed,        COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UQuest, Quest_Completed_Daily,  COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UQuest, Quest_Completed_Weakly, COND_OwnerOnly);
    DOREPLIFETIME_CONDITION(UQuest, Quest_Active_Progress,  COND_OwnerOnly);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
