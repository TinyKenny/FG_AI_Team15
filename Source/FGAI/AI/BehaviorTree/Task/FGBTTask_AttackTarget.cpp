#include "FGBTTask_AttackTarget.h"
#include "FGAI/Components/FGDirectAttackComponent.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


UFGBTTask_AttackTarget::UFGBTTask_AttackTarget()
{
	NodeName = TEXT("FG Attack Target");
	bNotifyTick = true;
}

EBTNodeResult::Type UFGBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// reset attack cooldown timer
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UFGBTTask_AttackTarget::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UFGBTTask_AttackTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	// do literally nothing apparently
}

void UFGBTTask_AttackTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// attack logic and attack timer
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(!AIController)
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget attempted to tick with null AIController"));
		return;
	}

	APawn* PawnOwner = AIController->GetPawn();

	if (!PawnOwner)
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget attempted to tick with null pawn, AI controller is: %s"), *(AIController->GetName()))
		// return failed here?
		return;
	}

	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackboardComponent == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget called in behaviour tree for controller %s, with null blackboard component"), *(AIController->GetName()))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (AttackTarget.SelectedKeyType != UBlackboardKeyType_Object::StaticClass())
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget called in behaviour tree for controller %s, with attack target of incorrect type"), *(AIController->GetName()))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	AActor* TargetActor = GetAttackTargetActor(OwnerComp);
	if (TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget Target was null"))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UFGDirectAttackComponent* AttackComponent = Cast<UFGDirectAttackComponent>(PawnOwner->GetComponentByClass(UFGDirectAttackComponent::StaticClass()));
	if (AttackComponent == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget called in behaviour tree for pawn %s, which doesn't have an attack component"), *(PawnOwner->GetName()))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const bool AttackSuccessful = AttackComponent->PerformAttackOnTarget(TargetActor);

	if (!AttackSuccessful)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UFGBTTask_AttackTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	// check that blackboard keys are the right kind of stuff
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		AttackTarget.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UFGBTTask_AttackTarget::GetInstanceMemorySize() const
{
	return sizeof(FBTAttackTargetTaskMemory);
}

FString UFGBTTask_AttackTarget::GetStaticDescription() const
{
	FString Desc;
	FString WarningString;

	Desc += TEXT("Attack target: ");
	Desc += AttackTarget.SelectedKeyName.ToString();
	if (AttackTarget.SelectedKeyType != UBlackboardKeyType_Object::StaticClass())
	{
		WarningString += TEXT("\nWarning: Invalid attack target type, must be Object");
	}

	return Desc + WarningString;
}

AActor* UFGBTTask_AttackTarget::GetAttackTargetActor(UBehaviorTreeComponent& OwnerComp) const
{
	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (BlackboardComponent == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget called in behaviour tree for controller %s, with null blackboard component"), *(OwnerComp.GetAIOwner()->GetName()))
		
		return nullptr;
	}

	if (AttackTarget.SelectedKeyType != UBlackboardKeyType_Object::StaticClass())
	{
		UE_LOG(LogTemp, Log, TEXT("FGBTTask_AttackTarget called in behaviour tree for controller %s, with attack target of incorrect type"), *(OwnerComp.GetAIOwner()->GetName()))
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return nullptr;
	}

	//return nullptr;
	return Cast<AActor>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(AttackTarget.GetSelectedKeyID()));
}


