#include "TSA_GameplayTags.h"

namespace ItemTags
{
	namespace Category
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(General,"Item.Category.General","通用物品标签");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Equipment,"Item.Category.Equipment","装备根标签");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Equipment_Weapon,"Item.Category.Equipment.Weapon","装备-武器");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Equipment_Armor,"Item.Category.Equipment.Armor","装备-防具");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Prop,"Item.Category.Prop","道具根标签");
		
		/* Collection Category */
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection,"Item.Category.Collection","收集品根标签");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Information, "Item.Category.Collection.Information", "文献与信息");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Art, "Item.Category.Collection.Art", "艺术与娱乐");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Wealth, "Item.Category.Collection.Wealth", "财富与商业");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Technology, "Item.Category.Collection.Technology", "科技与生产");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Ritual, "Item.Category.Collection.Ritual", "信仰与仪式");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Personal, "Item.Category.Collection.Personal", "日常与家居");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Warfare, "Item.Category.Collection.Warfare", "战争与荣誉");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Natural, "Item.Category.Collection.Natural", "自然与遗迹");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collection_Myth,"Item.Category.Collection.Myth", "神话与幻想");
		/* End of Collection Category */
		
	}
}

namespace AttributeTags
{
	// Vital Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health,"Attribute.Vital.Health","生命值");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxHealth,"Attribute.Vital.MaxHealth","最大生命值");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(HealthNetFow,"Attribute.Vital.HealthNetFlow","生命值变化率")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Armor,"Attribute.Vital.Armor","护甲值");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxArmor,"Attribute.Vital.MaxArmor","最大护甲值");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(ArmorNetFlow,"Attribute.Vital.ArmorNetFlow","护甲值变化率")
	// End of Vital Attributes
	
	// Core Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Mastery,"Attribute.Core.Mastery","掌控");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Reaction,"Attribute.Core.Reaction","反应");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Calculation,"Attribute.Core.Calculation","计算");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Observation,"Attribute.Core.Observation","观察");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tenacity,"Attribute.Core.Tenacity","坚韧");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resonance,"Attribute.Core.Resonance","共鸣")
	// End of Core Attributes
	
	// Combat Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(CritRate,"Attribute.Combat.CritRate","暴击率");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(CritDamage,"Attribute.Combat.CritDamage","暴击伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(DodgeRate,"Attribute.Combat.DodgeRate","闪避率");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resist_Sturdy,"Attribute.Combat.Resist.Sturdy","坚固");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resist_Toughness,"Attribute.Combat.Resist.Toughness","韧性");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resist_Stable,"Attribute.Combat.Resist.Stable","稳定");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resist_Reflect,"Attribute.Combat.Resist.Reflect","反射");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resist_Insulate_E,"Attribute.Combat.Resist.Insulate.E","绝缘");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resist_Insulate_H,"Attribute.Combat.Resist.Insulate.H","隔热");
	// End of Combat Attributes
	
	// Resource Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Energy,"Attribute.Resource.Energy","能量");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxEnergy,"Attribute.Resource.MaxEnergy","最大能量");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(EnergyNetFlow,"Attribute.Resource.EnergyNetFlow","能量变化率")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Matter,"Attribute.Resource.Matter","物质量");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxMatter,"Attribute.Resource.MaxMatter","最大物质量");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MatterNetFlow,"Attribute.Resource.MatterNetFlow","物质变化率")
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(ConversionRate,"Attribute.Resource.ConversionRate","转换率");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(ConversionSpeed,"Attribute.Resource.ConversionSpeed","转换速度");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(PrintSpeed,"Attribute.Resource.PrintSpeed","打印速度");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(PrintPower,"Attribute.Resource.PrintPower","打印功率");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(PropUseSpeed,"Attribute.Resource.PropUseSpeed","道具使用速度");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(PropUseEfficiency,"Attribute.Resource.PropUseEfficiency","道具使用效率");
	// End of Resource Attributes
}

namespace CombatTags
 {
 	namespace Attack
 	{
 		
 	}
 }