// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Omniverse_test/Utilities/CellFunctionLibrary.h"
#include "CellActor.generated.h"

class UCellObject;
UCLASS()
class OMNIVERSE_TEST_API ACellActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACellActor();

	UPROPERTY(VisibleAnywhere)
		USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere)
		TArray<UCellObject*> CellComponents;

	UPROPERTY(EditDefaultsOnly)
		ECellType CellObjectType = ECellType::Triple;

	UPROPERTY(VisibleAnywhere)
		float CellUnitSize = 100.f;

	UPROPERTY(VisibleAnywhere)
		ECellZone CellZone;

	UPROPERTY()
		UMaterialInstance* CellMaterial;

		int CellHP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MakeDamage();
};
