#pragma once
struct  GameConfiguration
{
public:
	bool MusicOn;
	bool SoundFXOn;

	GameConfiguration()
	{
		MusicOn = true;
		SoundFXOn = true;
	}


	GameConfiguration(GameConfiguration* gameConfiguration)
	{
		MusicOn = gameConfiguration->MusicOn;
		SoundFXOn = gameConfiguration->SoundFXOn;
	}
};