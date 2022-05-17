// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "PaperSpriteComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Utils/LocationUtils.h"

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
	_bodySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	_bodySprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	_bodySprite->SetSimulatePhysics(true);
	_bodySprite->SetEnableGravity(false);
	_bodySprite->BodyInstance.bLockRotation = true;
	_bodySprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_bodySprite->SetNotifyRigidBodyCollision(true);
	_bodySprite->SetCollisionProfileName(TEXT("Trigger"));
	_speed = 1000;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::StartPhysics()
{
	FVector velocity = UKismetMathLibrary::GetForwardVector(_bodySprite->GetComponentRotation() + FRotator(90, 0, 0)) * _speed;
	velocity *= _bodySprite->GetComponentRotation().Yaw >= 180 ? -1 : 1;

	_bodySprite->SetAllPhysicsLinearVelocity(velocity);
	_bodySprite->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	_bodySprite->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);
}

void ABullet::SetLocation(FVector pos)
{
	_bodySprite->SetWorldLocation(pos);
}


void ABullet::SetRotator(FRotator rot)
{
	_bodySprite->SetWorldRotation(rot);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!LocationUtils::IsAppearingOnTheFirstPlayersScreen(_bodySprite->GetComponentLocation(), GetWorld()))
		Destroy();
}


// Called every frame
void ABullet::SetOwnerTag(FString tag)
{
	OwnerTag = tag;
}


bool ABullet::CompareTag(FString tag)
{
	return tag == OwnerTag;
}

void ABullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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