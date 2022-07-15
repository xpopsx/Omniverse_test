// Fill out your copyright notice in the Description page of Project Settings.


#include "CellManager.h"
#include "CellActor.h"
#include "DrawDebugHelpers.h" 
#include "Omniverse_test/Omniverse_testGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogCellManager, All, All);

// Sets default values
ACellManager::ACellManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACellManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACellManager::InitSpawn()
{
	if (!GetWorld()) return false;
	auto CellGameMode = Cast<AOmniverse_testGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!CellGameMode) return false;

#pragma region MakingArrayCellObject
	FIntPoint FieldSize = CellGameMode->FieldSize - 1;

	int Row = FieldSize.X / 2;
	int Column = FieldSize.Y / 2;

	int ColumnSign = 1;
	int RowSign = 0;

	int FieldIntSize = FieldSize.X * FieldSize.Y;

	ArrayField.AddDefaulted(FieldIntSize);

	int StepX = 1; int StepY = 2;

	for (int i = 0; i < FieldIntSize; i++)
	{
		ArrayField[i].Row = Row;
		ArrayField[i].Column = Column;

		Column += ColumnSign;
		Row += RowSign;
		if (RowSign == 0)
		{
			switch (ColumnSign)
			{
			case 1:
				if (Column >= (FieldSize.Y / 2 + StepY))
				{
					Row++;
					RowSign = 1;
					Column--;
					ColumnSign = 0;
				}
				break;
			case -1:
				if (Column <= FieldSize.Y / 2 - StepY)
				{
					Row--;
					RowSign = -1;
					Column++;
					ColumnSign = 0;
					StepX++;
				}
				break;
			default:
				break;
			}
		}
		if (ColumnSign == 0)
		{
			switch (RowSign)
			{
			case 1:
				if (Row >= (FieldSize.X / 2 + StepX))
				{
					RowSign = 0;
					ColumnSign = -1;
				}
				break;
			case -1:
				if (Row <= FieldSize.X / 2 - StepX)
				{
					RowSign = 0;
					Row++;
					Column++;
					ColumnSign = 1;
					StepY++;
				}
				break;
			default:
				break;
			}
		}
	}
#pragma endregion
#pragma region GenerateBannedCellArray
	TArray<FFielStruct> BannedCells;
	int RandomBannedColumn = FMath::RandRange(0.0f, (float)FieldSize.Y);
	for (int j = 0; j <= FieldSize.X; j++)
	{
		auto index = BannedCells.AddDefaulted(1);
		BannedCells[index].Row = j;
		BannedCells[index].Column = RandomBannedColumn;

#if WITH_EDITOR
		DEBUG_BannedLine.Add(BannedCells[index]);
#endif

	}
