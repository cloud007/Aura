// Copyright - Javackson Studio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraStruct.generated.h"

USTRUCT(BlueprintType)
struct FWigetControllerParams
{
	GENERATED_BODY()
	
	FWigetControllerParams(){}
	FWigetControllerParams(
		APlayerController *InPlayerController, 
		APlayerState *InPlayerState,
		UAbilitySystemComponent *InAbilitySystemComponent,
		UAttributeSet *InAttributeSet) : 
		PlayerController(InPlayerController),
		PlayerState(InPlayerState),
		AbilitySystemComponent(InAbilitySystemComponent),
		AttributeSet(InAttributeSet)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};