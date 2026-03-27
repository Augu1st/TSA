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

namespace CombatTags
{
	namespace Attack
	{
		
	}
}

namespace AttributeTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health,"Attribute.Vital.Health","生命值");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Armor,"Attribute.Vital.Armor","护甲值");
}