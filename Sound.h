#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class SoundEffect{
public:
	SoundBuffer buffer;
	Sound sound;

	SoundEffect(String file);

	void play();

};
 
class Song{
public:
	Music currentSong;
	float volume;
	
	Song(String file, float volume);

	void setSong(String file);
	void setVolume(float volume);

};
