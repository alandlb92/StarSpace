// Fill out your copyright notice in the Description page of Project Settings.

#include "../StarSpace.h"
#include "IBulletReaction.h"

// Add default functionality here for any IIBulletReaction functions that are not pure virtual.
void IIBulletReaction::BulletReaction(AActor* BulletToReact)
{
	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> BASE"));
}