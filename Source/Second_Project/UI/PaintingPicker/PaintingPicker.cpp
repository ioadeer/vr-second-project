// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"
#include "ActionBar.h"
#include "../../Saving/PainterSaveGameIndex.h"
#include "../../Saving/PainterSaveGame.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget)
	{
		ActionBarWidget->SetParentPicker(this);
	}
	Refresh();
}

void APaintingPicker::RefreshSlots()
{
	UE_LOG(LogTemp, Warning, TEXT("Number of pages %d"), GetNumberOfPages());

	UPaintingGrid* PaintingGridWidget = GetPaintingGrid();
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaintings();

	int32 StartOffset = CurrentPage * PaintingGridWidget->GetNumberOfSlots();
	auto SlotNames = UPainterSaveGameIndex::Load()->GetSlotNames();
	for (int32 i = 0; i < PaintingGridWidget->GetNumberOfSlots() && StartOffset + i < SlotNames.Num(); ++i)
	{
		PaintingGridWidget->AddPainting(i, SlotNames[StartOffset+i]);
	}
}

void APaintingPicker::RefreshDots()
{
	UPaintingGrid* PaintingGridWidget = GetPaintingGrid();
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaginationDots();

	for (int32 i = 0; i < GetNumberOfPages(); i++)
	{
		PaintingGridWidget->AddPaginationDot(CurrentPage == i);
	}

}

int32 APaintingPicker::GetNumberOfPages() const
{
	if (!GetPaintingGrid()) return 0;
	int32 TotalNumberOfSlot = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
	int32 SlotsPerPage = GetPaintingGrid()->GetNumberOfSlots();
	return FMath::CeilToInt((float) TotalNumberOfSlot / SlotsPerPage);
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame::Create();
	Refresh();
}

void APaintingPicker::ToggleDeleteMode()
{
	UPaintingGrid* PaintingGridWidget = GetPaintingGrid();
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaintings();
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage+Offset,0,GetNumberOfPages()- 1);
	Refresh();
}
