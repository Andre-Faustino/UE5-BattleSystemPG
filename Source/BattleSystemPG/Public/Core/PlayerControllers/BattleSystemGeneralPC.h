// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "BSInputHandler.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	TSubclassOf<UBSInputHandler> InputConfig;

	/** Time to camera reach target's location, the higher the slower */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraConfiguration)
	float TargetSwitchTransitionTime = 4.f;
	
protected:	

	
	class ABattleSystemGM* BattleSystemGameMode;

	class ARootBattleSystemCharacter* selectedEnemy;
	class ARootBattleSystemCharacter* currentSelectedAlly;

	//=============================================
	// Setting up functions

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	//=============================================
	// Input handle funtions

public:

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

	void MoveCamera(const FVector2D& Value);
	void RotateCamera(const FVector2D& Value);

	void InputCameraMovementToActorLocation(AActor* targetActor);

	//=============================================
	// Internal Functions

	void onSelectedAlly(class ARootBattleSystemCharacter* selectedAlly);
};
