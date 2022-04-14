// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "PaperSpriteComponent.h"
#include "../Utilitils/LocationUtils.h"

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

	_bodySprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_bodySprite->SetNotifyRigidBodyCollision(true);
	_bodySprite->SetCollisionProfileName(TEXT("Trigger"));

	RootComponent = _bodySprite;

	_speed = 1000;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	FVector velocity = FVector(0, _speed, 0);
	_bodySprite->SetAllPhysicsLinearVelocity(velocity);
	_bodySprite->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	_bodySprite->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!LocationUtils::IsAppearingOnTheFirstPlayersScreen(RootComponent->GetRelativeLocation(), GetWorld()))
		Destroy();
}


// Called every frame
void ABullet::SetOwnerTag(FString tag)
{
	OwnerTag = tag;
}

void ABullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
	IBulletReaction* iBulletReaction = Cast<IBulletReaction>(OtherActor);
	if (iBulletReaction)
	{
		iBulletReaction->BulletReaction(this);
	}
}

void ABullet::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"));
}

void ABullet::BulletReaction(AActor* BulletToReact)
{
	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> Bullet"));
}