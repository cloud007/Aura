
#include "AuraAbilityTypes.h"

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);

	uint8 RepBits = 0;
	if (Ar.IsSaving())
	{
		if (bIsBlockedHit)  RepBits |= 1 << 0;
		if (bIsCriticalHit) RepBits |= 1 << 1;
	}

	Ar.SerializeBits(&RepBits, 2);

	if (Ar.IsLoading())
	{
		bIsBlockedHit  = (RepBits & (1 << 0)) != 0;
		bIsCriticalHit = (RepBits & (1 << 1)) != 0;
	}

	bOutSuccess = true;
	return true;
}
