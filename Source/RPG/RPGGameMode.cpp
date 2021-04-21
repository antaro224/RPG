// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGGameMode.h"
#include "RPG.h"
#include "RPGCharacter.h"
#include "RPGGameInstance.h"

ARPGGameMode::ARPGGameMode(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	DefaultPawnClass = ARPGCharacter::StaticClass();
}

void ARPGGameMode::BeginPlay()
{
	Cast<URPGGameInstance>(GetGameInstance())->Init();
}

void ARPGGameMode::Tick(float DeltaTime)
{
	if (this->currentCombatInstance != nullptr)
	{
		bool combatOver = this->currentCombatInstance->Tick(DeltaTime);
		if (combatOver)
		{
			if (this->currentCombatInstance->Cphase == CombatPhase::CPHASE_GameOver)
			{
				UE_LOG(LogTemp, Log, TEXT("Player loses combat, game over"));
			}
			else if (this->currentCombatInstance->Cphase == CombatPhase::CPHASE_Victory)
			{
				UE_LOG(LogTemp, Log, TEXT("Player wins combat"));
			}

			// Enable player actor
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(true);

			delete(this->currentCombatInstance);
			this->currentCombatInstance = nullptr;
			this->enemyParty.Empty();
		}
	}
}

void ARPGGameMode::TestCombat()
{
	// Locate enemies asset
	UDataTable* enemyTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL,
		TEXT("DataTable'/Game/Data/Enemies.Enemies'")));

	if (enemyTable == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemies data table not found!"));
		return;
	}

	// Locate enemy
	FEnemyInfo* row = enemyTable->FindRow<FEnemyInfo>(TEXT("S1"), TEXT("LookupEnemyInfo"));

	if (row == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy ID 'S1' not found!"));
		return;
	}

	// Disable player actor
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(false);

	// Add character to enemy party
	UGameCharacter* enemy = UGameCharacter::CreateGameCharacter(row, this);
	this->enemyParty.Add(enemy);

	URPGGameInstance* gameInstance = Cast<URPGGameInstance>(GetGameInstance());

	this->currentCombatInstance = new CombatEngine(gameInstance->PartyMembers, this->enemyParty);

	UE_LOG(LogTemp, Log, TEXT("Combat started"));
}