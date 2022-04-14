// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Cannon/Cannon.h"
#include "../Bullet/Bullet.h"
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
class STARSPACE_UE5_API APlayerSpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerSpaceship();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPaperSpriteComponent* _bodySprite;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip")
	FSpaceShipInput SpaceShipInput;

private:
	static const FString OwnerTag;
	const float TimeBetweenShoots = .2f;
	float _counter;

	void MoveY(float axisValue);
	void MoveX(float axisValue);
	TArray<ACannon*> _cannons;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACannon> _cannonRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> _bulletRef;

	UPROPERTY(EditAnywhere)
	int _speed;

	UPROPERTY(EditAnywhere)
	int _currentHeating;
	UPROPERTY(EditAnywhere)
	int _maxHeating;
	bool _isShooting;
	bool _canShoot;

	APlayerController* _playerController;
	class APlayerHUD* _playerHUD;

	void ClampSpaceShipPosition();
	void StartShoot();
	void StopShoot();
	void Shoot();
	void CountTimeBetweenShoots(float);
	void Heating();

};
