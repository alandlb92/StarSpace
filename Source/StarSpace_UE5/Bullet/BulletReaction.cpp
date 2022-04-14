// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletReaction.h"

// Add default functionality here for any IBulletReaction functions that are not pure virtual.
void IBulletReaction::BulletReaction(AActor* BulletToReact)
{
	UE_LOG(LogTemp, Warning, TEXT("BulletReaction -> BASE"));
}