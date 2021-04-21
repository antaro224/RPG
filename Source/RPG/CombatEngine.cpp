// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatEngine.h"

CombatEngine::CombatEngine(TArray<UGameCharacter*> playerParty, TArray<UGameCharacter*> enemyParty)
{
	this->playerParty = playerParty;
	this->enemyParty = enemyParty;

	// First add all players to combat order
	for (int i = 0; i < playerParty.Num(); i++)
	{
		this->combatantOrder.Add(playerParty[i]);
	}

	// Next add all enemies to combat order
	for (int i = 0; i < enemyParty.Num(); i++)
	{
		this->combatantOrder.Add(enemyParty[i]);
	}

	this->tickTargetIndex = 0;
	this->SetPhase(CombatPhase::CPHASE_Decision);

	for (int i = 0; i < this->combatantOrder.Num(); i++)
	{
		this->combatantOrder[i]->combatInstance = this;
	}

	this->tickTargetIndex = 0;
	this->SetPhase(CombatPhase::CPHASE_Decision);
}

CombatEngine::~CombatEngine()
{
	// Free enemies
	for (int i = 0; i < this->enemyParty.Num(); i++)
	{
		this->enemyParty[i] = nullptr;
	}

	for (int i = 0; i < this->combatantOrder.Num(); i++)
	{
		this->combatantOrder[i]->combatInstance = nullptr;
	}
}

bool CombatEngine::Tick(float DeltaSeconds)
{
	UE_LOG(LogTemp, Log, TEXT("CombatEngine Ticking"));
	switch (Cphase)
	{
		case CombatPhase::CPHASE_Decision:
		{
			if (!this->waitingForCharacter)
			{
				this->currentTickTarget->BeginMakeDecision();
				this->waitingForCharacter = true;
			}

			bool decisionMade = this->currentTickTarget->MakeDecision(DeltaSeconds);

			if (decisionMade)
			{
				SelectNextCharacter();

				// No next character, switch to action phase
				if (this->tickTargetIndex == -1)
				{
					this->SetPhase(CombatPhase::CPHASE_Action);
				}
			}
		}
		break;

		case CombatPhase::CPHASE_Action:
		{
			if (!this->waitingForCharacter)
			{
				this->currentTickTarget->BeginExecuteAction();
				this->waitingForCharacter = true;
			}

			bool actionFinished = this->currentTickTarget->ExecuteAction(DeltaSeconds);
	
			if (actionFinished)
			{
				SelectNextCharacter();

				// No next character, switch to action phase
				if (this->tickTargetIndex == -1)
				{
					this->SetPhase(CombatPhase::CPHASE_Decision);
				}
			}
		}
		break;

		// In case of victory or combat, return true (combat is finsihed)
		case CombatPhase::CPHASE_GameOver:
		case CombatPhase::CPHASE_Victory:
			return true;
			break;
	}

	// Check for game over
	int deadCount = 0;
	for (int i = 0; i < this->playerParty.Num(); i++)
	{
		if (this->playerParty[i]->HP <= 0) deadCount++;
	}

	// All players have died, switch to game over phase
	if (deadCount == this->playerParty.Num())
	{
		this->SetPhase(CombatPhase::CPHASE_GameOver);
		return false;
	}

	// Check for victory
	deadCount = 0;
	for (int i = 0; i < this->enemyParty.Num(); i++)
	{
		if (this->enemyParty[i]->HP <= 0) deadCount++;
	}

	// All enemies have died, switch to victory phase
	if (deadCount == this->enemyParty.Num())
	{
		this->SetPhase(CombatPhase::CPHASE_Victory);
		return false;
	}

	// If execution reaches here, combat has not finished return false
	return false;
}

void CombatEngine::SetPhase(CombatPhase phase)
{
	this->Cphase = phase;

	switch (phase)
	{
	case CombatPhase::CPHASE_Action:
	case CombatPhase::CPHASE_Decision:
		// Set the active target to the first character in the combat order
		this->tickTargetIndex = 0;
		this->SelectNextCharacter();
		break;
	case CombatPhase::CPHASE_Victory:
		// todo: handle victory
		break;
	case CombatPhase::CPHASE_GameOver:
		// todo: handle game over
		break;
	}
}

void CombatEngine::SelectNextCharacter()
{
	this->waitingForCharacter = false;
	for (int i = this->tickTargetIndex; i < this->combatantOrder.Num(); i++)
	{
		UGameCharacter* character = this->combatantOrder[i];

		if (character->HP > 0)
		{
			this->tickTargetIndex = i + 1;
			this->currentTickTarget = character;
			return;
		}
	}

	this->tickTargetIndex = -1;
	this->currentTickTarget = nullptr;
}
