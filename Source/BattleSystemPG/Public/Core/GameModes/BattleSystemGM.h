// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleSystemGM.generated.h"


/**
 * 
 */
UCLASS()
class BATTLESYSTEMPG_API ABattleSystemGM : public AGameModeBase
{
	GENERATED_BODY()

public:

	//====================================================
	// Exposed Functions

	TArray<class ARootBattleSystemCharacter*> getSelectableEnemiesReferences();
	class ARootBattleSystemCharacter* getSelectedEnemyRef();
	class ARootBattleSystemCharacter* selectNextEnemyRef();
	class ARootBattleSystemCharacter* selectPreviousEnemyRef();

	class ARootBattleSystemCharacter* getAllyRefByPosition(int8 position);
	int8 getPositionOfAllyRef(ARootBattleSystemCharacter* ally);




protected:
	
	TArray<class ARootBattleSystemCharacter*> enemiesReferences;
	TMap<int8,class ARootBattleSystemCharacter* > alliesReferences;
	class ARootBattleSystemCharacter* selectedEnemyRef;

	virtual void StartPlay() override;
	
	//====================================================
	// Setting up Battle System Functions

	void SetupAllEnemys();
	void SetupAllAllies();

	//====================================================
	// Internal Battle System Functions
	
	/*
	*	Direction must be 1 if it's the next enemy and -1 otherwise
	*/
	class ARootBattleSystemCharacter* ChangeEnemyRef(int direction);
};
