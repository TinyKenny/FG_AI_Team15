#include "FGHealthComponent.h"


void UFGHealthComponent::ChangeHitpointsByAmount(float ChangeAmount)
{
	HealthPoints += ChangeAmount;
	if (HealthPoints <= 0.0f)
	{
		OnReachZeroHealth.Broadcast();
	}
}
