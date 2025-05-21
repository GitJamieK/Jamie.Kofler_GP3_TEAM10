// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GP_AwakeTask.h"
#include "AIController.h"
#include "AI/GP_AICharacter.h"

DEFINE_LOG_CATEGORY_STATIC(GP_AwakeTaskLog, All, All);

UGP_AwakeTask::UGP_AwakeTask()
{
	NodeName = "Awake";
}

EBTNodeResult::Type UGP_AwakeTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Owner = Cast<AGP_AICharacter>(Controller->GetPawn());

	if (!Controller || !Owner)
	{
		//UE_LOG(GP_AwakeTaskLog, Display, TEXT("!Controller || !Owner : %s"), *Owner->GetName());
		return EBTNodeResult::Failed;
	}

	UE_LOG(GP_AwakeTaskLog, Display, TEXT("AwakeTask"));
	Owner->SetCurrentAnimState(EAIAnimState::StandUp);
	//return EBTNodeResult::Succeeded;

	FAwakeTaskMemory* MyMemory = reinterpret_cast<FAwakeTaskMemory*>(NodeMemory);
	MyMemory->OwnerComp = &OwnerComp;
	MyMemory->NodeMemory = NodeMemory;

	Owner->OnFinishedAwake.AddLambda(
		[this, MyMemory]()
		{
			UE_LOG(GP_AwakeTaskLog, Display, TEXT("Finish Awake"));

			AAIController* Controller = MyMemory->OwnerComp->GetAIOwner();
			AGP_AICharacter* Owner = Cast<AGP_AICharacter>(Controller->GetPawn());

			Owner->SetIsAwakening(false);
			Owner->SetCurrentAnimState(EAIAnimState::Idle);
			FinishLatentTask(*MyMemory->OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	return EBTNodeResult::InProgress;
}