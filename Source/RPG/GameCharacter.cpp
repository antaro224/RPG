// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"
#include "RPG.h"
#include "CombatEngine.h"

UGameCharacter* UGameCharacter::CreateGameCharacter(FCharacterInfo* characterInfo, UObject* outer)
{
	UGameCharacter* character = NewObject<UGameCharacter>(outer);

	// Locate character classes asset
	UDataTable* characterClasses = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT(
		"DataTable'/Game/Data/CharacterClasses.CharacterClasses'")));

	if (characterClasses == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Character classes datatable not found!"));
	}
	else
	{
		character->CharacterName = characterInfo->Character_Name;
		FCharacterClassInfo* row = characterClasses->FindRow<FCharacterClassInfo>(*(characterInfo->Class_ID),
			TEXT("LookupCharacterClass"));
		character->ClassInfo = row;

		character->MHP = character->ClassInfo->StartMHP;
		character->MMP = character->ClassInfo->StartMMP;
		character->HP = character->MHP;
		character->MP = character->MMP;

		character->ATK = character->ClassInfo->StartATK;
		character->DEF = character->ClassInfo->StartDEF;
		character->LUCK = character->ClassInfo->StartLuck;
	}

	return character;
}

void UGameCharacter::BeginDestroy()
{
	Super::BeginDestroy();
}

void UGameCharacter::BeginMakeDecision()
{
	UE_LOG(LogTemp, Log, TEXT("Character %s making decision"), *this->CharacterName);
	this->testDelayTimer = 1;
}

bool UGameCharacter::MakeDecision(float DeltaSeconds)
{
	this->testDelayTimer -= DeltaSeconds;
	return this->testDelayTimer <= 0;
}

void UGameCharacter::BeginExecuteAction()
{
	UE_LOG(LogTemp, Log, TEXT("Character %s executing action"), *this->CharacterName);
	this->testDelayTimer = 1;
}

bool UGameCharacter::ExecuteAction(float DeltaSeconds)
{
	this->testDelayTimer -= DeltaSeconds;
	return this->testDelayTimer <= 0;
}

UGameCharacter* UGameCharacter::CreateGameCharacter(FEnemyInfo* enemyInfo, UObject* outer)
{
	UGameCharacter* character = NewObject<UGameCharacter>(outer);

	character->CharacterName = enemyInfo->EnemyName;
	character->ClassInfo = nullptr;

	character->MHP = enemyInfo->MHP;
	character->MMP = 0;
	character->HP = enemyInfo->MHP;
	character->MP = 0;

	character->ATK = enemyInfo->ATK;
	character->DEF = enemyInfo->DEF;
	character->LUCK = enemyInfo->Luck;

	return character;
}