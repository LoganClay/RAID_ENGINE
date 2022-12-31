#include <iostream>
#include "GameObject.h"

using namespace sf;

void GameObject::fillAnimation(int array[60][2], int pX, int pY, int start, int length) {
	for (int i = start; i < start + length; i++) {
		for (int x = 0; x < 2; x++) {
			array[i][x] = (x == 0) ? pX : pY;
		}

		cout << i << ": " << array[i][0] << ", " << array[i][1] << "\n";
	}
}

void GameObject::createStillAnimation(int array[60][2], int pX, int pY) {
	for (int i = 0; i < 60; i++) {
		array[i][0] = pX;
		array[i][1] = pY;
	}
}

void GameObject::SetAnimation(int n) {
	this->node->getAnimation()->setAnimation(n); 
}

ObjectList::Node * ObjectList::addObject(GameObject * object) {
	listSize++;

	if (listSize == 0) {
		first = (Node *)(new Node(object));
		last = first;
		return first;
	}
	else {
		Node * new_node = (Node *)(new Node(object));
		last->setNext(new_node);
		last = new_node;
		return last;
	}
}

Background::Background(Render * render) {
	(*spriteW) = 1920;
	(*spriteH) = 1080;
	(*xPos) = 0;
	(*yPos) = 0;

	unitsW = 1;
	unitsH = 1;

	texture.loadFromFile("../img/bg.jpg", IntRect(0, 0, 1920, 1080));
	Sprite sprite = Sprite(texture);

	node = render->addToRender(sprite, xPos, yPos, spriteW, spriteH);
	nodeNum = render->getSize();

	// Animations
	int animation[60][2];

	createStillAnimation(animation, 0, 0);

	node->animation->addAnimation(0, animation);

	this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteW, this->spriteH);
}

CloseButton::CloseButton(Render * render) {
	(*spriteW) = 500;
	(*spriteH) = 250;
	(*xPos) = 710;
	(*yPos) = 415;

	unitsW = 2;
	unitsH = 1;

	texture.loadFromFile("../img/close.png", IntRect(0, 0, 1920, 1080));
	Sprite sprite = Sprite(texture);

	node = render->addToRender(sprite, xPos, yPos, spriteW, spriteH);
	nodeNum = render->getSize();

	//Animations
	int animation[60][2];

	createStillAnimation(animation,0,0);
	node->animation->addAnimation(0, animation);

	createStillAnimation(animation, 1, 0);
	node->animation->addAnimation(1, animation);

	this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteH, this->spriteW);

}

// TODO previously used shared_ptrs for everything
// Fix to make work with regular pointers (specifically .reset())
void ObjectList::removeObject(Node * node, Render * render) {
	if (listSize == 0) return;
	Node * temp = first;
	Node * temp2 = last;
	Node * temp3;
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

void ObjectList::truncateObjects(Node * node) {
	Node * temp = first;
	Node * temp2 = last;
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
			temp2->setNext(nullptr);
			last = temp2;
		}
		cout << listSize << endl;
	}
}

void ObjectList::clearObjects() {
	Node * temp = first;
	Node * temp2 = last;
	for (int i = 0; i < listSize; i++) {
		temp2 = temp->next;
		temp->object->render->removeFromRender(temp->object->node);
		temp.reset();
		temp = temp2;
	}
	first = nullptr;
	last = nullptr;
	listSize = 0;
}

ObjectList::Node * ObjectList::getIndex(int i) {
	if (i > listSize || i < 0) return first;
	Node * node = first;
	for (int x = 0; x < i; x++) {
		node = node->next;
	}
	return node;
}
