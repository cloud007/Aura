// Copyright - Javackson Studio


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AtributeTag, bool bLogNotFound) const
{
	for ( const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AtributeTag))
		{
			return Info;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]"), *AtributeTag.ToString(), *GetNameSafe(this));
	}
	
	return FAuraAttributeInfo();
}
