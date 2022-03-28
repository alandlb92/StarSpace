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

void ACannon::Shoot(TSubclassOf<ABullet> bullet)
{
	//UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), SpaceShipInput.MovementInput.X, SpaceShipInput.MovementInput.Y);
	UWorld* world = GetWorld();
	UE_LOG(LogTemp, Warning, TEXT("PIU"));
	FVector postion = RootComponent->GetComponentLocation() + FVector(0,100,0);
	AActor* instance = world->SpawnActor(bullet, &postion);
}
