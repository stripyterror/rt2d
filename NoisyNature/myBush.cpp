#include "myBush.h"

MyBush::MyBush() : Entity()
{
	this->addSprite("assets/Bush.tga");

	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();

	this->position = Point2(mousex, mousey);
	this->rotation = Point2(180, 0);
	this->scale = Point2(1, 2);
}

MyBush::~MyBush()
{

}

void MyBush::update(float deltaTime)
{

}