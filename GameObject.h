#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hitbox.h"
#include "Render.h"

using namespace sf;


class GameObject {
	public:
		string spriteFile;
		//coordinates of object
		shared_ptr<int> xPos, yPos;
		//Pixel dimensions of the individual sprites
		shared_ptr<int> spriteH, spriteW;
		//Amount of sprites in the dimensions of the sheet
		int unitsH, unitsW;

		Hitbox* hitbox;
		
		Render* render;
		Render::Node *node;
		Sprite sprite;
		Texture texture;
		
		int nodeNum;
		
		void fillAnimation(int array[60][2], int pX, int pY, int start, int length) {
			for (int i = start; i < start + length; i++) {
				for (int x = 0; x < 2; x++) {
					switch (x){
						case 0:
							array[i][x] = pX;
							break;
						case 1:
							array[i][x] = pY;
							break;
					}	
				}
				cout << i << ": " << array[i][0] << ", " << array[i][1] << endl;
			}
		}
		void createStillAnimation(int array[60][2], int pX, int pY) {
			for (int i = 0; i < 60; i++) {
				array[i][0] = pX;
				array[i][1] = pY;
			}
		}
		void SetAnimation(int n) { this->node->getAnimation()->setAnimation(n); }
};
class ObjectList {
public:
	class Node{
	public:
		shared_ptr<GameObject> object;
		shared_ptr<Node> next;
		Node(shared_ptr<GameObject> object) {
			this->object = object;
			this->next = NULL;
		}
		void setNext(shared_ptr<Node> node) { this->next = node; }
	};
	int listSize;

	shared_ptr<Node> first;
	shared_ptr<Node> last;

	ObjectList() {
		listSize = 0;
		first = NULL;
		last = NULL;
	}

	shared_ptr<Node> addObject(shared_ptr<GameObject> object) {
		if (listSize == 0) {
			first = shared_ptr<Node>(new Node(object));
			last = first;
			listSize++;
			return first;
		}
		else {
			shared_ptr<Node> new_node = shared_ptr<Node>(new Node(object));
			last->setNext(new_node);
			last = new_node;
			listSize++;
			return last;
		}
	}

	void removeObject(shared_ptr<Node> node, shared_ptr<Render> render) {
		if (listSize == 0) return;
		shared_ptr<Node> temp = first;
		shared_ptr<Node> temp2 = last;
		shared_ptr<Node> temp3;
		for (int i = 0; i < listSize; i++) {
			if (temp == node && i == 0) {
				temp2 = temp->next;
				render->removeFromRender(node->object->node);
				temp.reset();
				first = temp2;
				break;
			}
			else if (temp == node && node == last) {
				last = temp2;
				render->removeFromRender(node->object->node);
				temp.reset();
				break;
			}
			else if (temp == node) {
				temp3 = temp->next;
				temp2->setNext(temp3);
				render->removeFromRender(node->object->node);
				temp.reset();
				break;
			}
			temp2 = temp;
			temp = temp->next;
		}
		listSize--;
	}
	void truncateObjects(shared_ptr<Node> node) {
		shared_ptr<Node> temp = first;
		shared_ptr<Node> temp2 = last;
		int sizeTemp = listSize;
		bool trunc = false;
		for (int i = 0; i < sizeTemp; i++) {
			if (trunc) {
				temp2 = temp->next;
				temp->object->render->removeFromRender(temp->object->node);
				temp.reset();
				temp = temp2;
				listSize--;
			}
			else {
				temp2 = temp;
				temp = temp->next;
			}
			if (trunc == false && temp == node) {
				trunc = true;
				temp2->setNext(NULL);
				last = temp2;
			}
			cout << listSize << endl;
		}

	}
	void clearObjects() {
		shared_ptr<Node> temp = first;
		shared_ptr<Node> temp2 = last;
		for (int i = 0; i < listSize; i++) {
			temp2 = temp->next;
			temp->object->render->removeFromRender(temp->object->node);
			temp.reset();
			temp = temp2;
		}
		first = NULL;
		last = NULL;
		listSize = 0;
	}
	shared_ptr<Node> getIndex(int i) {
		if (i > listSize || i < 0)return first;
		shared_ptr<Node> node = first;
		for (int x = 0; x < i; x++) {
			node = node->next;
		}
		return node;
	}
};
