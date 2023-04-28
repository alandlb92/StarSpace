// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Bullet/Bullet.h"

// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon"));
	}
	_shieldSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CannonSprite"));
	_shieldSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AShield::BulletReaction(AActor* BulletToReact)
{
	if (!isEnable)
		return;

	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> APlayerSpaceship"));

	if (!Cast<ABullet>(BulletToReact)->CompareTag(OwnerTag))
	{
		BulletToReact->Destroy();
		TakeDamage();
		/*for (ACannon* cannon : _cannons)
		{
			cannon->Destroy();
		}
		Destroy();*/
	}
}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
}

void AShield::Enable()
{
	isEnable = true;
	_shieldSprite->SetVisibility(true);
}

void AShield::Disable()
{
	isEnable = false;
	_shieldSprite->SetVisibility(false);
}

void AShield::SetOwnerName(FString owner)
{
	OwnerTag = owner;
}

void AShield::TakeDamage()
{
	shieldLife--;
	if (shieldLife == 0) {
		shieldLife = 0;
		Disable();
	}
}

void AShield::SetShieldLife(int life)
{
	shieldLife = life;
	Enable();
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

