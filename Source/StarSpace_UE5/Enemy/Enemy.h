// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Bullet/BulletReaction.h"
#include "Enemy.generated.h"


UCLASS()
class STARSPACE_UE5_API AEnemy : public AActor, public IBulletReaction
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

	UFUNCTION()
	virtual void  BulletReaction(AActor* BulletToReact) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* _enemySprite;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int _health;
	FString _tag;
	int _id;

};
