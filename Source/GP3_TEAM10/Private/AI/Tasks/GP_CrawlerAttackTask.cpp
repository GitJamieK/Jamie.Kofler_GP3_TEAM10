// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/GP_CrawlerAttackTask.h"
#include "AIController.h"
#include "AI/GP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Interfaces/GP_QTETargetInterface.h"

DEFINE_LOG_CATEGORY_STATIC(GP_CrawlerAttackTaskLog, All, All);

UGP_CrawlerAttackTask::UGP_CrawlerAttackTask()
{
    NodeName = "Crawler Attack";
    bNotifyTick = true;
}

EBTNodeResult::Type UGP_CrawlerAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedOwnerComp = &OwnerComp;

    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto Crawler = Cast<AGP_AICharacter>(Controller->GetPawn());

    if (!Controller || !Blackboard || !Crawler)
    {
        UE_LOG(GP_CrawlerAttackTaskLog, Display, TEXT("Not Valid"));
        return EBTNodeResult::Failed;
    }

    ACharacter* Player = Cast<ACharacter>(Blackboard->GetValueAsObject(TargetActorKey.SelectedKeyName));

    if (!Player)
    {
        UE_LOG(GP_CrawlerAttackTaskLog, Display, TEXT("Target actor is notvalid"));
        return EBTNodeResult::Failed;
    }

    FVector JumpTarget = Player->GetActorLocation() + FVector(0, 0, 100); // ???

    FVector Direction = (JumpTarget - Crawler->GetActorLocation()).GetSafeNormal();
    Crawler->LaunchCharacter(Direction * 600 + FVector(0, 0, 400), true, true);

    Crawler->OnQTEFinished.AddDynamic(this, &UGP_CrawlerAttackTask::OnQTEComplete);
    Crawler->StartQTE();

    if (Player && Player->GetClass()->ImplementsInterface(UGP_QTETargetInterface::StaticClass()))
    {
        IGP_QTETargetInterface::Execute_StartQTE(Player, Crawler);
    }

    Controller->BrainComponent->PauseLogic("QTE In Progress");

    return EBTNodeResult::InProgress;
}

void UGP_CrawlerAttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (bQTECompleted)
    {
        FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
    }
}

void UGP_CrawlerAttackTask::OnQTEComplete(bool bSuccess)
{
    const auto Controller = CachedOwnerComp->GetAIOwner();
    const auto Blackboard = CachedOwnerComp->GetBlackboardComponent();
    if (!Controller || !Blackboard) return;

    const auto Crawler = Cast<AGP_AICharacter>(Controller->GetPawn());
    if (!Crawler) return;

    Crawler->OnQTEFinished.RemoveDynamic(this, &UGP_CrawlerAttackTask::OnQTEComplete);

    ACharacter* Player = Cast<ACharacter>(Blackboard->GetValueAsObject(TargetActorKey.SelectedKeyName));
    if (!Player) return;

    if (bSuccess)
    {
        FVector PushBack = (Crawler->GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();
        Crawler->LaunchCharacter(PushBack * 800 + FVector(0, 0, 300), true, true);
    }
    else
    {
        // death to player
    }

    bQTECompleted = true;
    Controller->BrainComponent->ResumeLogic("QTE Finished");
}

