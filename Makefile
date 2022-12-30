engineFiles := Controls.cpp Game.cpp GameEngine.cpp GameObject.cpp Hitbox.cpp KeyboardIn.cpp KeyboardOut.cpp Render.cpp Sound.cpp

run: $(engineFiles)
	g++ $(engineFiles) -o run -Wall -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system
