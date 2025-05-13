// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Components/GP_AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AI/GP_AIController.h"

AActor* UGP_AIPerceptionComponent::GetTargetEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);

	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AGP_AIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* TargetPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		if (!PercieveActor) return nullptr; //continue?

		//const auto BehaviorType = Controller->GetTeamAttitudeTowards(*PercieveActor);
		//const auto HealthComponent = PercieveActor->FindComponentByClass<>();
		//if (BehaviorType == ETeamAttitude::Hostile && HealthComponent && !HealthComponent->IsDead()) //TODO: check if enemies or not and dead actor or not
		{
			TargetPawn = PercieveActor;
		}
	}

	return TargetPawn;
}


