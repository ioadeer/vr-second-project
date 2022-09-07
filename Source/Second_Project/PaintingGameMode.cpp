// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Saving/PainterSaveGame.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

void APaintingGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SlotName = UGameplayStatics::ParseOption(Options, TEXT("SlotName"));
	UE_LOG(LogTemp, Warning,TEXT("SlotName: %s"), *SlotName);
}

void APaintingGameMode::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
	}
}

void APaintingGameMode::Load()
{
	UPainterSaveGame* LoadedPainting = UPainterSaveGame::Load(SlotName);
	if (LoadedPainting)
	{
		LoadedPainting->DeserializeToWorld(GetWorld());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not found: %s"), *SlotName);
	}
}

void APaintingGameMode::SaveAndQuit()
{
	Save();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();
	Load();
	UStereoLayerFunctionLibrary::HideSplashScreen();
}
