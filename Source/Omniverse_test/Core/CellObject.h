// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h" 
#include "Omniverse_test/Utilities/CellFunctionLibrary.h"
#include "CellObject.generated.h"


UCLASS()
class OMNIVERSE_TEST_API UCellObject : public UStaticMeshComponent
{
GENERATED_BODY()
public:
	UCellObject();

	UPROPERTY(VisibleAnywhere)
		TArray<UStaticMeshComponent*> Cell_Array_SM;
	UPROPERTY(EditDefaultsOnly)
		ECellZone CellZone;
};
