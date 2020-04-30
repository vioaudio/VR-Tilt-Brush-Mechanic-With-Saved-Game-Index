// Fill out your copyright notice in the Description page of Project Settings.


#include "PaginationDot.h"

void UPaginationDot::SetActive(bool Active)
{
	//Opacit 1 if true, 0.5 is false
	DotImage->SetOpacity(Active ? 1 : DisabledOpacity); //Ternary Operator, allows you to execute different code depending on the value of a condition
}
