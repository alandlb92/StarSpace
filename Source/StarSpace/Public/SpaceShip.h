// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cannon.h"
#include "Bullet.h"
#include "SpaceShip.generated.h"

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
class STARSPACE_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* _bodySprite;

private:
	static const FString OwnerTag;
	void MoveY(float axisValue);
	void MoveX(float axisValue);
	TArray<ACannon*> _cannons;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACannon> _cannonRef;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> _bulletRef;
	
	UPROPERTY(EditAnywhere)
	int _speed;

	APlayerController* _playerController;

	void Shoot();
	void ClampSpaceShipPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip")
	FSpaceShipInput SpaceShipInput;
};
