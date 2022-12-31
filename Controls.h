#pragma once
#include <iostream>
#include "KeyboardOut.h"

class GameEngine;

class Control{
public:
	virtual bool trigger(shared_ptr<KeyboardIn> mouse, shared_ptr<KeyboardOut> keys) = 0;

	virtual void event(GameEngine* g) = 0;
};
class Node {
public:
	shared_ptr<Control> control;
	shared_ptr<Node> next;


	Node(shared_ptr <Control> c) {
		this -> control = c;
		this -> next = NULL;
	}
	void setNext(shared_ptr <Node> n) { this -> next = n; }
};
class Controls {
public:	
	
	int controlsSize;

	shared_ptr <Node> first;
	shared_ptr<Node> last;

	Controls() {
		controlsSize = 0;
		first = NULL;
		last = NULL;
	}

	shared_ptr<Node> addControl(shared_ptr <Control> c) {
		if (controlsSize == 0) {
			first = shared_ptr<Node>(new Node(c));
			last = first;
			controlsSize++;
			return first;
		}
		else {
			shared_ptr<Node> new_node =shared_ptr<Node>(new Node(c));
			last->setNext(new_node);
			last = new_node;
			controlsSize++;
			return last;
		}
	}
	void removeControl(shared_ptr<Node> node) {
		if (controlsSize == 0) return;
		shared_ptr<Node> temp = first;
		shared_ptr<Node> temp2 = last;
		shared_ptr<Node> temp3;
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
	void truncateControls(shared_ptr<Node> node) {
		shared_ptr<Node> temp = first;
		shared_ptr<Node> temp2 = last;
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
				temp2->setNext(NULL);
				last = temp2;
			}
		}
	}
	void triggerAll(shared_ptr<KeyboardIn> keyboardIn, shared_ptr<KeyboardOut> keyboardOut, GameEngine* g) {
		shared_ptr<Node> temp = first;
		for (int i = 0; i < this->controlsSize; i++) {
			if (temp == nullptr)break;
			if (temp->control->trigger(keyboardIn, keyboardOut)) temp->control->event(g);
			temp = temp->next;
		}
	}
	void clearControls() {
		shared_ptr<Node> temp = first;
		shared_ptr<Node> temp2 = last;
		for (int i = 0; i < controlsSize; i++) {
			temp2 = temp->next;
			int n = temp.use_count();
			for (int x = 0; x < n; x++)
				temp.reset();
			temp = temp2;
		}
		first = NULL;
		last = NULL;
		controlsSize = 0;
	}
	shared_ptr<Node> getIndex(int i) {
		if (i > controlsSize || i < 0)return first;
		shared_ptr<Node> node = first;
		for (int x = 0; x < i; x++) {
			node = node->next;
		}
		return node;
	}
};
