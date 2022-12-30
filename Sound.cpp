#include "Sound.h"

SoundEffect::SoundEffect(String file) {
	if (!buffer.loadFromFile(file)) {
		cout << "Nopey" << endl;
	}
	sound = Sound(buffer);
}

void SoundEffect::play() {
	sound.play();
}

Song::Song(String file, float volume) {
	this->volume = volume;
	setSong(file);
}

void Song::setSong(String file) {
	if (!currentSong.openFromFile(file)) {
		cout << "Nopey" << endl;
	}

	currentSong.play();
	currentSong.setVolume(volume);
}

void Song::setVolume(float volume) {
	currentSong.setVolume(volume);
}