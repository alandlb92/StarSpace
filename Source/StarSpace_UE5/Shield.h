// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet/BulletReaction.h"
#include "Shield.generated.h"

UCLASS()
class STARSPACE_UE5_API AShield : public AActor, public IBulletReaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* _shieldSprite;

	UFUNCTION()
	virtual void  BulletReaction(AActor* BulletToReact) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FString OwnerTag;
	int shieldLife;

	bool isEnable;

public:
	UFUNCTION()
	void Enable();

	UFUNCTION()
	void Disable();

	void SetOwnerName(FString owner);

	UFUNCTION()
	void TakeDamage();
	
	UFUNCTION()
	void SetShieldLife(int life);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
