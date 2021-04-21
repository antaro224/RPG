// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPG.h"
#include "GameCharacter.h"
#include "CoreMinimal.h"

enum class CombatPhase : uint8
{
	CPHASE_Decision,
	CPHASE_Action,
	CPHASE_Victory,
	CPHASE_GameOver,
};

/**
 * 
 */
class RPG_API CombatEngine
{
public:
	TArray<UGameCharacter*> combatantOrder;
	TArray<UGameCharacter*> playerParty;
	TArray<UGameCharacter*> enemyParty;

	CombatPhase Cphase;

protected:
	UGameCharacter* currentTickTarget;
	int tickTargetIndex;

public:
	CombatEngine(TArray<UGameCharacter*> playerParty, TArray<UGameCharacter*> enemyParty);
	~CombatEngine();

	bool Tick(float DeltaSeconds);

protected:
	void SetPhase(CombatPhase Cphase);
	void SelectNextCharacter();
	bool waitingForCharacter;
};
