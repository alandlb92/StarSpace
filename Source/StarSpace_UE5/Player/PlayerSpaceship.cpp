// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"
#include "Math/Vector.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Camera/CameraComponent.h"
#include "../Utils/LocationUtils.h"
#include "Components/BoxComponent.h"
#include "../UI/PlayerHUD.h"

const FString  APlayerSpaceship::OwnerTag = FString(TEXT("Player"));

void FSpaceShipInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}

void FSpaceShipInput::MoveX(float AxisValue)
{
	RawMovementInput.X = AxisValue;
}

void FSpaceShipInput::MoveY(float AxisValue)
{
	RawMovementInput.Y = AxisValue;
}

// Sets default values
APlayerSpaceship::APlayerSpaceship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpaceShipBase"));
	}

	_bodySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpaceShip"));
	_bodySprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_bodySprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));


	_speed = 10;
	_canShoot = true;
	_maxHeating = 10;

}


TArray<UBoxComponent*> APlayerSpaceship::FindAllBoxComponents(AActor* Actor)
{

	UE_LOG(LogTemp, Warning, TEXT("FindAllBoxComponents"));

	TArray<UBoxComponent*> BoxComponents;

	for (UActorComponent* Component : Actor->GetComponents())
	{
		UBoxComponent* BoxComponent = Cast<UBoxComponent>(Component);
		if (BoxComponent)
		{
			BoxComponents.Add(BoxComponent);
		}
	}

	TArray<AActor*> ChildrenActors;
	Actor->GetAttachedActors(ChildrenActors);
	for (AActor* Child : ChildrenActors)
	{
		TArray<UBoxComponent*> ChildBoxComponents = FindAllBoxComponents(Child);
		BoxComponents.Append(ChildBoxComponents);
	}

	return BoxComponents;
}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();
	_world = GetWorld();

	if (_colliders.IsEmpty()) {
		_colliders = FindAllBoxComponents(this);
	}

	if(_colliders.IsEmpty())
		UE_LOG(LogTemp, Error, TEXT("_colliders.IsEmpty()"));

	if (_world)
	{
		_playerController = _world->GetFirstPlayerController();
		_playerHUD = Cast<APlayerHUD>(_playerController->GetHUD());
		_currentHeating = 0;
		_playerHUD->UpdatePlayerHeat(_currentHeating, _maxHeating);

		_levelGameMode = _world->GetAuthGameMode<ALevelsGameMode>();
		if (_levelGameMode)
		{
			_levelGameMode->AddOnLoadCallBack(bind(&APlayerSpaceship::OnLoadLevel, this));
			_levelGameMode->VerifyLoadingState();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Level GameMode not found"));
		}
	}
}

void APlayerSpaceship::TakeDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("TakeDamage"));


	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// Verifica se o controlador do jogador está controlando o ator que deseja desativar
	if (PlayerController && PlayerController->GetPawn() == this)
	{
		// Desativa o controle do jogador no ator atual
		PlayerController->UnPossess();
	}

	_bodySprite->SetVisibility(false);

	for (auto c : _colliders)
		c->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	for (auto cannon : _cannons)
		cannon->Disable();
}

void APlayerSpaceship::OnLoadLevel()
{
	ConfigureActiveCannons();
	ConfigureActiveShields();
}

void  APlayerSpaceship::ConfigureActiveShields()
{
	if (!_shield) {
		TArray<UChildActorComponent*> cannonsChilds;
		GetComponents(cannonsChilds, true);
		for (UChildActorComponent* child : cannonsChilds) {
			_shield = Cast<AShield>(child->GetChildActor());
			if (_shield)
				break;
		}
	}

	if (_shield)
	{
		_shield->SetOwnerName(OwnerTag);
		_shield->SetShieldLife(1);
	}
}

void  APlayerSpaceship::ConfigureActiveCannons()
{
	TArray<UChildActorComponent*> cannonsChilds;
	GetComponents(cannonsChilds, true);

	FPlayerConfiguration* PlayerConfiguration = _levelGameMode->StarSpaceGameState()->PlayerConfig;

	for (UChildActorComponent* child : cannonsChilds)
	{
		ACannon* cannon = Cast<ACannon>(child->GetChildActor());
		if (!cannon)
		{
			continue;
		}

		AddToCannonListIfNecessary(cannon, child);
		cannon->Activate((child->ComponentHasTag("Angle_Cannon") && PlayerConfiguration->AngleCannon)
			|| (child->ComponentHasTag("Side_Cannon") && PlayerConfiguration->SideCannon)
			|| (child->ComponentHasTag("Foward_Cannon") && PlayerConfiguration->FowardCannon)
			|| child->ComponentHasTag("Main_Cannon"));

		for (auto tag : child->ComponentTags)
		{
			UE_LOG(LogTemp, Warning, TEXT("tag -> %s"), *tag.ToString());
		}
	}
}

