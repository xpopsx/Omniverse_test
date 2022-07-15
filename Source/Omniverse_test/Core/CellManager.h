// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellManager.generated.h"

USTRUCT()
struct FFielStruct
{
	GENERATED_BODY()
public:
	int Row;
	int Column;
};

class ACellActor;

UCLASS()
class OMNIVERSE_TEST_API ACellManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACellManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	/* Return false if not init spawn cells */
	bool InitSpawn();
	UFUNCTION(BlueprintCallable)
	/* Clear Existing Assets*/
	void ClearCells();

	UFUNCTION(BlueprintCallable)
		void ShowDebugInfo(bool bBanLine, bool bBanCells);

	UPROPERTY(BlueprintReadWrite)
		bool bSkipCellCheck;

	UPROPERTY(BlueprintReadOnly)
		int FieldHP;
private:
	TArray<FFielStruct> ArrayField;
	UPROPERTY()
	TArray<ACellActor*> CellActorsArray;

#if WITH_EDITOR
	TArray<FFielStruct> DEBUG_BannedCells;
	TArray<FFielStruct> DEBUG_BannedLine;
#endif

};
