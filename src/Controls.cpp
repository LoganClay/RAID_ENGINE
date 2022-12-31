#include <iostream>
#include <memory>
#include "Controls.h"
#include "KeyboardOut.h"
#include "GameObject.h"

Node::Node(Control * c) {
	this -> control = c;
	this -> next = nullptr;
}

void Node::setNext(Node * n) {
	this -> next = n; 
}

Node * Controls::addControl(Control * c) {
	if (controlsSize == 0) {
		first =(Node *)(new Node(c));
		last = first;
		controlsSize++;
		return first;
	}
	else {
		Node * new_node = (Node *)(new Node(c));
		last->setNext(new_node);
		last = new_node;
		controlsSize++;
		return last;
	}
}

// TODO make work with regular pointers; especially use_count
// See if we even need that. If we do, potentially re-implement
// shared_ptrs
void Controls::removeControl(Node * node) {
	if (controlsSize == 0) return;

	Node * temp = first;
	Node * temp2 = last;
	Node * temp3;

	for (int i = 0; i < controlsSize; i++) {
		if (temp == node && i == 0) {
			temp2 = temp->next;
			int n = temp.use_count();
			for (int x = 0; x < n; x++)
				temp.reset();
			first = temp2;
			break;
		}
		else if (temp == node && i == controlsSize) {
			int n = temp.use_count();
			for(int x=0;x<n;x++)
				temp.reset();
			last = temp2;
			break;
		}
		else if (temp == node) {
			temp3 = temp->next;
			temp2->setNext(temp3);
			int n = temp.use_count();
			for (int x = 0; x < n; x++)
				temp.reset();
			break;
		}
		temp2 = temp;
		temp = temp->next;
	}
	controlsSize--;
}

void Controls::truncateControls(Node * node) {
	Node * temp = first;
	Node * temp2 = last;
	int sizeTemp = controlsSize;
	bool trunc = false;
	for (int i = 0; i < sizeTemp; i++) {
		if (trunc) {
			temp2 = temp->next;
			int n = temp.use_count();
			for (int x = 0; x < n; x++)
				temp.reset();
			temp = temp2;
			controlsSize--;
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
	}
}

void Controls::clearControls() {
	Node * temp = first;
	Node * temp2 = last;
	for (int i = 0; i < controlsSize; i++) {
		temp2 = temp->next;
		int n = temp.use_count();
		for (int x = 0; x < n; x++)
			temp.reset();
		temp = temp2;
	}
	first = nullptr;
	last = nullptr;
	controlsSize = 0;
}

Node * Controls::getIndex(int i) {
	if (i > controlsSize || i < 0) return first;

	Node * node = first;

	for (int x = 0; x < i; x++) {
		node = node->next;
	}

	return node;

}

bool CloseTrigger::trigger(KeyboardIn * mouse, KeyboardOut * keys) {
	if (mouse->mouse->detect(button->hitbox)) {
		button->SetAnimation(1);
		if (keys->checkBRelease(mouse->getButtonListAt(Mouse::Left), Mouse::Left)) {
			cout << "Closing\n";
			return true;
		}
		return false;
	}
	button->SetAnimation(0);
	return false;
}

void CloseTrigger::event(GameEngine* g) {
	g->window.close();
}
