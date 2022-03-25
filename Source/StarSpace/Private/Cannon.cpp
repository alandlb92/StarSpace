// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "PaperSpriteComponent.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon"));
	}

	_cannonSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CannonSprite"));
	_cannonSprite->AttachTo(RootComponent);
	_cannonSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACannon::Shoot()
{
	//UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), SpaceShipInput.MovementInput.X, SpaceShipInput.MovementInput.Y);
	UE_LOG(LogTemp, Warning, TEXT("PIU"));
}
