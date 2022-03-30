// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class STARSPACE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetOwnerTag(FString);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		int _speed;
	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* _bodySprite;

	FString OwnerTag;

};