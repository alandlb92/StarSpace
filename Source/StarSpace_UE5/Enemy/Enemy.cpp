// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PaperSpriteComponent.h"
#include "../Utils/IdUtils.h"
#include "Components/ChildActorComponent.h"

const FString  AEnemy::OwnerTag = FString(TEXT("Enemy"));

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

	TArray<UChildActorComponent*> cannonsChilds;
	GetComponents(cannonsChilds, true);
	UWorld* world = GetWorld();

	for (UChildActorComponent* child : cannonsChilds)
	{		
		ACannon* cannon = (ACannon*)child->GetChildActor();
		cannon->SetBulletRotation(child->GetComponentRotation());
		_cannons.Add(cannon);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::Shoot()
{
	for (ACannon* cannon : _cannons)
	{
		if (_bulletRef != nullptr)
			cannon->Shoot(_bulletRef, OwnerTag);
	}
}

void AEnemy::BulletReaction(AActor* BulletToReact)
{
	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> AEnemyBase"));

	if (!Cast<ABullet>(BulletToReact)->CompareTag(OwnerTag))
	{
		BulletToReact->Destroy();
		for (ACannon* cannon : _cannons)
		{
			cannon->Destroy();
		}
		Destroy();
	}
}