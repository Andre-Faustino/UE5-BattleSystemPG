// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleSystemGeneralPC.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEMPG_API ABattleSystemGeneralPC : public APlayerController
{
	GENERATED_BODY()

public:
	
	ABattleSystemGeneralPC();

	/** Time to camera reach target's location, the higher the slower */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraConfiguration)
	float TargetSwitchTransitionTime = 4.f;
	
protected:	

	
	class ABattleSystemGM* BattleSystemGameMode;

	class ARootBattleSystemCharacter* selectedEnemy;
	class ARootBattleSystemCharacter* currentlySelectedAlly;

	//=============================================
	// Setting up funtions

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	virtual void SetupInputComponent() override;
	void FreeInputState();
	void SelectedAllyInputState(int8 position);

	//=============================================
	// Input handle funtions

	void MoveCameraHorizontallyCommand(float Val);
	void MoveCameraVerticallyCommand(float Val);
	void RotateCameraHorizontallyCommand(float Val);
	void RotateCameraVerticallyCommand(float Val);

	void SelectFirstAllyCommand();
	void SelectSecondAllyCommand();
	void SelectThirdAllyCommand();
	void SelectFourthAllyCommand();

	void ReleaseAllySelectionCommand();

	void SelectNextEnemy();
	void SelectPreviousEnemy();


	//=============================================
	// Camera Mechanism Functions

	AActor* selectedActorTarget;
	ACharacter* cameraPawn;
	bool bIsCameraFree;

	void MoveCameraHorizontally(float Val);
	void MoveCameraVertically(float Val);
	void RotateCameraHorizontally(float Val);
	void RotateCameraVertically(float Val);

	void InputCameraMovementToActorLocation(AActor* targetActor);

	//=============================================
	// Internal Functions

	void onSelectedAlly(class ARootBattleSystemCharacter* selectedAlly);
};
