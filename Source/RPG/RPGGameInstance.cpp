// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGGameInstance.h"
#include "RPG.h"

URPGGameInstance::URPGGameInstance(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	isInitialized = false;
}

void URPGGameInstance::Init()
{
	if (this->isInitialized) return;

	this->isInitialized = true;

	// Locate characters asset
	UDataTable* characters = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL,
		TEXT("DataTable'/Game/Data/Characters.Characters'")));
	if (characters == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Characters data table not found!"));

		return;
	}

	// Locate character
	FCharacterInfo* row = characters->FindRow<FCharacterInfo>(TEXT("S1"), TEXT("LookupCharacterClass"));

	if (row == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Character ID 'S1' not found!"));
		return;
	}

	// Add character to party
	this->PartyMembers.Add(UGameCharacter::CreateGameCharacter(row, this));
}