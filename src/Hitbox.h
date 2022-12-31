#pragma once

class Hitbox {
	public:
		int * x;
		int * y;
		int * w;
		int * h;

		Hitbox(int * x, int * y, int * h, int * w) : x(x), y(y), w(w), h(h) {};

		bool detect(Hitbox* box) {
			return ((*this->x < *box->x + *box->w) && 
					(*this->x + *this->w > *box->x) && 
					(*this->y < *box->y + *box->h) && 
					(*this->y + *this->h > *box->y));
		}

		void setX(int * x) { this->x = x; }
		void setY(int * y) { this->y = y; }
		void setW(int * h) { this->h = h; }
		void setH(int * w) { this->w = w; }
};
