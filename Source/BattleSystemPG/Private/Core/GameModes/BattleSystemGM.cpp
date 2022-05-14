// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameModes/BattleSystemGM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BattleSystemPG/Public/Core/Characters/RootBattleSystemCharacter.h"

void ABattleSystemGM::StartPlay()
{
	Super::StartPlay();
		
	SetupAllEnemys();
	
}

//====================================================
// Setting up Battle System Functions

void ABattleSystemGM::SetupAllEnemys() {

	TArray<AActor*> enemyActorReferences;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARootBattleSystemCharacter::StaticClass(), enemyActorReferences);

	for (AActor* enemyActor : enemyActorReferences) {
		if (ARootBattleSystemCharacter* enemyReference = Cast<ARootBattleSystemCharacter>(enemyActor)) {
			enemysReferences.Push(enemyReference);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("NUMBER OF ENEMYS: %d"), enemysReferences.Num());
	
}



//====================================================
// Exposed Functions

TArray<ARootBattleSystemCharacter*> ABattleSystemGM::getSelectableEnemysReferences()
{
	// TODO: This must only return selectable enemys for the camera
	return enemysReferences;
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

//====================================================
// Internal Battle System Functions

ARootBattleSystemCharacter* ABattleSystemGM::ChangeEnemyRef(int direction)
{
	int32 selectedEnemyIndex;

	if (selectedEnemyRef != nullptr
		&& enemysReferences.Find(selectedEnemyRef, selectedEnemyIndex))
	{
		// TODO Needs a Util to wrap this silly logic to get the next element without worrying about OutBoundaries
		if (direction == 1) {
			selectedEnemyRef = (selectedEnemyIndex == enemysReferences.Num() - 1)
				? enemysReferences[0] : enemysReferences[selectedEnemyIndex + direction];
		}
		else {
			selectedEnemyRef = (selectedEnemyIndex == 0)
				? enemysReferences.Last() : enemysReferences[selectedEnemyIndex + direction];
		}
		return selectedEnemyRef;
	}
	else
	{
		selectedEnemyRef = enemysReferences[0];
		return selectedEnemyRef;
	}
}