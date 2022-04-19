// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PaperSpriteComponent.h"
#include "../Utilitils/IdUtils.h"
#include "Components/ChildActorComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyBase"));
	}
	_enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EnemySprite"));
	_enemySprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_enemySprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	_health = 1;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	_tag = TEXT("Enemy");
	_id = IdUtils::GetNewId();
	TArray<UChildActorComponent*> cannonsLocations;
	GetComponents(cannonsLocations, true);

	UWorld* world = GetWorld();
	for (auto location : cannonsLocations)
	{
		AActor* instance = world->SpawnActor(_cannonRef);
		instance->AttachToComponent(_enemySprite, FAttachmentTransformRules::KeepRelativeTransform);
		FVector position = location->GetRelativeLocation();
		position.Y = 5;
		instance->SetActorRelativeLocation(position);

		instance->SetActorRelativeScale3D(FVector(1 / _enemySprite->GetRelativeScale3D().X));
		_cannons.Add((ACannon*)instance);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::BulletReaction(AActor* BulletToReact)
{
	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> AEnemyBase"));
	BulletToReact->Destroy();
	Destroy();
}