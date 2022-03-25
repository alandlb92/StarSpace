// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Math/Vector.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "..\Public\SpaceShip.h"


void FSpaceShipInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}

void FSpaceShipInput::MoveX(float AxisValue)
{
	RawMovementInput.X = AxisValue;
}

void FSpaceShipInput::MoveY(float AxisValue)
{
	RawMovementInput.Y = AxisValue;
}
// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpaceShipBase"));
	}

	_bodySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpaceShip"));
	_bodySprite->AttachTo(RootComponent);
	_bodySprite->SetWorldRotation(FRotator(0.0f, 90.0f, -90.0f));

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->AttachTo(RootComponent);
	_camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	_camera->AspectRatio = 1024.0f;
	_camera->OrthoWidth = 1024;
	_camera->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpaceShipInput.Sanitize();
	UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), SpaceShipInput.MovementInput.X, SpaceShipInput.MovementInput.Y);

}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveY", this, &ASpaceShip::MoveY);
	InputComponent->BindAxis("MoveX", this, &ASpaceShip::MoveX);
}

void ASpaceShip::MoveY(float axisValue)
{
	SpaceShipInput.MoveY(axisValue);
}

void ASpaceShip::MoveX(float axisValue)
{
	SpaceShipInput.MoveX(axisValue);
}