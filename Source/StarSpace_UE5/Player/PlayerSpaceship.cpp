// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"
#include "Math/Vector.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "../UI/PlayerHUD.h"

const FString  APlayerSpaceship::OwnerTag = FString(TEXT("Player"));

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
APlayerSpaceship::APlayerSpaceship()
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
	_canShoot = true;
	_maxHeating = 10;

}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
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
		_playerHUD = Cast<APlayerHUD>(_playerController->GetHUD());
		_currentHeating = 0;
		_playerHUD->UpdatePlayerHeat(_currentHeating, _maxHeating);
	}
	
}

// Called every frame
void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpaceShipInput.Sanitize();

	FVector MovementDirection = FVector(SpaceShipInput.MovementInput.X, SpaceShipInput.MovementInput.Y, 0);
	if (!MovementDirection.IsNearlyZero())
	{
		FVector newPosition = GetActorLocation() + (MovementDirection * _speed);
		SetActorLocation(newPosition);
		ClampSpaceShipPosition();
	}

	if (_isShooting && _canShoot && !_isOverHeat)
	{
		Shoot();
	}
	else if (!_canShoot)
	{
		CountTimeBetweenShoots(DeltaTime);
	}
	else if (!_canCoolDown)
	{
		CountTimeToCoolDown(DeltaTime);
	}
	else if (_canCoolDown && _currentHeating > 0)
	{
		CoolDown();
	}
	else if (_isOverHeat)
	{
		_isOverHeat = false;
	}
}


void APlayerSpaceship::CountTimeBetweenShoots(float DeltaTime)
{
	_counter += DeltaTime;
	if (_counter > TimeBetweenShoots)
	{
		_canShoot = true;
		_counter = 0;
	}
}

void APlayerSpaceship::CountTimeToCoolDown(float DeltaTime)
{
	_counter += DeltaTime;
	if (_counter > TimeBetweenShoots)
	{
		_canCoolDown = true;
		_counter = 0;
	}
}

void APlayerSpaceship::ClampSpaceShipPosition()
{
}

void APlayerSpaceship::StartShoot()
{
	_isShooting = true;
}

void APlayerSpaceship::StopShoot()
{
	_isShooting = false;
}

void APlayerSpaceship::Shoot()
{
	for (ACannon* cannon : _cannons)
	{
		cannon->Shoot(_bulletRef, OwnerTag);
		Heating();
	}
	_canShoot = false;
}

void APlayerSpaceship::Heating()
{
	_currentHeating++;
	_isOverHeat = _currentHeating >= _maxHeating;
	_playerHUD->UpdatePlayerHeat(_currentHeating, _maxHeating);
}

void APlayerSpaceship::CoolDown()
{
	_canCoolDown = false;
	_currentHeating--;
	_playerHUD->UpdatePlayerHeat(_currentHeating, _maxHeating);
}



// Called to bind functionality to input
void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveY", this, &APlayerSpaceship::MoveY);
	InputComponent->BindAxis("MoveX", this, &APlayerSpaceship::MoveX);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerSpaceship::StartShoot);
	InputComponent->BindAction("Shoot", IE_Released, this, &APlayerSpaceship::StopShoot);
}

void APlayerSpaceship::MoveY(float axisValue)
{
	SpaceShipInput.MoveY(axisValue);
}

void APlayerSpaceship::MoveX(float axisValue)
{
	SpaceShipInput.MoveX(axisValue);
}

