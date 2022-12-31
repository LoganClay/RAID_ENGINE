engineHFiles := src/Controls.h src/GameObject.h src/Hitbox.h src/KeyboardIn.h src/KeyboardOut.h src/Render.h src/Sound.h
engineCPPFiles := src/Controls.cpp src/Game.cpp src/GameEngine.cpp src/GameObject.cpp src/Hitbox.cpp src/KeyboardIn.cpp src/KeyboardOut.cpp src/Render.cpp src/Sound.cpp
externFiles := src/glad.c

run: $(engineCPPFiles) $(engineHFiles)
	g++ $(engineCPPFiles) $(externFiles) -o run -Wall -std=c++17 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -I./include/
