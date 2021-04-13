// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameMode.h"
#include "RPGCharacter.h"

ARPGGameMode::ARPGGameMode(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	DefaultPawnClass = ARPGCharacter::StaticClass();
}