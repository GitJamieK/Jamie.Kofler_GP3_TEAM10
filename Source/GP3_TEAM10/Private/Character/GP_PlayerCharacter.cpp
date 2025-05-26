// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GP_PlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "AI/GP_AICharacter.h"
#include "Core/GP_GameModeBase.h"

AGP_PlayerCharacter::AGP_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGP_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGP_PlayerCharacter::StartQTE_Implementation(AActor* InstigatorActor)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	const auto GameMode = Cast<AGP_GameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->HandleQTEState();
	}

	bQTEActive = true;
	QTEProgress = 0.0f;
	QTEElapsedTime = 0.0f;
	QTEInstigator = InstigatorActor;

	GetWorldTimerManager().SetTimer(QTETickHandle, this, &AGP_PlayerCharacter::UpdateQTE, 0.05f, true);
	GetWorldTimerManager().SetTimer(QTEFailHandle, this, &AGP_PlayerCharacter::FailQTE, QTEFillTime, false);
}

void AGP_PlayerCharacter::OnQTEButtonPressed()
{
	if (!bQTEActive) return;

	QTEProgress += QTEDrainPerPress;
	QTEProgress = FMath::Clamp(QTEProgress, 0.0f, QTEThreshold);

	if (QTEProgress >= QTEThreshold)
	{
		bQTEActive = false;
		GetWorldTimerManager().ClearTimer(QTETickHandle);
		GetWorldTimerManager().ClearTimer(QTEFailHandle);

		if (auto* Enemy = Cast<AGP_AICharacter>(QTEInstigator))
		{
			Enemy->OnQTEFinished.Broadcast(true);
		}
	}
}

void AGP_PlayerCharacter::UpdateQTE()
{
	if (!bQTEActive) return;

	QTEElapsedTime += 0.05f;
	float TimeLeft = FMath::Clamp(QTEFillTime - QTEElapsedTime, 0.0f, QTEFillTime);

	IGP_QTETargetInterface::Execute_OnQTEProgressUpdated(this, QTEProgress, TimeLeft);
}

void AGP_PlayerCharacter::FailQTE()
{
	bQTEActive = false;
	GetWorldTimerManager().ClearTimer(QTETickHandle);

	if (auto* Enemy = Cast<AGP_AICharacter>(QTEInstigator))
	{
		Enemy->OnQTEFinished.Broadcast(false);
	}
}

