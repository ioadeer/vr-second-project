// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("StrokeMeshes"));
	StrokeMeshes->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AStroke::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStroke::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStroke::Update(FVector CursorLocation)
{
	FTransform NewStrokeTransform;

	FVector LocalCursosLocation = GetTransform().InverseTransformPosition(CursorLocation);

	NewStrokeTransform.SetLocation(LocalCursosLocation);

	StrokeMeshes->AddInstance(NewStrokeTransform);

	PreviousCursorLocation = CursorLocation;
}

