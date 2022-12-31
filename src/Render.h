#pragma once
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;
using namespace std;

class Render
{
public:	
	class Node;

	class Animation {
	public:
		const int MAX_ANIMATIONS = 20, FRAMES = 60, COORDS = 2;
		//
		int activeAnimations = 0;
		//
		int currentFrame = 0;
		//
		int currentAnimation = 0;
		//
		int animationPatterns [20][60][2];


		void addAnimation(int n, int array[60][2]);

		void setAnimation(int n);

		void iterate(Render::Node* node);
	};
	class Node {
		public:
			Sprite sprite;
			Render::Node *next;
			Node(Sprite object, shared_ptr<int> x, shared_ptr<int> y, shared_ptr<int> w, shared_ptr<int> h);
			void setNext(Node *node);
			shared_ptr<int> w, h;
			shared_ptr<int> x, y;
			
			Render::Animation* animation;
			Render::Animation* getAnimation();
			void iterate();
	}; 
	
	Render();
	Render::Node* addToRender(Sprite object, shared_ptr<int> x, shared_ptr<int> y, shared_ptr<int> w, shared_ptr<int> h);
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