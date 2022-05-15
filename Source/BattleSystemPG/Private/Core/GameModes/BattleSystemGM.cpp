// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameModes/BattleSystemGM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BattleSystemPG/Public/Core/Characters/RootBattleSystemCharacter.h"

void ABattleSystemGM::StartPlay()
{
	Super::StartPlay();
		
	SetupAllEnemys();
	SetupAllAllies();
}

//====================================================
// Setting up Battle System Functions

void ABattleSystemGM::SetupAllEnemys() {

	TArray<AActor*> enemyActorReferences;
	//TODO: Change this Tag implementation when allies and enemies have it's own subclasses  
	UGameplayStatics::GetAllActorsOfClassWithTag
		(GetWorld(), ARootBattleSystemCharacter::StaticClass(), "enemy", enemyActorReferences);

	for (AActor* enemyActor : enemyActorReferences) {
		if (ARootBattleSystemCharacter* enemyReference = Cast<ARootBattleSystemCharacter>(enemyActor)) {
			enemiesReferences.Push(enemyReference);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("NUMBER OF ENEMYS: %d"), enemiesReferences.Num());	
}

void ABattleSystemGM::SetupAllAllies()
{
	
	TArray<AActor*> alliesActorReferences;
	//TODO: Change this Tag implementation when allies and enemies have it's own subclasses  
	UGameplayStatics::GetAllActorsOfClassWithTag
	(GetWorld(), ARootBattleSystemCharacter::StaticClass(), "ally", alliesActorReferences);
	int countPosition = 1;
	for (AActor* allyActor : alliesActorReferences) {
		if (ARootBattleSystemCharacter* allyReference = Cast<ARootBattleSystemCharacter>(allyActor)) {
			alliesReferences.Add(countPosition, allyReference);
			countPosition++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("NUMBER OF ALLIES: %d"), enemiesReferences.Num());
}



//====================================================
// Exposed Functions

TArray<ARootBattleSystemCharacter*> ABattleSystemGM::getSelectableEnemiesReferences()
{
	// TODO: This must only return selectable enemys for the camera
	return enemiesReferences;
}

ARootBattleSystemCharacter* ABattleSystemGM::getSelectedEnemyRef()
{
	return (selectedEnemyRef != nullptr) ? selectedEnemyRef : selectNextEnemyRef();
}

ARootBattleSystemCharacter* ABattleSystemGM::selectNextEnemyRef()
{
	return ChangeEnemyRef(1);
}

ARootBattleSystemCharacter* ABattleSystemGM::selectPreviousEnemyRef()
{
	return ChangeEnemyRef(-1);
}

ARootBattleSystemCharacter* ABattleSystemGM::getAllyRefByPosition(int8 position)
{
	return (alliesReferences.Contains(position)) 
		? * alliesReferences.Find(position) : nullptr;
}

int8 ABattleSystemGM::getPositionOfAllyRef(ARootBattleSystemCharacter* ally)
{
	return *alliesReferences.FindKey(ally);
}

//====================================================
// Internal Battle System Functions

ARootBattleSystemCharacter* ABattleSystemGM::ChangeEnemyRef(int direction)
{
	int32 selectedEnemyIndex;

	if (selectedEnemyRef != nullptr
		&& enemiesReferences.Find(selectedEnemyRef, selectedEnemyIndex))
	{
		// TODO Needs a Util to wrap this silly logic to get the next element without worrying about OutBoundaries
		if (direction == 1) {
			selectedEnemyRef = (selectedEnemyIndex == enemiesReferences.Num() - 1)
				? enemiesReferences[0] : enemiesReferences[selectedEnemyIndex + direction];
		}
		else {
			selectedEnemyRef = (selectedEnemyIndex == 0)
				? enemiesReferences.Last() : enemiesReferences[selectedEnemyIndex + direction];
		}
		return selectedEnemyRef;
	}
	else
	{
		selectedEnemyRef = enemiesReferences[0];
		return selectedEnemyRef;
	}
}