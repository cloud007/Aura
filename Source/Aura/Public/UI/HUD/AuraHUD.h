// Copyright - Javackson Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AuraHUD.generated.h"

USTRUCT(BlueprintType)
struct FAuraConfigController
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<UAuraWidgetController> WidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraWidgetController> WidgetControllerClass;
};

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	template<typename T>
	T* GetWidgetController(const FWidgetControllerParams& Params);
	
	void InitOverlay(APlayerController *InPlayerController, 
		APlayerState *InPlayerState,
		UAbilitySystemComponent *InAbilitySystemComponent,
		UAttributeSet *InAttributeSet);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraConfigController> ConfigurationWidgetControllers;
	
protected:
	
private:
	
	UFUNCTION()
	void InitConfigurationWidgetControllers(const FWidgetControllerParams& Params);
	
	template <typename T>
	T* GetConfigurationWidgetController();
	
	UPROPERTY()
	TSoftObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};

template <typename T>
T* AAuraHUD::GetWidgetController(const FWidgetControllerParams& Params)
{
	for (const FAuraConfigController& ConfigController : ConfigurationWidgetControllers)
	{
		if (ConfigController.WidgetController && ConfigController.WidgetController->IsA<T>())
		{
			ConfigController.WidgetController->SetWidgetControllerParams(Params);
			ConfigController.WidgetController->BindCallbacksToDependencies();
			return Cast<T>(ConfigController.WidgetController);
		}
	}
	return nullptr;
}

template <typename T>
T* AAuraHUD::GetConfigurationWidgetController()
{
	for (const FAuraConfigController& ConfigController : ConfigurationWidgetControllers)
	{
		if (ConfigController.WidgetController && ConfigController.WidgetController->IsA<T>())
		{
			return Cast<T>(ConfigController.WidgetController);
		}
	}
	return nullptr;
}
