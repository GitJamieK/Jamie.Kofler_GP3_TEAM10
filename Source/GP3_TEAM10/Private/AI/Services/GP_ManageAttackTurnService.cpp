// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/GP_ManageAttackTurnService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(GP_ManageAttackTurnServiceLog, All, All);

UGP_ManageAttackTurnService::UGP_ManageAttackTurnService()
{
	NodeName = "Manage Attack Turn";

	Interval = 0.1f;
	bNotifyBecomeRelevant = true;
}

void UGP_ManageAttackTurnService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	UWorld* World = OwnerComp.GetWorld();
	if (!Controller || !Blackboard || !World) return;

	/*bool bIsThisEnemyAttacking = Blackboard->GetValueAsBool(IsAttackingKey.SelectedKeyName);
	bool bIsSomeoneElseAttacking = false;
	for (auto It = World->GetControllerIterator(); It; ++It)
	{
		AAIController* Other = Cast<AAIController>(It->Get());
		if(!Other || Other == Controller) continue;

		if (auto* OtherBlackboard = Other->GetBlackboardComponent())
		{
			if (OtherBlackboard->GetValueAsBool(IsAttackingKey.SelectedKeyName))
			{
				bIsSomeoneElseAttacking = true;
				break;
			}
		}
	}
	bool bCanAttack = bIsThisEnemyAttacking && !bIsSomeoneElseAttacking;
	Blackboard->SetValueAsBool(CanAttackKey.SelectedKeyName, bCanAttack);
	UE_LOG(GP_ManageAttackTurnServiceLog, Display, TEXT("Controller = %s, bCanAttack = %s"), *Controller->GetName(), bCanAttack ? TEXT("TRUE") : TEXT("FALSE"));*/

	TArray<AAIController*> CloseEnemies;
	for (auto It = World->GetControllerIterator(); It; ++It)
	{
		AAIController* AI = Cast<AAIController>(It->Get());
		if (!AI) continue;

		if (auto* AIBlackboard = AI->GetBlackboardComponent())
		{
			if (AIBlackboard->GetValueAsObject(TargetActorKey.SelectedKeyName) && AIBlackboard->GetValueAsBool(IsCloseEnoughKey.SelectedKeyName))
			{
				CloseEnemies.Add(AI);
			}
		}
	}

	AAIController* CurrentAttacker = nullptr;
	for (AAIController* AI : CloseEnemies)
	{
		if (AI->GetBlackboardComponent()->GetValueAsBool(IsAttackingKey.SelectedKeyName))
		{
			CurrentAttacker = AI;
			break;
		}
	}

	for (auto It = World->GetControllerIterator(); It; ++It)
	{
		AAIController* AI = Cast<AAIController>(It->Get());
		if (!AI) continue;

		auto* AIBlackboard = AI->GetBlackboardComponent();
		if (!AIBlackboard) continue;

		bool bCanAttack = true;
		if (CurrentAttacker)
		{
			bCanAttack = AI == CurrentAttacker;
		}
		AIBlackboard->SetValueAsBool(CanAttackKey.SelectedKeyName, bCanAttack);
		UE_LOG(GP_ManageAttackTurnServiceLog, Display, TEXT("Controller = %s, bCanAttack = %s"), *AI->GetName(), bCanAttack ? TEXT("TRUE") : TEXT("FALSE"));
	}
}

