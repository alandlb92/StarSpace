#pragma once
struct  PlayerConfiguration
{
public:
	bool FowardCannon;
	bool AngleCannon;
	bool SideCannon;
	int Speed;
	int MaxHeating;
	int BulletLevel;

	PlayerConfiguration()
	{
		FowardCannon = false;
		AngleCannon = false;
		SideCannon = false;
		Speed = 1;
		MaxHeating = 1;
		BulletLevel = 1;
	}

	PlayerConfiguration(PlayerConfiguration* playerConfiguration)
	{
		FowardCannon = playerConfiguration->FowardCannon;
		AngleCannon = playerConfiguration->AngleCannon;
		SideCannon = playerConfiguration->SideCannon;
		Speed = playerConfiguration->Speed;
		MaxHeating = playerConfiguration->MaxHeating;
		BulletLevel = playerConfiguration->BulletLevel;
	}
};