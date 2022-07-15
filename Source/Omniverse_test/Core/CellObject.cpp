// Fill out your copyright notice in the Description page of Project Settings.


#include "CellObject.h"
#include "Materials/MaterialInstance.h"

UCellObject::UCellObject()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CellMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	this->SetStaticMesh(CellMesh.Object);

}
