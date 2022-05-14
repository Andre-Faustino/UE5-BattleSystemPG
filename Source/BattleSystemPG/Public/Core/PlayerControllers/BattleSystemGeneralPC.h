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

	
	
protected:	

	APawn* thisPawn;

	virtual void SetupInputComponent() override;
	
	//Input handle funtions
	void MoveCameraHorizontally(float Val);
	void MoveCameraVertically(float Val);
	void RotateCameraHorizontally(float Val);
	void RotateCameraVertically(float Val);

};
