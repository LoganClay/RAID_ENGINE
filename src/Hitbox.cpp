#include "Hitbox.h"

using namespace std;

Hitbox::Hitbox(shared_ptr<int> x, shared_ptr<int>y, shared_ptr<int> h, shared_ptr<int> w) {
	this->h = h;
	this->w = w;
	this->x = x;
	this->y = y;
}
bool Hitbox::detect(Hitbox* box){
	if ((*this->x < *box->x + *box->w) && (*this->x + *this->w > *box->x) && (*this->y < *box->y + *box->h) && (*this->y + *this->h > *box->y)) return true;
	return false;
}

void Hitbox::setX(shared_ptr<int> x) { this->x = x; }

void Hitbox::setY(shared_ptr<int> y) { this->y = y; }

void Hitbox::setW(shared_ptr<int> h) { this->h = h; }

void Hitbox::setH(shared_ptr<int> w) { this->w = w; }