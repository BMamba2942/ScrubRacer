// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScrubRacerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SCRUBRACER_API AScrubRacerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void GameStart();
	void GameOver();
	
};
