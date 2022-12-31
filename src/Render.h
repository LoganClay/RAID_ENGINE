#pragma once
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;
using namespace std;

class Render {
	public:	
		class Node;

		class Animation {
			public:
				const static int MAX_ANIMATIONS = 20;
				const static int FRAMES = 60;
				const static int COORDS = 2;

				int activeAnimations = 0;
				int currentFrame = 0;
				int currentAnimation = 0;
				int animationPatterns [20][60][2];
				void addAnimation(int n, int array[60][2]);
				void setAnimation(int n);
				void iterate(Render::Node * node);
		};

		class Node {
			public:
				Sprite sprite;
				Render::Node *next;
				int w;
				int h;
				int x;
				int y;
				Node(Sprite object, int x, int y, int w, int h);
				void setNext(Node *node);

				Render::Animation* animation;
				Render::Animation* getAnimation();
				void iterate();
		}; 

		Render();
		Render::Node * addToRender(Sprite object, int x, int y, int w, int h);
		void removeFromRender(Render::Node* node);
		void removeFromRender(int i);
		void truncateRender(Sprite object);
		void truncateRender(int i);
		void clearRender();
		Render::Node* getIndex(int i);
		Render::Node* getFirst();
		Render::Node* getLast();
		int getSize();

	private:
		int renderSize;
		Node *first;
		Node *last;
};
