// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG.h"
#include "RPGGameMode.h"
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