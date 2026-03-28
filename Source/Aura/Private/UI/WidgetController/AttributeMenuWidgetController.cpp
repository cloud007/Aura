// Copyright - Javackson Studio


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo);

	for (const FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		if (const auto* FuncPtr = AuraAttributeSet->TagsToAttributes.Find(Info.AttributeTag))
		{
			const FGameplayAttribute Attribute = (*FuncPtr)();
			FAuraAttributeInfo InfoWithValue = Info;
			InfoWithValue.AttributeValue = Attribute.GetNumericValue(AuraAttributeSet);
			AttributeInfoDelegate.Broadcast(InfoWithValue);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find Attribute for Tag [%s] on AttributeMenuWidgetController [%s]"), *Info.AttributeTag.ToString(), *GetNameSafe(this));
		}
	}
}