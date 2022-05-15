// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerControllers/BattleSystemGeneralPC.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "BattleSystemPG/Public/Core/GameModes/BattleSystemGM.h"
#include "BattleSystemPG/Public/Core/Characters/RootBattleSystemCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"

ABattleSystemGeneralPC::ABattleSystemGeneralPC()
{
	
}
void ABattleSystemGeneralPC::BeginPlay()
{
	Super::BeginPlay();


	if (GetPawn() != nullptr) {
		cameraPawn = Cast<ACharacter>(GetPawn());
		USpringArmComponent* springArm = cameraPawn->FindComponentByClass<USpringArmComponent>();
		springArm->bEnableCameraLag = true;
		springArm->CameraLagSpeed = TargetSwitchTransitionTime;
	}

	if (GetWorld()->GetAuthGameMode() != nullptr) {
		BattleSystemGameMode = Cast<ABattleSystemGM>(GetWorld()->GetAuthGameMode());
	}
}
void ABattleSystemGeneralPC::Tick(float DeltaTime)
{
	

}

void ABattleSystemGeneralPC::SetupInputComponent() {

	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveCameraHorizontal", this, &ABattleSystemGeneralPC::MoveCameraHorizontallyCommand);
	InputComponent->BindAxis("MoveCameraVertical", this, &ABattleSystemGeneralPC::MoveCameraVerticallyCommand);
	InputComponent->BindAxis("RotateCameraHorizontal", this, &ABattleSystemGeneralPC::RotateCameraHorizontallyCommand);
	InputComponent->BindAxis("RotateCameraVertical", this, &ABattleSystemGeneralPC::RotateCameraVerticallyCommand);

	InputComponent->BindAction("NextEnemy", IE_Pressed, this, &ABattleSystemGeneralPC::SelectNextEnemy);
	InputComponent->BindAction("PrevioustEnemy", IE_Pressed, this, &ABattleSystemGeneralPC::SelectPreviousEnemy); 
}

//=============================================
// Input handle funtions

void ABattleSystemGeneralPC::MoveCameraHorizontallyCommand(float Val)
{
	MoveCameraHorizontally(Val);
}

void ABattleSystemGeneralPC::MoveCameraVerticallyCommand(float Val)
{
	MoveCameraVertically(Val);
}

void ABattleSystemGeneralPC::RotateCameraHorizontallyCommand(float Val)
{
	RotateCameraHorizontally(Val);
}

void ABattleSystemGeneralPC::RotateCameraVerticallyCommand(float Val)
{
	RotateCameraVertically(Val);
}

void ABattleSystemGeneralPC::SelectNextEnemy()
{
	selectedEnemy = BattleSystemGameMode->selectNextEnemyRef();
	selectedActorTarget = selectedEnemy;
	InputMovementToActorLocation(selectedActorTarget);
	UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), selectedEnemy->GetUniqueID());
}

void ABattleSystemGeneralPC::SelectPreviousEnemy()
{
	selectedEnemy = BattleSystemGameMode->selectPreviousEnemyRef();
	selectedActorTarget = selectedEnemy;
	InputMovementToActorLocation(selectedActorTarget);
	UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), selectedEnemy->GetUniqueID());
}


//=============================================
// Camera Mechanism Functions

void ABattleSystemGeneralPC::MoveCameraHorizontally(float Val)
{
	if (Val != 0.f && cameraPawn != nullptr) {
		cameraPawn->AddMovementInput(cameraPawn->GetActorRightVector(), Val);
		cameraPawn->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void ABattleSystemGeneralPC::MoveCameraVertically(float Val)
{
	if (Val != 0.f && cameraPawn != nullptr) {
		cameraPawn->AddMovementInput(cameraPawn->GetActorForwardVector(), Val);
		cameraPawn->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void ABattleSystemGeneralPC::RotateCameraHorizontally(float Val)
{
	if (Val != 0.f && cameraPawn != nullptr) {
		cameraPawn->AddControllerYawInput(Val);
	}
}

void ABattleSystemGeneralPC::RotateCameraVertically(float Val)
{
	if (Val != 0.f && cameraPawn != nullptr) {
		USpringArmComponent* springArm = cameraPawn->FindComponentByClass<USpringArmComponent>();
		if (springArm != nullptr
			&& springArm->GetRelativeRotation().Pitch + Val < 0
			&& springArm->GetRelativeRotation().Pitch + Val > -90)
		{
			springArm->AddRelativeRotation(FRotator(Val, 0, 0));
		}
	}
}

void ABattleSystemGeneralPC::InputMovementToActorLocation(AActor* targetActor)
{
	cameraPawn->SetActorLocation(targetActor->GetActorLocation());
	cameraPawn->AttachToComponent(targetActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);

}

