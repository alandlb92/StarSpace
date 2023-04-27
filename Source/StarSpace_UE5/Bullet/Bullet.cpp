// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "PaperSpriteComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "../Utils/LocationUtils.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpaceShipBase"));
	}

	_bodySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Bullet"));
	_bodySprite->SetEnableGravity(false);
	_bodySprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_bodySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	_bodySprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	_speed = 500;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	UClass* MovementComponentClass = UProjectileMovementComponent::StaticClass();
	_movementComponent = Cast<UProjectileMovementComponent>(GetComponentByClass(MovementComponentClass));

	 UClass* SphereComponentClass = USphereComponent::StaticClass();
	_sphereCollision = Cast<USphereComponent>(GetComponentByClass(MovementComponentClass));
}

void ABullet::StartPhysics()
{
	FVector velocity = UKismetMathLibrary::GetForwardVector(GetActorRotation() + FRotator(90, 0, 0)) * _speed;

	if (_movementComponent)
	{
		_movementComponent->SetVelocityInLocalSpace(velocity);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("no _movementComponent"));
	}

	//_bodySprite->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	//_bodySprite->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);
}

void ABullet::SetLocation(FVector pos)
{
	SetActorRelativeLocation(pos);
}


void ABullet::SetRotator(FRotator rot)
{
	SetActorRelativeRotation(rot);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!LocationUtils::IsAppearingOnTheFirstPlayersScreen(GetActorLocation(), GetWorld()))
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

//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams(FComponentHitSignature, UPrimitiveComponent, OnComponentHit, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit);

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