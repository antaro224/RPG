// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FCharacterInfo.h"
#include "FCharacterClassInfo.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameCharacter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RPG_API UGameCharacter : public UObject
{
	GENERATED_BODY()
	
	public:
		FCharacterClassInfo* ClassInfo;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			FString CharacterName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			int32 MHP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			int32 MMP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			int32 HP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			int32 MP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			int32 ATK;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			int32 DEF;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
			int32 LUCK;


		static UGameCharacter* CreateGameCharacter(FCharacterInfo* characterInfo, UObject* outer);

		void BeginDestroy() override;
};
