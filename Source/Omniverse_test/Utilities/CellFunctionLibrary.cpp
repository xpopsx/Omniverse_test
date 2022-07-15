// Fill out your copyright notice in the Description page of Project Settings.


#include "CellFunctionLibrary.h"
#include "Omniverse_test/Omniverse_testGameModeBase.h"

bool UCellFunctionLibrary::RandomBoolWithWeight(float Weight)
{
	if (Weight <= 0.0f) return false;
	return Weight >= FMath::FRandRange(0.0f, 1.0f);
}

float UCellFunctionLibrary::GetCellWeight(UObject* World, const ECellType Type, const ECellZone Zone)
{
	if (!World) return 0.0f;
	auto CellGameMode = Cast<AOmniverse_testGameModeBase>(World->GetWorld()->GetAuthGameMode());
	if (!CellGameMode) return 0.0f;
	int CellConfig = CellGameMode->CellSetup.Find(Type)->CellOptions.Find(Zone)->Weight;
	return CellConfig * 0.01;
}

TMultiMap<int, int> UCellFunctionLibrary::GetCellType(const ECellType Type)
{
	TMultiMap<int, int> ReturnType;
	switch (Type)
	{
	case ECellType::One:
		ReturnType.Add(0, 0);
		break;
	case ECellType::Two:
		ReturnType.Add(0, 0);
		ReturnType.Add(0, 1);
		break;
	case ECellType::Triple:
		ReturnType.Add(1, 0);
		ReturnType.Add(1, 1);
		ReturnType.Add(0, 1);
		break;
	case ECellType::TShape:
		ReturnType.Add(1, 0);
		ReturnType.Add(1, 1);
		ReturnType.Add(1, 2);
		ReturnType.Add(0, 1);
		break;
	case ECellType::Square:
		ReturnType.Add(1, 0);
		ReturnType.Add(1, 1);
		ReturnType.Add(0, 1);
		ReturnType.Add(0, 0);
		break;
	default:
		break;
	}
	return ReturnType;
}
