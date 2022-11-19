// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "UObject/NoExportTypes.h"
#include "BSInputHandler.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BATTLESYSTEMPG_API UBSInputHandler : public UObject
{
	GENERATED_BODY()

private:

	class ABattleSystemGeneralPC* GeneralPC;
	class UEnhancedInputComponent* Input;
	class UEnhancedInputLocalPlayerSubsystem* InputSystem;

public:

	// Entry point for set controller and bind actions
	void SetupInputComponent(ABattleSystemGeneralPC* PlayerController);
	
	//=============================================
	// MAPPINGS

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Mappings")
	class UInputMappingContext* IM_BaseMapping;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Mappings")
	class UInputMappingContext* IM_BaseActionsMapping;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Mappings")
	class UInputMappingContext* IM_FirstAllySelectedMapping;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Mappings")
	class UInputMappingContext* IM_SecondAllySelectedMapping;

	//=============================================
	// ACTIONS

	// Camera Movements

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Actions")
	class UInputAction* IAMoveCamera;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Actions")
	class UInputAction* IARotateCamera;

	// Characters Selections

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Selection Actions")
	class UInputAction* IASelectFirstAlly;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Selection Actions")
	class UInputAction* IASelectSecondAlly;
	
	UPROPERTY(EditAnywhere, Category = "Enhanced Input Selection Actions")
	class UInputAction* IASelectThirdAlly;
	
	UPROPERTY(EditAnywhere, Category = "Enhanced Input Selection Actions")
	class UInputAction* IASelectFourthAlly;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Selection Actions")
	class UInputAction* IASelectNextEnemy;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input Selection Actions")
	class UInputAction* IASelectPreviousEnemy;

	//=============================================
	// Input handle funtions

	void MoveCamera(const FInputActionValue& Value);
	void RotateCamera(const FInputActionValue& Value);

	void SelectFirstAlly(const FInputActionValue& Value);
	void SelectSecondAlly(const FInputActionValue& Value);
	void SelectThirdAlly(const FInputActionValue& Value);
	void SelectFourthAlly(const FInputActionValue& Value);

	void SelectNextEnemy(const FInputActionValue& Value);
	void SelectPreviousEnemy(const FInputActionValue& Value);

	void ReleaseAllySelectionCommand();
};
