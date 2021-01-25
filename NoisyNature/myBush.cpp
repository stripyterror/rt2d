#include "myBush.h"

MyBush::MyBush() : Entity()
{
	this->addSprite("assets/Bush.tga");

	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();

	this->position = Point2(mousex, mousey);
	this->rotation = Point2(180, 0);
	this->scale = Point2(1, 2);

	isEaten = false;
	childtimer = 0;
}

MyBush::~MyBush()
{

}

void MyBush::Duplicate() 
{
	if(childCooldown == false) {
		vt.start();
		childCooldown = true;
	}

	if (vt.seconds() - childtimer >= 10)
	{
		childtimer += 5;
		childCooldown = false;
		childBirth = true;
	}
}

void MyBush::update(float deltaTime)
{
	Duplicate();
}