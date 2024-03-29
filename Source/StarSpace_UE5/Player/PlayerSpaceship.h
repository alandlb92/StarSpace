// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Cannon/Cannon.h"
#include "../Bullet/Bullet.h"
#include "../Data/PlayerConfiguration.h"
#include "../Bullet/BulletReaction.h"
#include "..\Shield.h"
#include "../LevelsGameMode.h"
#include "PlayerSpaceship.generated.h"

USTRUCT(BlueprintType)
struct FSpaceShipInput
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip Input")
		FVector2D MovementInput;

	void Sanitize();
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

private:
	FVector2D RawMovementInput;
};


UCLASS()
class STARSPACE_UE5_API APlayerSpaceship : public APawn, public IBulletReaction
{
	GENERATED_BODY()

public:
	APlayerSpaceship();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPaperSpriteComponent* _bodySprite;
	UFUNCTION()
		virtual void  BulletReaction(AActor* BulletToReact) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip")
		FSpaceShipInput SpaceShipInput;

private:
	TArray<class UBoxComponent*> FindAllBoxComponents(AActor* Actor);

	void TakeDamage();

	void OnLoadLevel();
	static const FString OwnerTag;
	const float TimeBetweenShoots = .2f;

	void MoveY(float axisValue);
	void MoveX(float axisValue);

	float _counter;
	UPROPERTY()
		UWorld* _world;

	UPROPERTY()
		AShield* _shield;

	UPROPERTY()
		TArray<ACannon*> _cannons;
	UPROPERTY()
		TArray<ACannon*> _shields;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ACannon> _cannonRef;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> _bulletRef;

	UPROPERTY(EditAnywhere)
		int _speed;

	UPROPERTY(EditAnywhere)
		int _cannonsLevel = 1;

	UPROPERTY(EditAnywhere)
		int _currentHeating;
	UPROPERTY(EditAnywhere)
		int _maxHeating;
	bool _isShooting;
	bool _isOverHeat;
	bool _canShoot;
	bool _canCoolDown;

	UPROPERTY()
		ALevelsGameMode* _levelGameMode;
	UPROPERTY()
		APlayerController* _playerController;
	UPROPERTY()
		class APlayerHUD* _playerHUD;

	void ConfigureActiveCannons();
	void ConfigureActiveShields();

	void Move();
	void ClampSpaceShipPosition();
	void StartShoot();
	void StopShoot();
	void Shoot();
	void CountTimeBetweenShoots(float);
	void CountTimeToCoolDown(float);
	void Heating();
	void CoolDown();
	void AddToCannonListIfNecessary(ACannon* cannon, UChildActorComponent* child);

	UPROPERTY()
	TArray<class UBoxComponent*> _colliders;
};
