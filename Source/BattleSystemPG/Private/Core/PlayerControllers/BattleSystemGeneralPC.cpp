// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerControllers/BattleSystemGeneralPC.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"

ABattleSystemGeneralPC::ABattleSystemGeneralPC()
{

}
void ABattleSystemGeneralPC::SetupInputComponent() {

	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveCameraHorizontal", this, &ABattleSystemGeneralPC::MoveCameraHorizontally);
	InputComponent->BindAxis("MoveCameraVertical", this, &ABattleSystemGeneralPC::MoveCameraVertically);
	InputComponent->BindAxis("RotateCameraHorizontal", this, &ABattleSystemGeneralPC::RotateCameraHorizontally);
	InputComponent->BindAxis("RotateCameraVertical", this, &ABattleSystemGeneralPC::RotateCameraVertically);

}

void ABattleSystemGeneralPC::MoveCameraHorizontally(float Val)
{
	if (Val != 0.f && GetPawn() != nullptr) {
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Val);		
	}
}

void ABattleSystemGeneralPC::MoveCameraVertically(float Val)
{
	if (Val != 0.f && GetPawn() != nullptr) {
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Val);	
	}
}

void ABattleSystemGeneralPC::RotateCameraHorizontally(float Val)
{
	if (Val != 0.f && GetPawn() != nullptr) {
		GetPawn()->AddControllerYawInput(Val);	
	}
}

void ABattleSystemGeneralPC::RotateCameraVertically(float Val)
{
	if (Val != 0.f && GetPawn() != nullptr) {
		USpringArmComponent* springArm = GetPawn()->FindComponentByClass<USpringArmComponent>();
		if (springArm != nullptr 
			&& springArm->GetRelativeRotation().Pitch + Val < 0
			&& springArm->GetRelativeRotation().Pitch + Val > -90)
		{			
			springArm->AddRelativeRotation(FRotator(Val, 0, 0));
		}	
	}
}


