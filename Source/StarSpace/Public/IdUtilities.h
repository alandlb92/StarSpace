// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STARSPACE_API IdUtilities
{
public:
	IdUtilities();
	static int GetNewId();
private:
	static int _nextId;
};
