#include "FGDirectAttackComponent.h"
#include "FGTakeDamageComponent.h"

#include "FGAI/Components/FGDirectAttackSettings.h"

UFGDirectAttackComponent::UFGDirectAttackComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UFGDirectAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentAttackCooldown -= DeltaTime;
}


bool UFGDirectAttackComponent::PerformAttackOnTarget(AActor* AttackTarget)
{
	AActor* OwningActor = GetOwner();
	if (AttackSettings == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s attempted to attack, but AttackSettings were null"), *OwningActor->GetName())
		return false;
	}

	if (AttackTarget == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s attempted to attack, but attack target was null"), *OwningActor->GetName())
		return false;
	}

	const FVector OwnerLocation = OwningActor->GetActorLocation();
	const FVector TargetLocation = AttackTarget->GetActorLocation();
	const float DistanceToTargetSq = FVector::DistSquared(OwnerLocation, TargetLocation);
	if (DistanceToTargetSq > AttackSettings->Range * AttackSettings->Range)
	{
		return false;
	}

	if (CurrentAttackCooldown > 0.0f)
	{
		return true;
	}

	CurrentAttackCooldown = AttackSettings->Cooldown;
	UE_LOG(LogTemp, Log, TEXT("Attack!"))

	
	UFGTakeDamageComponent* TargetTakeDamageComponent = Cast<UFGTakeDamageComponent>(AttackTarget->GetComponentByClass(UFGTakeDamageComponent::StaticClass()));
	if (TargetTakeDamageComponent != nullptr)
	{
		FFGDamageInfo DamageInfo;
		DamageInfo.DamageAmount = AttackSettings->Damage;
		DamageInfo.DamageInstigator = OwningActor;
		DamageInfo.DamageDirection = TargetLocation - OwnerLocation;
		DamageInfo.DamageImpactLocation = TargetLocation;
		TargetTakeDamageComponent->OnTakeDamage(DamageInfo);
	}
	
	
	return true;
}
