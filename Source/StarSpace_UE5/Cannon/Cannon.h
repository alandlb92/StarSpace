// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Bullet/Bullet.h"
#include "Cannon.generated.h"

UCLASS()
class STARSPACE_UE5_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* _cannonSprite;
	void Shoot(TSubclassOf<ABullet>, FString);
	void SetBulletRotation(FRotator);
	void Activate(bool enable);
	UPROPERTY(EditAnywhere)
	FRotator _bulletRotation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Disable();
	void Enable();

};
