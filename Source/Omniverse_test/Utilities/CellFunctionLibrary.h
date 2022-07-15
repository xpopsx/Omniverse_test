// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CellFunctionLibrary.generated.h"

USTRUCT()
struct FCellObjectColor
{
	GENERATED_USTRUCT_BODY()

		static FLinearColor GetZoneColor(ECellZone Zone)
	{
		TArray<FLinearColor> ColorArray = {
			FLinearColor(0.822786f, 0.318547f, 0.318547f, 1.000000f),
			FLinearColor(1.000000, 0.783538, 0.318547, 1.000000),
			FLinearColor(0.467784, 0.679542, 0.391572, 1.000000)
		};

		return ColorArray[(uint8)Zone];
	}
};


UENUM(BlueprintType)
enum class ECellZone : uint8
{
	Red = 0,
	Yellow = 1,
	Green = 2
};

UENUM(BlueprintType)
enum class ECellType : uint8
{
	One = 0,
	Two = 1,
	Triple = 2,
	TShape = 3,
	Square = 4,
	MAX
};


UCLASS()
class OMNIVERSE_TEST_API UCellFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		/* return TMap of row & columns for Cell Type*/
		static TMultiMap<int, int> GetCellType(const ECellType Type);
		/* get false if Rand not in*/
		static bool RandomBoolWithWeight(float Weight);
		static float GetCellWeight(UObject* World, const ECellType Type,const ECellZone Zone);
};
