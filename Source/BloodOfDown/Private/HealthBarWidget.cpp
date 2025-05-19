// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"


void UHealthBarWidget::NativeConstruct()
{
}

void UHealthBarWidget::SetBarValuePercent(float const value)
{
	HealthValue->SetPercent(value);
}
