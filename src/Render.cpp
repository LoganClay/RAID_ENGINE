#include "Render.h"

Render::Render(){
	renderSize = 0;
	first = NULL;
	last = NULL;
}

void Render::Animation::addAnimation(int n, int array[60][2]) {
	for (int i = 0; i < FRAMES; i++) {
		for (int x = 0; x < COORDS; x++) {
			animationPatterns[n][i][x] = array[i][x];
		}
	}
	this->activeAnimations++;
}

void Render::Animation::setAnimation(int n) { 
	this->currentAnimation = n;
	this->currentFrame = 0;
}

void Render::Animation::iterate(Render::Node* node) {
	if (currentFrame < FRAMES-1){ currentFrame++; }
	else { currentFrame = 0; }
	
	int x = animationPatterns[this->currentAnimation][currentFrame][0];
	int	y = animationPatterns[this->currentAnimation][currentFrame][1];
	int w = *node->w;
	int h = *node->h;

	

	//cout << w*x << ", " << h*y << ", frame: " << currentFrame << endl;
	node->sprite.setTextureRect(IntRect( w * x, h * y, w, h));

	//cout << *node->x << ", " << *node->y << endl;
	node->sprite.setPosition(*node->x, *node->y);
}

Render::Node* Render::addToRender(Sprite object, shared_ptr<int> x, shared_ptr<int> y, shared_ptr<int> w, shared_ptr<int> h) {
	if (renderSize == 0) {
		first = new Node(object, x, y, w, h);
		last = first;
		renderSize++;
		return first;
	}
	else {
		Node* new_node = new Node(object,x, y, w, h);
		last -> setNext(new_node);
		last = new_node;
		renderSize++;
		return last;
	}
}

void Render::removeFromRender(Render::Node* node){
	if (renderSize == 0) return;
	Node *temp = first;
	Node *temp2 = last;
	Node *temp3;
	for (int i = 0; i < renderSize; i++) {
		if (temp ==  node && i == 0) {
			temp2 = temp->next;
			delete temp;
			first = temp2;
			break;
		}
		else if (temp == node && i == renderSize-1) {
			last = temp2;
			delete temp;
			break;
		}
		else if (temp == node) {
			temp3 = temp->next;
			temp2->setNext(temp3);
			delete temp;
			break;
		}
		temp2 = temp;
		temp = temp->next;
	}
	renderSize--;
}

void Render::removeFromRender(int i){
	if (i > renderSize || i < 0)return;

	Node* temp = first;
	Node* temp2 = last;
	Node* temp3;

	for (int x = 0; x < i; i++) {
		temp2 = temp;
		temp = temp->next;
	}
	temp3 = temp->next;
	temp2->setNext(temp3);
	delete temp;
}

void Render::truncateRender(Sprite object){
	Node* temp = first;
	Node* temp2 = last;
	int sizeTemp = renderSize;
	bool trunc=false;
	for (int i = 0; i < sizeTemp; i++) {
		if (trunc) {
			temp2 = temp->next;
			delete temp;
			temp = temp2;
			renderSize--;
		}
		else {
			temp2 = temp;
			temp = temp->next;
		}
		if (trunc==false && temp->sprite.getTexture() == object.getTexture()) {
			trunc = true;
			temp2->setNext(NULL);
			last = temp2;
		}
	}
}

void Render::truncateRender(int x){
	Node* temp = first;
	Node* temp2 = last;
	for (int i = 0; i < renderSize; i++) {
		if (i > x) {
			temp2 = temp->next;
			delete temp;
			temp = temp2;
			renderSize--;
		}
		else {
			temp2 = temp;
			temp = temp->next;
		}
		if (i == x) {
			temp2->setNext(NULL);
			last = temp2;
		}
	}
}

void Render::clearRender(){
	Node *temp = first;
	Node *temp2 = last;
	for (int i = 0; i < renderSize; i++) {
		temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
	first = NULL;
	last = NULL;
	renderSize = 0;
}

Render::Node* Render::getIndex(int i){
	if ( i >= renderSize || i < 0 )return first;
	Node* node=first;
	for (int x = 0; x < i; x++) {
		node = node->next;
	}
	return node;
}

Render::Node* Render::getFirst(){
	return first;
}

Render::Node* Render::getLast(){
	return last;
}

int Render::getSize() { return this->renderSize; }


Render::Node::Node(Sprite object, shared_ptr<int> x, shared_ptr<int> y, shared_ptr<int> w, shared_ptr<int> h){
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	sprite = object;
	this->next = NULL;
	this->animation = new Animation();
}



void Render::Node::setNext(Node *node){
	next = node;
}

Render::Animation* Render::Node::getAnimation(){
	return this->animation;
}

void Render::Node::iterate(){
	this->animation->iterate(this);
}
