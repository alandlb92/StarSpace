// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletBase"));
	}

	_bodySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Bullet"));
	_bodySprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_bodySprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));


	_speed = 10;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

