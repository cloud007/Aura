// Copyright - Javackson Studio


#include "UI/HUD/AuraHUD.h"

void AAuraHUD::InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState,
                           UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	//checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(
		InPlayerController, 
		InPlayerState,
		InAbilitySystemComponent, 
		InAttributeSet);
	
	InitConfigurationWidgetControllers(WidgetControllerParams);
	
	UOverlayWidgetController* OverlayWC = GetConfigurationWidgetController<UOverlayWidgetController>();
	
	OverlayWidget->SetWidgetController(OverlayWC);
	
	OverlayWC->BroadcastInitialValues();
	
	Widget->AddToViewport();	
}

void AAuraHUD::InitConfigurationWidgetControllers(const FWidgetControllerParams& Params)
{
	for (FAuraConfigController& ConfigController : ConfigurationWidgetControllers)
	{
		if (ConfigController.WidgetController == nullptr && ConfigController.WidgetControllerClass)
		{
			ConfigController.WidgetController = NewObject<UAuraWidgetController>(this, ConfigController.WidgetControllerClass);
			ConfigController.WidgetController->SetWidgetControllerParams(Params);
			ConfigController.WidgetController->BindCallbacksToDependencies();
		}
	}
}
