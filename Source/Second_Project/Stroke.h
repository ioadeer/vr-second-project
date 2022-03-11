// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.generated.h"

UCLASS()
class SECOND_PROJECT_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStroke();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Update(FVector CursorLocation);

private:
	class USplineMeshComponent* CreateSplineMesh();

	//Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	//Config
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* SplineMesh;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* SplineMaterial;

	//State
	FVector PreviousCursorLocation;
};
