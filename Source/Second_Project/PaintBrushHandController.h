// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class SECOND_PROJECT_API APaintBrushHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintBrushHandController();
	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); };
	void TriggerPressed();
	void TriggerReleased();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Component
	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* MotionController;

	//State
	UPROPERTY()
	class AStroke* CurrentStroke;

	//Config
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStroke> AStrokeClass;

};
