// Fill out your copyright notice in the Description page of Project Settings.


#include "CellPawn.h"
#include "Camera/CameraComponent.h" 
#include "Omniverse_test/Omniverse_testGameModeBase.h"
#include "Blueprint/UserWidget.h" 

// Sets default values
ACellPawn::ACellPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->SetRootComponent(Camera);
}

// Called when the game starts or when spawned
void ACellPawn::BeginPlay()
{
	Super::BeginPlay();
	if (!GetWorld()) return;
	auto CurrGameMode = Cast<AOmniverse_testGameModeBase>(GetWorld()->GetAuthGameMode());
	if (CurrGameMode)
	{
		FIntPoint Size = CurrGameMode->FieldSize;
		float Height = 2000.f;
		this->SetActorLocation(FVector(Size.X / 2 * 100, Size.Y / 2 * 100, Height));
		this->SetActorRotation(FRotator(-90.f, 0.f, 0.f));
	}



}

void ACellPawn::PossessedBy(AController* NewController)
{
	if (NewController->IsPlayerController()) 
	{
		FStringClassReference WidgetAsset(TEXT("WidgetBlueprint'/Game/UMG/W_MainWidget.W_MainWidget_C'"));
		UClass* WidgetClass = WidgetAsset.TryLoadClass<UUserWidget>();
		auto PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass, TEXT("UserWidget"));
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
		}
	}
}


