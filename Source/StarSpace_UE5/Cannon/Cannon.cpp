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
	_cannonSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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

void ACannon::SetBulletRotation(FRotator rot)
{
	_bulletRotation = rot;
}

void ACannon::Shoot(TSubclassOf<ABullet> bullet, FString ownerTag)
{
	UWorld* world = GetWorld();
	FVector position = RootComponent->GetComponentLocation() + FVector(0, 100, 0);
	FRotator rotation = RootComponent->GetRelativeRotation();
	ABullet* instance = (ABullet*)world->SpawnActor(bullet);
	instance->SetLocation(position);
	instance->SetRotator(_bulletRotation);
	instance->SetOwnerTag(ownerTag);
	instance->StartPhysics();
}

