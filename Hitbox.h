#pragma once
#include <iostream>

using namespace std;

class Hitbox
{
public:
	shared_ptr<int> x, y;
	shared_ptr<int> w, h;

	Hitbox(shared_ptr<int> x, shared_ptr<int> y, shared_ptr<int> h, shared_ptr<int> w);

	bool detect( Hitbox* box );
	
	void setX(shared_ptr<int> x);
	void setY(shared_ptr<int> y);
	void setW(shared_ptr<int> h);
	void setH(shared_ptr<int> w);
};

