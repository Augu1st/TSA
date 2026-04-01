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
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Module);
		
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

namespace AttributeTags
{
	// Vital Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxHealth);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthNetFlow);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Armor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxArmor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ArmorNetFlow);
	// End of Vital Attributes
	
	// Core Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mastery);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reaction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Calculation);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Observation);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tenacity);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resonance);
	// End of Core Attributes
	
	// Combat Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CritRate);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CritDamage);
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(DodgeRate);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resist_Sturdy);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resist_Toughness);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resist_Stable);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resist_Reflect);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resist_Insulate_E);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resist_Insulate_H);
	// End of Combat Attributes
	
	// Resource Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Energy);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxEnergy);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EnergyNetFlow);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Matter);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxMatter);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MatterNetFlow);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ConversionRate);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ConversionSpeed);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrintSpeed);
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrintPower);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PropUseSpeed);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PropUseEfficiency);
	// End of Resource Attributes
	
}

namespace CombatTags
{
	namespace Attack
	{
		
	}
}

namespace StateTags
{
	// Converter State
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Convert_Idle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Convert_Working);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Convert_Locked);
}

namespace EventTags
{
	namespace Converter
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ItemToMatter);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ItemToEnergy);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(MatterToEnergy);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(EnergyToMatter);		
	}

}


namespace ItemBonds
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MartialSaint);
}
