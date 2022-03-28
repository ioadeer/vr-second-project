// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "HandControllerBase.generated.h"

UCLASS()
class SECOND_PROJECT_API AHandControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandControllerBase();

public:
	//
	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); };
	virtual void TriggerPressed() {};
	virtual void TriggerReleased() {};

private:

	//Component
	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* MotionController;


};
