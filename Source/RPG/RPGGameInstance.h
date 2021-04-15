// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

	URPGGameInstance(const class FObjectInitializer& ObjectInitializer);

	public:
		TArray<UGameCharacter*> PartyMembers;

	protected:
		bool isInitialized;

	public:
		void Init();
};
