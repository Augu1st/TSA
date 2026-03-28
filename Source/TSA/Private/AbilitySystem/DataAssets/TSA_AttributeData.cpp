// Dark Trace Studio Works


#include "AbilitySystem/DataAssets/TSA_AttributeData.h"

FTSA_AttributeInfo UTSA_AttributeData::FindInfoByTag(const FGameplayTag& Tag) const
{
	for (const FTSA_AttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == Tag)return Info;
	}
	return FTSA_AttributeInfo();
}


