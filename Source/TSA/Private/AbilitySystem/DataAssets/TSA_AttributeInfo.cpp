// Dark Trace Studio Works


#include "AbilitySystem/DataAssets/TSA_AttributeInfo.h"

FTSA_AttributeWithTag UTSA_AttributeInfo::FindInfoByTag(const FGameplayTag& Tag) const
{
	for (const FTSA_AttributeWithTag& Info : AttributeInformation)
	{
		if (Info.AttributeTag == Tag)return Info;
	}
	return FTSA_AttributeWithTag();
}


