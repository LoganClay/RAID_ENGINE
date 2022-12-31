engineHFiles := src/Controls.h src/GameObject.h src/Hitbox.h src/KeyboardIn.h src/KeyboardOut.h src/Render.h src/Sound.h
engineCPPFiles := src/Controls.cpp src/Game.cpp src/GameEngine.cpp src/GameObject.cpp src/KeyboardIn.cpp src/KeyboardOut.cpp src/Render.cpp src/Sound.cpp
externFiles := src/glad.c

run.exe: $(engineCPPFiles) $(engineHFiles)
	g++ $(engineCPPFiles) $(externFiles) -o run.exe -Wall -std=c++20 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -I./include/

clean:
	rm -f run.exe
