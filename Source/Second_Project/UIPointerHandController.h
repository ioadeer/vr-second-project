// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"
#include "UIPointerHandController.generated.h"

/**
 * 
 */
UCLASS()
class SECOND_PROJECT_API AUIPointerHandController : public AHandControllerBase
{
	GENERATED_BODY()

public:
	AUIPointerHandController();

	void TriggerReleased() override;
	void TriggerPressed() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UWidgetInteractionComponent* Pointer;
};
