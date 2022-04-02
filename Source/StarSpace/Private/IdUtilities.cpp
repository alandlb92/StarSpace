// Fill out your copyright notice in the Description page of Project Settings.


#include "IdUtilities.h"

int IdUtilities::_nextId = 0;

IdUtilities::IdUtilities()
{
}

int IdUtilities::GetNewId()
{
	int newId = _nextId;
	_nextId++;
	return newId;
}
