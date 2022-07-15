// Fill out your copyright notice in the Description page of Project Settings.


#include "CellActor.h"
#include "CellObject.h"

// Sets default values
ACellActor::ACellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootScene = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(RootScene);

	///* Cell Cant be less that 1 cell*/
	//UCellObject* CellObject = CreateDefaultSubobject<UCellObject>("RootCell");
	//this->SetRootComponent(CellObject);
	//CellComponents.Add(CellObject);
}

// Called when the game starts or when spawned
void ACellActor::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) return;
	int CellCouter = 0;

	for (auto CellElem : UCellFunctionLibrary::GetCellType(CellObjectType))
	{
		UCellObject* CellComponent = NewObject<UCellObject>(this, *FString::Printf(TEXT("Cell_%i"), CellCouter));
		CellComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		CellComponent->SetRelativeLocation(FVector(CellElem.Key * CellUnitSize, CellElem.Value * CellUnitSize, 0));
		CellComponent->SetMaterial(0, CellMaterial);
		CellComponent->RegisterComponent();
		CellCouter++;
	}

}

// Called every frame
void ACellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACellActor::MakeDamage()
{
	if (CellHP == -1) return;
}

