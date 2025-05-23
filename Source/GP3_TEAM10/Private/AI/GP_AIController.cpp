// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GP_AIController.h"
#include "AI/GP_AICharacter.h"
#include "AI/Components/GP_AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(GP_AIController, All, All);

AGP_AIController::AGP_AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UGP_AIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);

	SetGenericTeamId(FGenericTeamId(0));
}

ETeamAttitude::Type AGP_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	ETeamAttitude::Type Attitude;
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	if (OtherTeamAgent)
	{
		Attitude = FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId());
	}
	else
	{
		Attitude = ETeamAttitude::Neutral;
	}
	return Attitude;
}

void AGP_AIController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	IGenericTeamAgentInterface* ControlledAgent = Cast<IGenericTeamAgentInterface>(GetPawn());
	if (ControlledAgent)
	{
		ControlledAgent->SetGenericTeamId(NewTeamID);
	}
}

FGenericTeamId AGP_AIController::GetGenericTeamId() const
{
	const IGenericTeamAgentInterface* ControlledAgent = Cast<const IGenericTeamAgentInterface>(GetPawn());
	if (ControlledAgent)
	{
		return ControlledAgent->GetGenericTeamId();
	}

	return FGenericTeamId();
}

void AGP_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const AGP_AICharacter* AICharacter = Cast<AGP_AICharacter>(InPawn);
	if (!IsValid(AICharacter))
	{
		UE_LOG(GP_AIController, Warning, TEXT("OnPossess: InPawn is not AGP_AICharacter"));
		return;
	}

	if (AICharacter->BehaviorTree)
	{
		RunBehaviorTree(AICharacter->BehaviorTree);
		UE_LOG(GP_AIController, Display, TEXT("OnPossess: RunBehaviorTree"));
	}
}

void AGP_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//const auto TargetActor = AIPerceptionComponent->GetTargetEnemy();
	SetFocus(GetFocusOnActor()); // where to set?
}

AActor* AGP_AIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
