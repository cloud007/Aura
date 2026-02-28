// Copyright - Javackson Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraHUD.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	TSoftObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWigetControllerParams& Params);
	
	void InitOverlay(APlayerController *InPlayerController, 
		APlayerState *InPlayerState,
		UAbilitySystemComponent *InAbilitySystemComponent,
		UAttributeSet *InAttributeSet);
	
protected:
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
