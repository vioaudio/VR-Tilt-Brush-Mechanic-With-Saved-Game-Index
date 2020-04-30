// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGridCard.h"
#include "Kismet/GameplayStatics.h"


void UPaintingGridCard::SetPaintingName(FString NewPaintingName)
{
	PaintingName = NewPaintingName;
	SlotName->SetText(FText::FromString(PaintingName));

	//Set up binding here because you want to know what the name of the painting is before you bind it
	Button->OnClicked.AddDynamic(this, &UPaintingGridCard::ButtonClicked); //Dynamic Delegate so need to create UFUNCTION for it to call 
}

void UPaintingGridCard::ButtonClicked()
{
	//Unreal bug that makes it take a long time to open leve, need to call ShowSplashScreem before you call Open Level, then HideSplashScreen after load
	UStereoLayerFunctionLibrary::ShowSplashScreen();

	//Opens level, 4th Parameter is what you want to pass on into the next level, great way of passing state
	//TODO: refactor out the slotname string used in this function so it can be used elsewhere
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Canvas"), true, "SlotName=" + PaintingName); 
}
