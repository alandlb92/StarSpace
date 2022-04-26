
#pragma once

#include "CoreMinimal.h"

class STARSPACE_UE5_API UIAnimationBase
{
public:
	virtual void Initialize();
	virtual void Tick(float DeltaTime);
};
