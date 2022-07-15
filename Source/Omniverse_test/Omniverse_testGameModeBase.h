// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Utilities/CellFunctionLibrary.h"
#include "Omniverse_testGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FCellOptions
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Limit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int HitHP;
};

USTRUCT(BlueprintType)
struct FCellSetup
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap < ECellZone, FCellOptions > CellOptions;
};

UCLASS()
class OMNIVERSE_TEST_API AOmniverse_testGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AOmniverse_testGameModeBase();

protected:
	virtual void StartPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
		TMap<ECellType, FCellSetup> CellSetup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/* Sector Size Persent */
		TMap<ECellZone, int> CellSectorsSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint FieldSize = (10,10);
	UPROPERTY(EditDefaultsOnly)
		TMap<ECellZone, UMaterialInstance*> ZoneMaterials;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int FieldStrength = (10, 10);
};