#pragma endregion

	for (int i = 0; i < ArrayField.Num(); i++)
	{
		ECellZone CurrentZone;
#pragma region FindCurrentZone
		if (i < *CellGameMode->CellSectorsSize.Find(ECellZone::Red))
		{
			CurrentZone = ECellZone::Red;
		}
		else if (*CellGameMode->CellSectorsSize.Find(ECellZone::Red) <= i && i < *CellGameMode->CellSectorsSize.Find(ECellZone::Yellow))
		{
			CurrentZone = ECellZone::Yellow;
		}
		else
		{
			CurrentZone = ECellZone::Green;
		}
#pragma endregion

		int RandCellType = FMath::RandRange(0.f, (float)ECellType::MAX - 1);


		if (!bSkipCellCheck)
		{


			if (BannedCells.FindByPredicate([&](FFielStruct x) {return x.Row == ArrayField[i].Row && x.Column == ArrayField[i].Column; })) continue;

			while (RandCellType > -1)
			{
				if (CellGameMode->CellSetup.Find((ECellType)RandCellType)->CellOptions.Find(CurrentZone)->Limit != -1)
				{
					if (CellActorsArray.FilterByPredicate([&](ACellActor* x) {return x->CellZone == CurrentZone, x->CellObjectType == (ECellType)RandCellType; }).Num()
						>= CellGameMode->CellSetup.Find((ECellType)RandCellType)->CellOptions.Find(CurrentZone)->Limit)
					{
						RandCellType--;
						continue;
					}
				}
				if (UCellFunctionLibrary::RandomBoolWithWeight(UCellFunctionLibrary::GetCellWeight(GetWorld(), (ECellType)RandCellType, CurrentZone))) break;
				else RandCellType--;
			}

			if (RandCellType < 0) continue;

			bool bCantBeSpawned = false;
			for (auto& BanCell : UCellFunctionLibrary::GetCellType((ECellType)RandCellType))
			{
				if (BannedCells.FindByPredicate([&](FFielStruct x) {return x.Row == ArrayField[i].Row + BanCell.Key && x.Column == ArrayField[i].Column + BanCell.Value; }))
				{
					bCantBeSpawned = true;
					break;
				}
			}

			if (bCantBeSpawned) continue;

			TMultiMap<int, int> CellMapForBanned = UCellFunctionLibrary::GetCellType((ECellType)RandCellType);
			for (auto& BanCell : CellMapForBanned)
			{
				for (int k = -1; k <= 1; k++)
				{
					for (int p = -1; p <= 1; p++)
					{
						int BanCellRow = ArrayField[i].Row + BanCell.Key + k;
						int BanCellColumn = ArrayField[i].Column + BanCell.Value + p;
						if (BanCellRow < 0 || BanCellColumn < 0) continue;
						if (BanCellRow > FieldSize.X || BanCellColumn > FieldSize.Y) continue;

						int index = BannedCells.AddDefaulted(1);
						BannedCells[index].Row = BanCellRow;
						BannedCells[index].Column = BanCellColumn;

#if WITH_EDITOR
						DEBUG_BannedCells.Add(BannedCells[index]);
#endif
					}
				}
			}
		}

		/* cell actor generation */

		FTransform CellTransform = FTransform::Identity;
		CellTransform.SetLocation(FVector(ArrayField[i].Row * 100, ArrayField[i].Column * 100, 0.f));
		auto Actor = GetWorld()->SpawnActorDeferred<ACellActor>(ACellActor::StaticClass(), CellTransform);
		Actor->CellObjectType = bSkipCellCheck ? ECellType::One : (ECellType)RandCellType;
		TArray<ECellZone> CellUEnumArray;
		CellGameMode->CellSectorsSize.GenerateKeyArray(CellUEnumArray);
		Actor->CellMaterial = *CellGameMode->ZoneMaterials.Find(CurrentZone);
		Actor->CellHP = CellGameMode->CellSetup.Find((ECellType)RandCellType)->CellOptions.Find(CurrentZone)->HitHP;
		FieldHP += Actor->CellHP;
		Actor->FinishSpawning(CellTransform);
		CellActorsArray.Add(Actor);
	}

	return true;
}

void ACellManager::ClearCells()
{
	for (auto& CellActor : CellActorsArray)
	{
		CellActor->Destroy();
	};
	CellActorsArray.Empty();
	ArrayField.Empty();
	FieldHP = 0;

#if WITH_EDITOR
	DEBUG_BannedCells.Empty();
	DEBUG_BannedLine.Empty();
#endif
}

void ACellManager::ShowDebugInfo(bool bBanLine, bool bBanCells)
{
#if WITH_EDITOR
	DEBUG_BannedCells;
	DEBUG_BannedLine;

	if (!GetWorld()) return;
	if (bBanLine)
	{
		for (auto& Cell : DEBUG_BannedLine)
		{
			FVector Center = FVector(Cell.Row * 100, Cell.Column * 100, 0);
			DrawDebugBox(GetWorld(), Center, FVector(50.f, 50.f, 50.f), FColor::Red, false, 1.f, 0U, 10);
		}
	}
	if (bBanCells)
	{
		for (auto& Cell : DEBUG_BannedCells)
		{
			FVector Center = FVector(Cell.Row * 100, Cell.Column * 100, 0);
			DrawDebugBox(GetWorld(), Center, FVector(50.f, 50.f, 50.f), FColor::Red, false, 1.f, 0U, 10);
		}
	}
#endif
}

