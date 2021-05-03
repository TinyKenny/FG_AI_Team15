#include "FGTakeDamageComponent.h"
#include "FGHealthComponent.h"

void UFGTakeDamageComponent::OnTakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator) const
{
	UFGHealthComponent* HealthComponent = Cast<UFGHealthComponent>(GetOwner()->GetComponentByClass(UFGHealthComponent::StaticClass()));
	if (HealthComponent != nullptr)
	{
		HealthComponent->ChangeHitpointsByAmount(-Damage);
	}
}

void UFGTakeDamageComponent::OnTakeDamage(const FFGDamageInfo& DamageInfo) const
{
	UFGHealthComponent* HealthComponent = Cast<UFGHealthComponent>(GetOwner()->GetComponentByClass(UFGHealthComponent::StaticClass()));
	if (HealthComponent != nullptr)
	{
		HealthComponent->ChangeHitpointsByAmount(-DamageInfo.DamageAmount);
	}
}
