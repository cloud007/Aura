// Copyright - Javackson Studio


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse *MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	//Get Local under the mouse cursor, draw debug sphere at the location in the ability
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorResult;
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorResult);
		if (CursorResult.bBlockingHit)
		{
			//draw debug sphere at the location
			DrawDebugSphere(GetWorld(), CursorResult.ImpactPoint, 100.f, 12, FColor::White, false, 10.f);
			ValidData.Broadcast(CursorResult.ImpactPoint);
		}
	}
}
