// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GP_AICharacter.h"
#include "AI/GP_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/GP_HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "AI/GP_AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(GP_AICharacterLog, All, All);

AGP_AICharacter::AGP_AICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; //PlacedInWorldOrSpawned  Disabled
	AIControllerClass = AGP_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}

	RightHandCollision = CreateDefaultSubobject<UBoxComponent>("RightHandCollision");
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	RightHandCollision->AttachToComponent(GetMesh(), AttachmentRules, "RightHandCollisionSocket");
	RightHandCollision->OnComponentBeginOverlap.AddDynamic(this, &AGP_AICharacter::OnOverlapHit);
	RightHandCollision->IgnoreActorWhenMoving(GetOwner(), true);

	LeftHandCollision = CreateDefaultSubobject<UBoxComponent>("LefttHandCollision");
	LeftHandCollision->AttachToComponent(GetMesh(), AttachmentRules, "LeftHandCollisionSocket");
	LeftHandCollision->OnComponentBeginOverlap.AddDynamic(this, &AGP_AICharacter::OnOverlapHit);
	LeftHandCollision->IgnoreActorWhenMoving(GetOwner(), true);

	HealthComponent = CreateDefaultSubobject<UGP_HealthComponent>("HealthComponent");
}

void AGP_AICharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);

	HealthComponent->OnDeath.AddDynamic(this, &AGP_AICharacter::HandleDeath);
}

void AGP_AICharacter::SetCurrentAnimState(EAIAnimState NextAnimState)
{
	if (CurrentAnimState == NextAnimState) return;

	EAIAnimState PreviousAnimState = CurrentAnimState;
	CurrentAnimState = NextAnimState;

	UE_LOG(GP_AICharacterLog, Display, TEXT("EAIAnimState changed from %s to %s"),
		*StaticEnum<EAIAnimState>()->GetNameStringByValue((int64)PreviousAnimState),
		*StaticEnum<EAIAnimState>()->GetNameStringByValue((int64)CurrentAnimState)
	);
}

void AGP_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_AICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGP_AICharacter::Attack()
{
	UE_LOG(GP_AICharacterLog, Display, TEXT("Attack"));

	PlayAnimMontage(AttackAnimMontage);
	SetCurrentAnimState(EAIAnimState::Attack);

	//GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AGP_AICharacter::StopAttack, AttackAnimMontage->CalculateSequenceLength(), false);
}

void AGP_AICharacter::StopAttack()
{
	UE_LOG(GP_AICharacterLog, Display, TEXT("StopAttack"));

	OnFinishedAttack.Broadcast();

	//GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	bIsDamageDone = false;
}

void AGP_AICharacter::FinishAwake()
{
	//bIsAwakening = false;
	OnFinishedAwake.Broadcast();
	//SetCurrentAnimState(EAIAnimState::Idle);
}

void AGP_AICharacter::OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Is it attack? broadcact event ?

	const auto HitActor = SweepResult.GetActor();
	if (!HitActor)
	{
		UE_LOG(GP_AICharacterLog, Display, TEXT("OnOverlapHit:: No HitActor"));
		return;
	}

	if (HitActor == this) return;
	
	const auto AIController = Cast<AGP_AIController>(Controller);
	const auto BehaviorType = AIController->GetTeamAttitudeTowards(*HitActor);
	if (BehaviorType == ETeamAttitude::Neutral)
	{
		UE_LOG(GP_AICharacterLog, Display, TEXT("AIController = %s, BehaviorType == ETeamAttitude::Neutral = %s"), *AIController->GetName(), BehaviorType == ETeamAttitude::Neutral ? TEXT("TRUE") : TEXT("FALSE"));
		return;
	}

	if (!bIsDamageDone && BehaviorType == ETeamAttitude::Hostile)
	{
		UE_LOG(GP_AICharacterLog, Display, TEXT("HitActor = %s, BehaviorType == ETeamAttitude::Hostile = %s"), *HitActor->GetName(), BehaviorType == ETeamAttitude::Hostile ? TEXT("TRUE") : TEXT("FALSE"));
		HitActor->TakeDamage(DamageAmount, FDamageEvent{}, Controller, this);
		bIsDamageDone = true;
	}
}

void AGP_AICharacter::HandleDeath()
{
	UE_LOG(GP_AICharacterLog, Display, TEXT("%s are dead"), *GetName());
	const auto AIController = Cast<AGP_AIController>(Controller);
	if (AIController && AIController->BrainComponent)
	{
		UE_LOG(GP_AICharacterLog, Display, TEXT("AIController && AIController->BrainComponent"));
		StopAttack();
		AIController->BrainComponent->Cleanup();

		PlayAnimMontage(DeathAnimMontage);
		SetCurrentAnimState(EAIAnimState::Death);

		GetCharacterMovement()->DisableMovement();
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		SetLifeSpan(DeathAnimMontage->CalculateSequenceLength() + 5.5f); // change it
	}
	else
	{
		UE_LOG(GP_AICharacterLog, Display, TEXT("no"));
	}
}
