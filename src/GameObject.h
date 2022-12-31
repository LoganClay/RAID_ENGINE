#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Render.h"

using namespace sf;

class GameObject {
	public:
		string spriteFile;
		int * xPos;
		int * yPos;
		int * spriteH;
		int * spriteW;
		int unitsH;
		int unitsW;

		Hitbox* hitbox;

		Render* render;
		Render::Node *node;
		Sprite sprite;
		Texture texture;

		int nodeNum;

		void fillAnimation(int array[60][2], int pX, int pY, int start, int length);
		void createStillAnimation(int array[60][2], int pX, int pY);
		void SetAnimation(int n);
};

class Background : public GameObject {
	public:
		Background(Render * render);
};

class CloseButton : public GameObject {
	public:
		CloseButton(Render * render);
};

class ObjectList {
	public:
		class Node {
			public:
				GameObject * object;
				Node * next;
				Node(GameObject * object) {
					this->object = object;
					this->next = nullptr;
				}
				void setNext(Node * node) { this->next = node; }
		};

		int listSize;

		Node * first;
		Node * last;

		ObjectList() : listSize(0), first(nullptr), last(nullptr){}

		void removeObject(Node * node, Render * render);
		void truncateObjects(Node * node);
		void clearObjects();
		Node * addObject(GameObject * object);
		Node * getIndex(int i);
};

