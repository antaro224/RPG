// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "GameCharacter.h"
#include "CombatEngine.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "RPGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ARPGGameMode(const class FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(exec)
	void TestCombat();

public:
	CombatEngine* currentCombatInstance;
	TArray<UGameCharacter*> enemyParty;
};
