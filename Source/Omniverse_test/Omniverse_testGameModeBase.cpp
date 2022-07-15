// Copyright Epic Games, Inc. All Rights Reserved.


#include "Omniverse_testGameModeBase.h"
#include "Core/CellManager.h"
#include "Core/CellPawn.h"

AOmniverse_testGameModeBase::AOmniverse_testGameModeBase()
{
	DefaultPawnClass = ACellPawn::StaticClass();
}

void AOmniverse_testGameModeBase::StartPlay()
{
	Super::StartPlay();
	if (GetWorld()) 
	{
		auto CellManager = GetWorld()->SpawnActor<ACellManager>();
		CellManager->InitSpawn();
	}
}
