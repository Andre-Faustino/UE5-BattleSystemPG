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

	/** Speed of camera transition to enemy target */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraConfiguration)
	float EnemyFollowMovimentSpeed;
	
protected:	

	
	class ABattleSystemGM* BattleSystemGameMode;

	class ARootBattleSystemCharacter* selectedEnemy;

	//=============================================
	// Setting up funtions

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	

	//=============================================
	// Input handle funtions

	void MoveCameraHorizontallyCommand(float Val);
	void MoveCameraVerticallyCommand(float Val);
	void RotateCameraHorizontallyCommand(float Val);
	void RotateCameraVerticallyCommand(float Val);

	void SelectNextEnemy();
	void SelectPreviousEnemy();

	//=============================================
	// Camera Mechanism Functions

	AActor* selectedActorTarget;
	ACharacter* cameraPawn;

	void MoveCameraHorizontally(float Val);
	void MoveCameraVertically(float Val);
	void RotateCameraHorizontally(float Val);
	void RotateCameraVertically(float Val);

	void InputMovementToActorLocation(AActor* targetActor);
};
