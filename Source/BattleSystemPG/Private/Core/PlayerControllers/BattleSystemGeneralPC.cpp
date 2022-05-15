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
void ABattleSystemGeneralPC::Tick(float DeltaTime)
{
	

}

void ABattleSystemGeneralPC::SetupInputComponent() {

	// set up gameplay key bindings
	Super::SetupInputComponent();
	FreeInputState();
}

void ABattleSystemGeneralPC::FreeInputState()
{
	
	InputComponent->ClearActionBindings();

	InputComponent->BindAxis("MoveCameraHorizontal", this, &ABattleSystemGeneralPC::MoveCameraHorizontallyCommand);
	InputComponent->BindAxis("MoveCameraVertical", this, &ABattleSystemGeneralPC::MoveCameraVerticallyCommand);
	InputComponent->BindAxis("RotateCameraHorizontal", this, &ABattleSystemGeneralPC::RotateCameraHorizontallyCommand);
	InputComponent->BindAxis("RotateCameraVertical", this, &ABattleSystemGeneralPC::RotateCameraVerticallyCommand);

	InputComponent->BindAction("SelectFirstAlly", IE_Pressed, this, &ABattleSystemGeneralPC::SelectFirstAllyCommand);
	InputComponent->BindAction("SelectSecondAlly", IE_Pressed, this, &ABattleSystemGeneralPC::SelectSecondAllyCommand);
	InputComponent->BindAction("SelectThirdAlly", IE_Pressed, this, &ABattleSystemGeneralPC::SelectThirdAllyCommand);
	InputComponent->BindAction("SelectFourthAlly", IE_Pressed, this, &ABattleSystemGeneralPC::SelectFourthAllyCommand);

	InputComponent->BindAction("NextEnemy", IE_Pressed, this, &ABattleSystemGeneralPC::SelectNextEnemy);
	InputComponent->BindAction("PrevioustEnemy", IE_Pressed, this, &ABattleSystemGeneralPC::SelectPreviousEnemy);
}

void ABattleSystemGeneralPC::SelectedAllyInputState(int8 position)
{
	InputComponent->ClearActionBindings();

	// Only Release Ally Selection if the released trigger is the same of the position of the currently selected ally
	switch (position) {
		case 1: 
		{
			InputComponent->BindAction("SelectFirstAlly", IE_Released, this, &ABattleSystemGeneralPC::ReleaseAllySelectionCommand);
			break;
		}
		case 2:
		{
			InputComponent->BindAction("SelectSecondAlly", IE_Released, this, &ABattleSystemGeneralPC::ReleaseAllySelectionCommand);
			break;
		}
		case 3:
		{
			InputComponent->BindAction("SelectThirdAlly", IE_Released, this, &ABattleSystemGeneralPC::ReleaseAllySelectionCommand);
			break;
		}
		case 4:
		{
			InputComponent->BindAction("SelectFourthAlly", IE_Released, this, &ABattleSystemGeneralPC::ReleaseAllySelectionCommand);
			break;
		}
	}

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
	FreeInputState();

	// Only move camera to Selected Enemy if camera is NOT free and there's any enemy selected
	if (!bIsCameraFree && selectedEnemy != nullptr) {
		selectedActorTarget = selectedEnemy;
		InputCameraMovementToActorLocation(selectedActorTarget);
	}

	// Deselect Ally
	currentlySelectedAlly = nullptr;
}

void ABattleSystemGeneralPC::SelectNextEnemy()
{
	selectedEnemy = BattleSystemGameMode->selectNextEnemyRef();

	//Only move camera if no ally is selected
	if (currentlySelectedAlly == nullptr) {
		selectedActorTarget = selectedEnemy;
		InputCameraMovementToActorLocation(selectedActorTarget);
	}	
	UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), selectedEnemy->GetUniqueID());
}

void ABattleSystemGeneralPC::SelectPreviousEnemy()
{
	selectedEnemy = BattleSystemGameMode->selectPreviousEnemyRef();

	//Only move camera if no ally is selected
	if (currentlySelectedAlly == nullptr){
		selectedActorTarget = selectedEnemy;
		InputCameraMovementToActorLocation(selectedActorTarget);
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), selectedEnemy->GetUniqueID());
}


//=============================================
// Camera Mechanism Functions

void ABattleSystemGeneralPC::MoveCameraHorizontally(float Val)
{
	if (Val != 0.f && cameraPawn != nullptr) {
		bIsCameraFree = true;
		cameraPawn->AddMovementInput(cameraPawn->GetActorRightVector(), Val);
		cameraPawn->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void ABattleSystemGeneralPC::MoveCameraVertically(float Val)
{
	if (Val != 0.f && cameraPawn != nullptr) {
		bIsCameraFree = true;
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
	currentlySelectedAlly = selectedAlly;
	
	// Change Input to Ally State 
	int8 position = BattleSystemGameMode->getPositionOfAllyRef(selectedAlly);
	SelectedAllyInputState(position);
	
	// Move Camera to Selected Ally
	selectedActorTarget = selectedAlly;
	InputCameraMovementToActorLocation(selectedActorTarget);
}

