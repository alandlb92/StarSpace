// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Enemy.h"
#include "Components/ActorComponent.h"
#include "ShootBehaviour.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSPACE_UE5_API UShootBehaviour : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootBehaviour();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AEnemy* _enemy;
	UPROPERTY(EditAnywhere)
	int _howMuchShoots;
	UPROPERTY(EditAnywhere)
	float _timeBetwenShoots;
	UPROPERTY(EditAnywhere)
	float _timeBetwenSequence;


	int _countShoots;
	float _countTimeBetwenShoots;
	float _countTimeBetwenSequence;
		
};
