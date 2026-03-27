#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h" 

namespace ItemTags
{
	namespace Category
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(General);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Weapon);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Armor);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Prop);
		
		/* Collection Category */
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Information);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Art);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Wealth);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Technology);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Ritual);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Personal);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Warfare);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Natural);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Collection_Myth);
		/* End of Collection Category */
	}
	
}

namespace CombatTags
{
	namespace Attack
	{
		
	}
}

namespace AttributeTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Armor);
}

namespace ItemBonds
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MartialSaint);
}
