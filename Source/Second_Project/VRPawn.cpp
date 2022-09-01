// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Saving/PainterSaveGame.h"
#include "PaintBrushHandController.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);


}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	if (Painting && Painting->Save())
	{
		CurrentSlotName = Painting->GetSlotName();
	}

	RightController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
	if (RightController != nullptr)
	{
		RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightController->SetHand(EControllerHand::Right);
		RightController->SetOwner(this);
	}
}


// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0.0f;
	AddActorWorldOffset(NewCameraOffset);
	VRRoot->AddWorldOffset(-NewCameraOffset);
	
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this,&AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);

	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AVRPawn::Save);
}

void AVRPawn::RightTriggerPressed()
{
	if (RightController)
	{
		RightController->TriggerPressed();
	}
}

void AVRPawn::RightTriggerReleased()
{
	if (RightController)
	{
		RightController->TriggerReleased();
	}
}

void AVRPawn::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
	if (Painting)
	{
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
		UE_LOG(LogTemp, Warning, TEXT("Game saved!"));
	}
}
