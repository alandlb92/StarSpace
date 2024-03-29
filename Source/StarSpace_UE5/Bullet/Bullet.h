// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletReaction.h"
#include "Bullet.generated.h"

UCLASS()
class STARSPACE_UE5_API ABullet : public AActor, public IBulletReaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetOwnerTag(FString);
	bool CompareTag(FString);
	void SetLocation(FVector);
	void SetRotator(FRotator);
	void StartPhysics();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void  BulletReaction(AActor* BulletToReact) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* _bodySprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* _sphereCollision;


private:
	UPROPERTY(EditAnywhere)
	int _speed;

	FString OwnerTag;
	
	UPROPERTY()
	class UProjectileMovementComponent* _movementComponent;

};
