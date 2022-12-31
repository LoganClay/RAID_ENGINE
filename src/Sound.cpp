#include "Sound.h"
#include "Util.h"

using namespace sf;
using namespace std;

/**
 * SoundEffect constructor.
 * This loads in a sound effect.
 *
 * @param file -- String representing a file
 */
SoundEffect::SoundEffect(string file) : MySound(file) {
	// Error reading in sound effect
	if (!buffer.loadFromFile(file)) { cout << "Nopey\n"; }

	// Otherwise, success
	sound = Sound(buffer);
}

// Play a SoundEffect sound
void SoundEffect::play() {
	sound.play();
}

// Set the volume of the SoundEffect object
void SoundEffect::setVolume(float v) {
	sound.setVolume(v);
}

/**
 * Song constructor.
 * This loads in a song and a volume.
 *
 * @param file -- String representing a file
 */
Song::Song(string file) : MySound(file) {
	// Open song from filename in this->fileName
	if (!song.openFromFile(this->fileName)) { cout << "Nopey\n"; }

}

// Set the song to the file passed into the constructor
void Song::play() {
	song.play();
}

// Set the volume of the Song object
void Song::setVolume(float v) {
	song.setVolume(v);
}
