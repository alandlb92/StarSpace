// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Math/Vector.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "../Public/SpaceShip.h"


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
	_bodySprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_bodySprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));


	_speed = 10;
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	if (world)
	{
		AActor* instance = world->SpawnActor(_cannonRef);
		instance->AttachToComponent(_bodySprite, FAttachmentTransformRules::KeepRelativeTransform);
		instance->SetActorRelativeLocation(FVector(0, 0, 50));
		_cannons.Add((ACannon*)instance);

		_playerController = world->GetFirstPlayerController();
	}


	//ACannon* basicCannon = SpawnActor  //CreateDefaultSubobject<ACannon>(TEXT("BasicCannon"));
	//basicCannon->AttachToComponent(_bodySprite, FAttachmentTransformRules::KeepRelativeTransform);
	//_cannons.Add(basicCannon);

}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpaceShipInput.Sanitize();

	//UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), SpaceShipInput.MovementInput.X, SpaceShipInput.MovementInput.Y);
	FVector MovementDirection = FVector(SpaceShipInput.MovementInput.X, SpaceShipInput.MovementInput.Y, 0);
	if (!MovementDirection.IsNearlyZero())
	{
		FVector newPosition = GetActorLocation() + (MovementDirection * _speed);
		SetActorLocation(newPosition);
		ClampSpaceShipPosition();
	}
}

void ASpaceShip::ClampSpaceShipPosition()
{
}


void ASpaceShip::Shoot()
{
	for (ACannon* cannon : _cannons)
	{
		cannon->Shoot(_bulletRef);
	}
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveY", this, &ASpaceShip::MoveY);
	InputComponent->BindAxis("MoveX", this, &ASpaceShip::MoveX);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceShip::Shoot);
}

void ASpaceShip::MoveY(float axisValue)
{
	SpaceShipInput.MoveY(axisValue);
}

void ASpaceShip::MoveX(float axisValue)
{
	SpaceShipInput.MoveX(axisValue);
}