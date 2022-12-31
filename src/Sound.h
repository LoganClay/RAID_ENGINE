#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace sf;
using std::string;

// Note that there is an actual distinction between SoundBuffers and
// Music in SFML. SoundBuffers are loaded all at once into memory, and
// are thus better for short sounds. Music is loaded in as-needed.
// For the ability to change the volume of sound effects, I've
// created a parent function that handles this functionality.
class MySound {
	public:
		string fileName;

		MySound(string file) : fileName(file) {};
		virtual void play() = 0;
		virtual void setVolume(float v) = 0;
};

/**
 * SoundEffect Class.
 * Represents a sound effect in code.
 */
class SoundEffect : public MySound {
	public:
		SoundBuffer buffer;
		Sound sound;

		SoundEffect(string file);
		void play();
		void setVolume(float v);
};

/**
 * Song Class.
 * Represents a Song in code.
 */
class Song : public MySound {
	public:
		Music song;

		Song(string file);
		void play();
		void setVolume(float v);
};
