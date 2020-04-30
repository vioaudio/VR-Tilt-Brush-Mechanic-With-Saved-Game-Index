// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "PaintingGridCard.h"
#include "Components/HorizontalBox.h"
#include "PaginationDot.h"
#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex, FString PaintingName);
	void ClearPaintings();
	void ClearPaginationDots();
	void AddPaginationDot(bool Active);
	int32 GetNumberOfSlots() const;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UUniformGridPanel* PaintingGrid;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UHorizontalBox* PaginationDots;

private: 
	UPROPERTY(EditDefaultsOnly) //to configure the class that is passed into create widget function called in add painting
		TSubclassOf<UPaintingGridCard> GridCardClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UPaginationDot> PaginationDotClass;
	UPROPERTY(EditDefaultsOnly)
		float PaginationDotPadding = 8;
};
