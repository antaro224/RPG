// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG.h"
#include "GameCharacter.h"

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