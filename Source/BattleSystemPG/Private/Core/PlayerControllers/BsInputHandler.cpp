// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerControllers/BSInputHandler.h"
#include "BattleSystemPG/Public/Core/PlayerControllers/BattleSystemGeneralPC.h"
#include "GameFramework/Character.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"

void UBSInputHandler::SetupInputComponent(ABattleSystemGeneralPC* PlayerController)
{
	if(PlayerController) 
		GeneralPC = PlayerController;

	Input = Cast<UEnhancedInputComponent>(GeneralPC->InputComponent);
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GeneralPC->Player))
	{
		InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSystem)
		{
			InputSystem->ClearAllMappings();
			InputSystem->AddMappingContext(IM_BaseMapping, 0);
			InputSystem->AddMappingContext(IM_BaseActionsMapping, 0);
		}
	}
	if (Input == nullptr) return;

	Input->BindAction(IAMoveCamera, ETriggerEvent::Triggered, this, &UBSInputHandler::MoveCamera);
	Input->BindAction(IARotateCamera, ETriggerEvent::Triggered, this, &UBSInputHandler::RotateCamera);

	Input->BindAction(IASelectFirstAlly, ETriggerEvent::Started, this, &UBSInputHandler::SelectFirstAlly);
	Input->BindAction(IASelectSecondAlly, ETriggerEvent::Started, this, &UBSInputHandler::SelectSecondAlly);
	Input->BindAction(IASelectThirdAlly, ETriggerEvent::Started, this, &UBSInputHandler::SelectThirdAlly);
	Input->BindAction(IASelectFourthAlly, ETriggerEvent::Started, this, &UBSInputHandler::SelectFourthAlly);

	Input->BindAction(IASelectFirstAlly, ETriggerEvent::Completed, this, &UBSInputHandler::ReleaseAllySelectionCommand);
	Input->BindAction(IASelectSecondAlly, ETriggerEvent::Completed, this, &UBSInputHandler::ReleaseAllySelectionCommand);
	Input->BindAction(IASelectThirdAlly, ETriggerEvent::Completed, this, &UBSInputHandler::ReleaseAllySelectionCommand);
	Input->BindAction(IASelectFourthAlly, ETriggerEvent::Completed, this, &UBSInputHandler::ReleaseAllySelectionCommand);

	Input->BindAction(IASelectNextEnemy, ETriggerEvent::Started, this, &UBSInputHandler::SelectNextEnemy);
	Input->BindAction(IASelectPreviousEnemy, ETriggerEvent::Started, this, &UBSInputHandler::SelectPreviousEnemy);
}

void UBSInputHandler::MoveCamera(const FInputActionValue& Value)
{
	if (Value.IsNonZero() && GeneralPC->cameraPawn != nullptr) 
		GeneralPC->MoveCamera(Value.Get<FVector2D>());
}

void UBSInputHandler::RotateCamera(const FInputActionValue& Value)
{
	if (Value.IsNonZero() && GeneralPC->cameraPawn != nullptr)
		GeneralPC->RotateCamera(Value.Get<FVector2D>());
}

void UBSInputHandler::SelectFirstAlly(const FInputActionValue& Value)
{
	GeneralPC->SelectFirstAllyCommand();
	InputSystem->AddMappingContext(IM_FirstAllySelectedMapping, 1);
}

void UBSInputHandler::SelectSecondAlly(const FInputActionValue& Value)
{
	GeneralPC->SelectSecondAllyCommand();
	InputSystem->AddMappingContext(IM_SecondAllySelectedMapping, 1);
}

void UBSInputHandler::SelectThirdAlly(const FInputActionValue& Value)
{
	GeneralPC->SelectThirdAllyCommand();
}

void UBSInputHandler::SelectFourthAlly(const FInputActionValue& Value)
{
	GeneralPC->SelectFourthAllyCommand();
}

void UBSInputHandler::SelectNextEnemy(const FInputActionValue& Value)
{
	GeneralPC->SelectNextEnemy();
}

void UBSInputHandler::SelectPreviousEnemy(const FInputActionValue& Value)
{
	GeneralPC->SelectPreviousEnemy();
}

void UBSInputHandler::ReleaseAllySelectionCommand()
{
	InputSystem->ClearAllMappings();
	InputSystem->AddMappingContext(IM_BaseMapping, 0);
	InputSystem->AddMappingContext(IM_BaseActionsMapping, 0);

	GeneralPC->ReleaseAllySelectionCommand();
}
