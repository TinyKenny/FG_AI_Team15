#include "FGBTTask_RotateToTarget.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "FGAI/FGUtilityStatics.h"

UFGBTTask_RotateToTarget::UFGBTTask_RotateToTarget()
{
	NodeName = TEXT("Smooth Rotate To Target");
	bNotifyTick = true;
}

EBTNodeResult::Type UFGBTTask_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UFGBTTask_RotateToTarget::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UFGBTTask_RotateToTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{

}

void UFGBTTask_RotateToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTFaceDirectionTaskMemory* FaceDirectionMemory = (FBTFaceDirectionTaskMemory*)NodeMemory;

	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return;

	APawn* PawnOwner = AIController->GetPawn();

	if (!PawnOwner)
		return;

	bool bSuccess = false;
	const FVector TargetLocation = GetTargetLocation(OwnerComp, bSuccess);

	if (!bSuccess)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
		

	const FVector DirectionToTarget = (TargetLocation - PawnOwner->GetActorLocation()).GetSafeNormal();
	FQuat Rot = FQuat::Slerp(PawnOwner->GetActorQuat(), DirectionToTarget.ToOrientationQuat(), DeltaSeconds * GetRotationSpeed(OwnerComp));

	FRotator NewRot = Rot.Rotator();
	NewRot.Pitch = 0.0f;
	NewRot.Roll = 0.0f;

	PawnOwner->SetActorRotation(NewRot);

	if (FMath::IsNearlyEqual(DirectionToTarget.Rotation().Yaw, NewRot.Yaw, AcceptableTolerance))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UFGBTTask_RotateToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		TargetLocationEntry.ResolveSelectedKey(*BBAsset);

		if (RotationSpeedEntryType == EFGSmoothFaceDirectionSpeedType::BBEntry)
			RotationSpeedBlackboard.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UFGBTTask_RotateToTarget::GetInstanceMemorySize() const
{
	return sizeof(FBTFaceDirectionTaskMemory);
}

FVector UFGBTTask_RotateToTarget::GetTargetLocation(const UBehaviorTreeComponent& OwnerComp, bool& bSuccess) const
{
	bSuccess = true;

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (BlackboardComp != nullptr)
	{
		if (TargetLocationEntry.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			UObject* TargetObject = BlackboardComp->GetValue<UBlackboardKeyType_Object>(TargetLocationEntry.GetSelectedKeyID());
			if (TargetObject != nullptr)
			{
				return CastChecked<AActor>(TargetObject)->GetActorLocation();
			}
		}
		else if (TargetLocationEntry.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			return BlackboardComp->GetValue<UBlackboardKeyType_Vector>(TargetLocationEntry.GetSelectedKeyID());
		}
	}

	bSuccess = false;

	return FVector::ZeroVector;
}

float UFGBTTask_RotateToTarget::GetRotationSpeed(const UBehaviorTreeComponent& OwnerComp) const
{
	if (RotationSpeedEntryType == EFGSmoothFaceDirectionSpeedType::BBEntry)
	{
		const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

		if (BlackboardComp && RotationSpeedBlackboard.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
		{
			return BlackboardComp->GetValue<UBlackboardKeyType_Float>(RotationSpeedBlackboard.GetSelectedKeyID());
		}
	}

	return RotationSpeedValue;
}
