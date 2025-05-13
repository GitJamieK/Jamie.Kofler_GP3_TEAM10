// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GP_AttackTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/GP_AICharacter.h"

DEFINE_LOG_CATEGORY_STATIC(GP_AttackTaskLog, All, All);

UGP_AttackTask::UGP_AttackTask()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UGP_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Owner = Cast<AGP_AICharacter>(Controller->GetPawn());

	if (!Controller || !Blackboard || !Owner)
	{
		UE_LOG(GP_AttackTaskLog, Display, TEXT("!Controller || !Blackboard || !Owner : %s"), *Owner->GetName());
		return EBTNodeResult::Failed;
	}

	const auto HasTarget = Blackboard && Blackboard->GetValueAsObject(TargetActorKey.SelectedKeyName);
	if (HasTarget)
	{
		UE_LOG(GP_AttackTaskLog, Display, TEXT("HasTarget"));
		Owner->Attack();

		FAttackTaskMemory* MyMemory = reinterpret_cast<FAttackTaskMemory*>(NodeMemory);
		MyMemory->OwnerComp = &OwnerComp;
		MyMemory->NodeMemory = NodeMemory;

		Owner->OnFinishedAttack.AddLambda(
			[this, MyMemory]()
			{
				FinishLatentTask(
					*MyMemory->OwnerComp,
					EBTNodeResult::Succeeded
				);
			}
		);
	}
	else
	{
		UE_LOG(GP_AttackTaskLog, Display, TEXT("Has No Target"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UGP_AttackTask::OnAttackFinished()
{

}