void APlayerSpaceship::AddToCannonListIfNecessary(ACannon* cannon, UChildActorComponent* child)
{
	if (!_cannons.Contains(cannon))
	{
		cannon->SetBulletRotation(child->GetComponentRotation());
		_cannons.Add(cannon);
	}
}


// Called every frame
void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpaceShipInput.Sanitize();

	Move();

	if (_isShooting && _canShoot && !_isOverHeat)
	{
		Shoot();
	}
	else if (!_canShoot)
	{
		CountTimeBetweenShoots(DeltaTime);
	}
	else if (!_canCoolDown)
	{
		CountTimeToCoolDown(DeltaTime);
	}
	else if (_canCoolDown && _currentHeating > 0)
	{
		CoolDown();
	}
	else if (_isOverHeat)
	{
		_isOverHeat = false;
	}
}

void APlayerSpaceship::BulletReaction(AActor* BulletToReact)
{
	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> APlayerSpaceship"));

	if (!Cast<ABullet>(BulletToReact)->CompareTag(OwnerTag))
	{
		BulletToReact->Destroy();
		TakeDamage();
	}
}

void APlayerSpaceship::Move()
{
	FVector MovementDirection = FVector(SpaceShipInput.MovementInput.X, 0, SpaceShipInput.MovementInput.Y);
	if (!MovementDirection.IsNearlyZero())
	{
		FVector newPosition = GetActorLocation() + (MovementDirection * _speed);
		SetActorLocation(newPosition);
		ClampSpaceShipPosition();
	}
}

void APlayerSpaceship::ClampSpaceShipPosition()
{
	FVector maxPositions = LocationUtils::GetRightTopFirstPlayerScreenWorldposition(_world);
	FVector minPositions = LocationUtils::GetLeftBottonFirstPlayerScreenWorldposition(_world);
	FVector newPosition = GetActorLocation();

	double xAdjustments = _bodySprite->GetSprite()->GetRenderBounds().GetBox().GetSize().X / 2;
	double zAdjustments = _bodySprite->GetSprite()->GetRenderBounds().GetBox().GetSize().Y / 2;

	newPosition.X = FMath::Clamp<double>(newPosition.X, minPositions.X + xAdjustments, maxPositions.X - xAdjustments);
	newPosition.Z = FMath::Clamp<double>(newPosition.Z, minPositions.Z + zAdjustments, maxPositions.Z - zAdjustments);
	SetActorLocation(newPosition);
}

void APlayerSpaceship::StartShoot()
{
	_isShooting = true;
}

void APlayerSpaceship::StopShoot()
{
	_isShooting = false;
}


void APlayerSpaceship::Shoot()
{
	for (ACannon* cannon : _cannons)
	{
		if (cannon != nullptr)
			cannon->Shoot(_bulletRef, OwnerTag);
	}
	Heating();
	_canShoot = false;
}

void APlayerSpaceship::Heating()
{
	_currentHeating++;
	_isOverHeat = _currentHeating >= _maxHeating;
	_playerHUD->UpdatePlayerHeat(_currentHeating, _maxHeating);
}

void APlayerSpaceship::CoolDown()
{
	_canCoolDown = false;
	_currentHeating--;
	_playerHUD->UpdatePlayerHeat(_currentHeating, _maxHeating);
}

void APlayerSpaceship::CountTimeBetweenShoots(float DeltaTime)
{
	_counter += DeltaTime;
	if (_counter > TimeBetweenShoots)
	{
		_canShoot = true;
		_counter = 0;
	}
}

void APlayerSpaceship::CountTimeToCoolDown(float DeltaTime)
{
	_counter += DeltaTime;
	if (_counter > TimeBetweenShoots)
	{
		_canCoolDown = true;
		_counter = 0;
	}
}

void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveY", this, &APlayerSpaceship::MoveY);
	InputComponent->BindAxis("MoveX", this, &APlayerSpaceship::MoveX);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerSpaceship::StartShoot);
	InputComponent->BindAction("Shoot", IE_Released, this, &APlayerSpaceship::StopShoot);
}

void APlayerSpaceship::MoveY(float axisValue)
{
	SpaceShipInput.MoveY(axisValue);
}

void APlayerSpaceship::MoveX(float axisValue)
{
	SpaceShipInput.MoveX(axisValue);
}

