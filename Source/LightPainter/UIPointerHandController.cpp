// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPointerHandController.h"
#include "InputCoreTypes.h"

AUIPointerHandController::AUIPointerHandController()
{
	Pointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Pointer"));
	Pointer->SetupAttachment(GetRootComponent());
}

void AUIPointerHandController::Draw()
{
	Pointer->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::DrawStop()
{
	Pointer->ReleasePointerKey(EKeys::LeftMouseButton);
}
