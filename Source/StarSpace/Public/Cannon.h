// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "Cannon.generated.h"

UCLASS()
class STARSPACE_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* _cannonSprite;
	void Shoot(TSubclassOf<ABullet>, FString);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
