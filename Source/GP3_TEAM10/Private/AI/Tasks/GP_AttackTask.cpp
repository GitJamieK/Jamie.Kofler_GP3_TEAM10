// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GP_AttackTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/GP_AICharacter.h"

UGP_AttackTask::UGP_AttackTask()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UGP_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}