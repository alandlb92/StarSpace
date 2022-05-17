// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootBehaviour.h"

// Sets default values for this component's properties
UShootBehaviour::UShootBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootBehaviour::BeginPlay()
{
	Super::BeginPlay();
	_enemy = Cast<AEnemy>(GetOwner());
}


// Called every frame
void UShootBehaviour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_enemy != nullptr)
	{
		_countTimeBetwenSequence += DeltaTime;
		if (_countTimeBetwenSequence > _timeBetwenSequence)
		{
			_countTimeBetwenShoots += DeltaTime;
			if (_countTimeBetwenShoots > _timeBetwenShoots)
			{
				_enemy->Shoot();
				_countShoots++;
				_countTimeBetwenShoots = 0;
				if (_countShoots >= _howMuchShoots)
				{
					_countShoots = 0;
					_countTimeBetwenShoots = 0;
					_countTimeBetwenSequence = 0;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT FOUND ENEMY"));
	}
}

