// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "PaperSpriteComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyBase"));
	}
	_enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EnemySprite"));
	_enemySprite->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AEnemyBase::BulletReaction(AActor* BulletToReact)
{
	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> AEnemyBase"));
}

