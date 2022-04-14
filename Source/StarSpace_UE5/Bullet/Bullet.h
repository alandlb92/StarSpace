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

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		virtual void  BulletReaction(AActor* BulletToReact) override;

private:
	UPROPERTY(EditAnywhere)
		int _speed;
	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* _bodySprite;

	FString OwnerTag;

};
