// Fill out your copyright notice in the Description page of Project Settings.


#include "IdUtils.h"

int IdUtils::_nextId = 0;

IdUtils::IdUtils()
{
}

IdUtils::~IdUtils()
{
}

int IdUtils::GetNewId()
{
	int newId = _nextId;
	_nextId++;
	return newId;
}
