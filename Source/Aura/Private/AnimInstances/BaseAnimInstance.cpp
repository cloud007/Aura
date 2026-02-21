// Copyright - Javackson Studio


#include "AnimInstances/BaseAnimInstance.h"


void UBaseAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AAuraCharacterBase>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UBaseAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	
	ShouldMove = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 3.f;
}