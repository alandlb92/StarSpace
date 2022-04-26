// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STARSPACE_UE5_API IdUtils
{
public:
	IdUtils();
	~IdUtils();
	static int GetNewId();
private:
	static int _nextId;
};
