// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"
#include "ActionBar.h"
#include "PaintingGrid.h"
#include "PainterSaveGameIndex.h"
#include "LightPainterSaveGame.h"


// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(GetRootComponent());
}

void APaintingPicker::AddPainting()
{
	ULightPainterSaveGame::Create();

	Refresh();
}

void APaintingPicker::ToggleDeleteMode()
{
	if (!GetPaintingGrid()) return;
	GetPaintingGrid()->ClearPaintings();
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, GetNumberOfPages() - 1);

	Refresh();
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
	if (!GetPaintingGrid()) return;

	GetPaintingGrid()->ClearPaintings();

	int32 StartOffset = CurrentPage * GetPaintingGrid()->GetNumberOfSlots();
	int32 PaintingIndex = 0;

	auto SlotNames = UPainterSaveGameIndex::Load()->GetSlotNames();

	for (int32 i = 0; i < GetPaintingGrid()->GetNumberOfSlots() && StartOffset + i < SlotNames.Num(); ++i) //second condition there so you don't iterate past the end of the array
	{
		GetPaintingGrid()->AddPainting(i, SlotNames[StartOffset + i]); //will go in interverals of 9
	}
}

void APaintingPicker::RefreshDots()
{
	if (!GetPaintingGrid()) return;
	GetPaintingGrid()->ClearPaginationDots();

	for (int32 i = 0; i < GetNumberOfPages(); ++i)
	{
		GetPaintingGrid()->AddPaginationDot(CurrentPage == i);
	}
}


int32 APaintingPicker::GetNumberOfPages() const
{
	if (!GetPaintingGrid()) return 0;
	int32 TotalNumberOfSlots = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
	int32 SlotsPerPage = GetPaintingGrid()->GetNumberOfSlots();
	return FMath::CeilToInt((float)TotalNumberOfSlots / SlotsPerPage); //parantheses is a C Style cast to return a float, that then gets rounded up (ceiling)
}

UPaintingGrid* APaintingPicker::GetPaintingGrid() const
{
	return Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
}

