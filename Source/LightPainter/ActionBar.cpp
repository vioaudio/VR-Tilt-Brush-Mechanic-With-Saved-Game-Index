// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBar.h"

bool UActionBar::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!Add) return false; //if the add button did not properly bind can also return false
	Add->OnClicked.AddDynamic(this, &UActionBar::AddButtonClicked);

	if (!Delete) return false; //if the delete button did not properly bind can also return false
	Delete->OnClicked.AddDynamic(this, &UActionBar::DeleteButtonClicked);

	return true;
}

void UActionBar::AddButtonClicked()
{
	if (ParentPicker) ParentPicker->AddPainting();
}

void UActionBar::DeleteButtonClicked()
{
	if (ParentPicker) ParentPicker->ToggleDeleteMode();
}
