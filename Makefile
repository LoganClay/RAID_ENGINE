engineFiles := Controls.cpp Game.cpp GameEngine.cpp GameObject.cpp Hitbox.cpp KeyboardIn.cpp KeyboardOut.cpp Render.cpp Sound.cpp
externFiles := glad.c

run: $(engineFiles)
	g++ $(engineFiles) $(externFiles) -o run -Wall -std=c++17 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -I./glad/include/
