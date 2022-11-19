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
	bIsCameraFree = true;
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

void ABattleSystemGeneralPC::Tick(float DeltaTime) {}

void ABattleSystemGeneralPC::SetupInputComponent() {

	Super::SetupInputComponent();
	if (InputConfig) InputConfig.GetDefaultObject()->SetupInputComponent(this);
}

void ABattleSystemGeneralPC::SelectFirstAllyCommand()
{
	UE_LOG(LogTemp, Display , TEXT("Try to select First Ally"));
	ARootBattleSystemCharacter* selectedAllyTemp = BattleSystemGameMode->getAllyRefByPosition(1);
	if (selectedAllyTemp != nullptr) {
		onSelectedAlly(selectedAllyTemp);
		
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("There's no Ally on this position"));
	}
}

void ABattleSystemGeneralPC::SelectSecondAllyCommand()
{
	UE_LOG(LogTemp, Display, TEXT("Try to select Second Ally"));
	ARootBattleSystemCharacter* selectedAllyTemp = BattleSystemGameMode->getAllyRefByPosition(2);
	if (selectedAllyTemp != nullptr) {
		onSelectedAlly(selectedAllyTemp);
		
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("There's no Ally on this position"));
	}
}

void ABattleSystemGeneralPC::SelectThirdAllyCommand()
{
	UE_LOG(LogTemp, Display, TEXT("Try to select Third Ally"));
	ARootBattleSystemCharacter* selectedAllyTemp = BattleSystemGameMode->getAllyRefByPosition(3);
	if (selectedAllyTemp != nullptr) {
		onSelectedAlly(selectedAllyTemp);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("There's no Ally on this position"));
	}
}

void ABattleSystemGeneralPC::SelectFourthAllyCommand()
{
	UE_LOG(LogTemp, Display, TEXT("Try to select Fourth Ally"));
	ARootBattleSystemCharacter* selectedAllyTemp = BattleSystemGameMode->getAllyRefByPosition(4);
	if (selectedAllyTemp != nullptr) {
		onSelectedAlly(selectedAllyTemp);		
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("There's no Ally on this position"));
	}
}

void ABattleSystemGeneralPC::ReleaseAllySelectionCommand()
{

	// Only move camera to Selected Enemy if camera is NOT free and there's any enemy selected
	if (!bIsCameraFree && selectedEnemy != nullptr) {
		selectedActorTarget = selectedEnemy;
		InputCameraMovementToActorLocation(selectedActorTarget);
	}

	// Deselect Ally
	currentSelectedAlly = nullptr;
}

void ABattleSystemGeneralPC::SelectNextEnemy()
{
	selectedEnemy = BattleSystemGameMode->selectNextEnemyRef();

	//Only move camera if no ally is selected
	if (currentSelectedAlly == nullptr) {
		selectedActorTarget = selectedEnemy;
		InputCameraMovementToActorLocation(selectedActorTarget);
	}	
	UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), selectedEnemy->GetUniqueID());
}

void ABattleSystemGeneralPC::SelectPreviousEnemy()
{
	selectedEnemy = BattleSystemGameMode->selectPreviousEnemyRef();

	//Only move camera if no ally is selected
	if (currentSelectedAlly == nullptr){
		selectedActorTarget = selectedEnemy;
		InputCameraMovementToActorLocation(selectedActorTarget);
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), selectedEnemy->GetUniqueID());
}


//=============================================
// Camera Mechanism Functions

void ABattleSystemGeneralPC::MoveCamera(const FVector2D& Value)
{
	bIsCameraFree = true;
	cameraPawn->AddMovementInput(cameraPawn->GetActorRightVector(), Value.X);
	cameraPawn->AddMovementInput(cameraPawn->GetActorForwardVector(), Value.Y);
	cameraPawn->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void ABattleSystemGeneralPC::RotateCamera(const FVector2D& Value)
{
	cameraPawn->AddControllerYawInput(Value.X);

	USpringArmComponent* springArm = cameraPawn->FindComponentByClass<USpringArmComponent>();
	if (springArm != nullptr
		&& springArm->GetRelativeRotation().Pitch + Value.Y < 0
		&& springArm->GetRelativeRotation().Pitch + Value.Y > -90)
	{
		springArm->AddRelativeRotation(FRotator(Value.Y, 0, 0));
	}
}

void ABattleSystemGeneralPC::InputCameraMovementToActorLocation(AActor* targetActor)
{
	bIsCameraFree = false;
	cameraPawn->SetActorLocation(targetActor->GetActorLocation());
	cameraPawn->AttachToComponent(targetActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
}

//=============================================
// Internal Functions

void ABattleSystemGeneralPC::onSelectedAlly(ARootBattleSystemCharacter* selectedAlly)
{
	currentSelectedAlly = selectedAlly;
		
	// Move Camera to Selected Ally
	selectedActorTarget = selectedAlly;
	InputCameraMovementToActorLocation(selectedActorTarget);
}

