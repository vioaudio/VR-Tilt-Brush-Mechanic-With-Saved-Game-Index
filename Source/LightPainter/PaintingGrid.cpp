// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBoxSlot.h"

void UPaintingGrid::AddPainting(int32 PaintingIndex, FString PaintingName)
{
	if (!PaintingGrid) return;
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass); //creates painting, or new grid card
	if (!NewWidget) return;

	NewWidget->SetPaintingName(PaintingName);

	USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(PaintingIndex)); //Get the first child of the painting grid, then cast it to a size box
	if (!CardContainer) return;
	CardContainer->AddChild(NewWidget); //add grid card as child to the size box

}

void UPaintingGrid::ClearPaintings()
{
	for (int32 i = 0; i < PaintingGrid->GetChildrenCount(); ++i)
	{
		USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(i));
		if (!CardContainer) continue; //continue means skip this iteration of the loop and go to the next one

		CardContainer->ClearChildren();
	}
}

void UPaintingGrid::ClearPaginationDots()
{
	if (!PaginationDots) return;

	PaginationDots->ClearChildren();
}

void UPaintingGrid::AddPaginationDot(bool Active)
{
	if (!PaginationDots) return;
	auto Dot = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotClass);
	if (!Dot) return;

	Dot->SetActive(Active);

	UHorizontalBoxSlot* PaginationSlot = PaginationDots->AddChildToHorizontalBox(Dot);
	PaginationSlot->SetPadding(FMargin(PaginationDotPadding, 0));
}

int32 UPaintingGrid::GetNumberOfSlots() const
{
	return PaintingGrid->GetChildrenCount();
}
