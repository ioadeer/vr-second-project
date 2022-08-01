// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "PaintingGrid.generated.h"


/**
 * 
 */
UCLASS()
class SECOND_PROJECT_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;
public:
	UFUNCTION(BlueprintCallable)
	void AddPainting();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> GridCardClass;
};