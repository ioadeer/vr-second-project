// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/HorizontalBox.h"
#include "PaintingGridCard.h"
#include "PaginationDot.h"
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
	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* PaginationDots;


public:
	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex, FString PaintingName);
	void AddPaginationDot(bool Active);

	void ClearPaintings();
	void ClearPaginationDots();

	int32 GetNumberOfSlots() const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintingGridCard> GridCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaginationDot> PaginationDotClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationDotPadding = 8.f;
};
