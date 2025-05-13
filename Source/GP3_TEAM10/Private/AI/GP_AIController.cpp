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
