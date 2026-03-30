// Copyright - Javackson Studio


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
	Spline = CreateDefaultSubobject<USplineComponent>("Spline"); 
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	
	SetInputMode(InputModeData);

	GetWorldTimerManager().SetTimer(CursorTraceTimerHandle, this, &AAuraPlayerController::CursorTrace, 0.1f, true);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UAuraInputComponent* EnhancedInputComponent = Cast<UAuraInputComponent>(InputComponent))
	{		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
		EnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	}
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);	
	
	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	/** 
	 *  Line trace from cursor. There are several scenarios:
	 *  A. LastActor is null && ThisActor is null
	 *   - Do nothing
	 *  B. LastActor is null && ThisActor is valid
	 *   - Call ThisActor->OnBeginCursorOver() - Highlight ThisActor
	 *  C. LastActor is valid && ThisActor is null
	 *   - Call LastActor->OnEndCursorOver() - UnHighlight LastActor
	 *  D. LastActor is valid && ThisActor is valid && LastActor != ThisActor
	 *   - Call LastActor->OnEndCursorOver() - UnHighlight LastActor
	 *   - Call ThisActor->OnBeginCursorOver() - Highlight ThisActor
	 *  E. LastActor is valid && ThisActor is valid && LastActor == ThisActor
	 *   - Do nothing
	 */
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Case B
			ThisActor->HighlightActor();
		}else
		{
			//Case A - Both are null, do nothing
		}
	}else
	{
		if (ThisActor == nullptr)
		{
			//Case C
			LastActor->UnHighlightActor();
		}else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				//Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}else
			{
				//Case E - Both actors are the same, do nothing
			}
		}
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);		
		}
		return;
	}
	
	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if ( UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
					//DrawDebugLine(GetWorld(), PointLoc, PointLoc + FVector(0.f, 0.f, 50.f), FColor::Red, false, 5.f, 2.f);
					//DrawDebugDirectionalArrow(GetWorld(), PointLoc, PointLoc + FVector(0.f, 0.f, 50.f), 25.f, FColor::Red, false, 5.f, 2.f, 2.f);
					//DrawDebugBox(GetWorld(), PointLoc, FVector(25.f), FColor::Red, false, 5.f, 2.f);
					//DrawDebugCapsule(GetWorld(), PointLoc, 25.f, 12	.f, FColor::Red, false, 5.f, 2.f, 2.f);
				}
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);		
		}
		return;
	}
	
	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection, 1.f);
		}
	
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}
