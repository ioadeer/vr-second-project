// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HandControllerBase.h"
#include "VRPawn.generated.h"

UCLASS()
class SECOND_PROJECT_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UCameraComponent* Camera;

	UPROPERTY()
	class USceneComponent* VRRoot;

	UPROPERTY()
	AHandControllerBase* RightController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> PaintBrushHandControllerClass;

	void RightTriggerPressed();
	void RightTriggerReleased();

	void Save();
	void Load();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
