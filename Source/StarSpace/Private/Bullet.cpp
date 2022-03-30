// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/PrimitiveComponent.h"
#include "PaperSpriteComponent.h"
#include "LocationUltilities.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	_bodySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Bullet"));
	_bodySprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_bodySprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	_bodySprite->SetSimulatePhysics(true);
	_bodySprite->SetEnableGravity(false);
	_bodySprite->BodyInstance.bLockRotation = true;
	_bodySprite->BodyInstance.SetDOFLock(EDOFMode::SixDOF);

	RootComponent = _bodySprite;

	_speed = 1000;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	FVector velocity = FVector(0, _speed, 0);
	_bodySprite->SetAllPhysicsLinearVelocity(velocity);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!LocationUltilities::IsAppearingOnTheFirstPlayersScreen(RootComponent->GetRelativeLocation(), GetWorld()))
		Destroy();
}


// Called every frame
void ABullet::SetOwnerTag(FString tag)
{
	OwnerTag = tag;
}