// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "../Stroke.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"
#include "Engine/World.h" 
#include "PainterSaveGameIndex.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if (!NewSaveGame->Save()) return nullptr;

	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	Index->AddSaveGame(NewSaveGame);
	Index->Save();

	return NewSaveGame;
}

bool UPainterSaveGame::Save()
{

	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame* UPainterSaveGame::Load(FString SlotName)
{ 
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	Strokes.Empty();
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		//TODO Serialize
		Strokes.Add(StrokeItr->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	//Clear world
	//For all stroke
	//Spawn stroke of that type
	ClearWorld(World);
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		//TODO Serialize
		StrokeItr->Destroy();
	}
}
