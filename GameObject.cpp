#include "GameObject.h"

using namespace sf;

//Template

/*
Game Object template

class template : public GameObject {

public:
	template(Render* render) {
		spriteW = 1920;
		spriteH = 1080;
		unitsW = 2;
		unitsH = 2;

		texture.loadFromFile("Textures\\template.png", IntRect(0, 0, 1920, 1080));
		Sprite sprite = Sprite(texture);

		node = render->addToRender(sprite, spriteW, spriteH);
		nodeNum = render->getSize();

		//Animations
		int animation[60][2];

		createStillAnimation(animation); // fillAnimation(animation, 0, 0, 0, 20);

		node->animation->addAnimation(0, animation);

		this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteW, this->spriteH);
	}
};*/
class Background : public GameObject {

public:
	Background(shared_ptr<Render> render) {
		spriteW =  make_shared<int>(1920);
		spriteH = make_shared<int>(1080);
		xPos = make_shared<int>(0);
		yPos = make_shared<int>(0);

		unitsW = 1;
		unitsH = 1;

		texture.loadFromFile("Textures\\Test_Menu\\Test_Background.png", IntRect(0, 0, 1920, 1080));
		Sprite sprite = Sprite(texture);

		node = render->addToRender(sprite, xPos, yPos, spriteW, spriteH);
		nodeNum = render->getSize();

		//Animations
		int animation[60][2];

		createStillAnimation(animation, 0, 0); // fillAnimation(animation, 0, 0, 0, 20);

		node->animation->addAnimation(0, animation);

		this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteW, this->spriteH);
	}
};

class CloseButton : public GameObject {

public:
	CloseButton(shared_ptr<Render> render) {
		spriteW = make_shared<int>(500);
		spriteH = make_shared<int>(250);
		xPos = make_shared<int>(710);
		yPos = make_shared<int>(415);
		
		unitsW = 2;
		unitsH = 1;

		texture.loadFromFile("Textures\\Test_Menu\\close.png", IntRect(0, 0, 1920, 1080));
		Sprite sprite = Sprite(texture);

		node = render->addToRender(sprite, xPos, yPos, spriteW, spriteH);
		nodeNum = render->getSize();

		//Animations
		int animation[60][2];

		createStillAnimation(animation,0,0); // fillAnimation(animation, 0, 0, 0, 60);
		node->animation->addAnimation(0, animation);

		createStillAnimation(animation, 1, 0);
		node->animation->addAnimation(1, animation);

		this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteH, this->spriteW);
	}
};