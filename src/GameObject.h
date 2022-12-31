#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Render.h"

using namespace sf;

class GameObject {
	public:
		string spriteFile;
		shared_ptr<int> xPos, yPos; // Coordinates of object
		shared_ptr<int> spriteH, spriteW; // Pixel dimensions of the sprites
		int unitsH, unitsW; // Amount of sprites in the dimensions of the sheet

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
		Background(shared_ptr<Render> render);
};

class CloseButton : public GameObject {
	public:
		CloseButton(shared_ptr<Render> render);
};

class ObjectList {
	public:
		class Node {
			public:
				shared_ptr<GameObject> object;
				shared_ptr<Node> next;
				Node(shared_ptr<GameObject> object) {
					this->object = object;
					this->next = nullptr;
				}
				void setNext(shared_ptr<Node> node) { this->next = node; }
		};

		int listSize;

		shared_ptr<Node> first;
		shared_ptr<Node> last;

		ObjectList() : listSize(0), first(nullptr), last(nullptr){}

		void removeObject(shared_ptr<Node> node, shared_ptr<Render> render);
		void truncateObjects(shared_ptr<Node> node);
		void clearObjects();
		shared_ptr<Node> addObject(shared_ptr<GameObject> object);
		shared_ptr<Node> getIndex(int i);
};

