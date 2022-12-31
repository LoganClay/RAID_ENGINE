#pragma once
#include "KeyboardIn.h"
#include "KeyboardOut.h"
#include "GameObject.h"

// TODO circular dependencies -- Control -> GameEngine --> Controls --> Control
// This is gonna require some digging to figure out and refactor
class Control {
	public:
		virtual bool trigger(KeyboardIn * mouse,
							KeyboardOut * keys) = 0;

		virtual void event(RenderWindow * window) = 0;
};

class Node {
	public:
		Control * control;
		Node * next;

		Node(Control * c);
		void setNext(Node * n);
};

class Controls {
	public:	
		int controlsSize;

		Node * first;
		Node * last;

		Controls() : controlsSize(0), first(nullptr), last(nullptr) {}
		Node * addControl(Control * c);
		Node * getIndex(int i);
		void removeControl(Node * node);
		void truncateControls(Node * node);
		void clearControls();
};

class CloseTrigger : public Control {
	public:
		CloseButton * button;
		CloseTrigger(CloseButton * b) : button(b) {}
		bool trigger(KeyboardIn * mouse, KeyboardOut * keys);
		void event(RenderWindow * window);
};
