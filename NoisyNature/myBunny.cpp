
#include "myBunny.h"

MyBunny::MyBunny() : Entity()
{
	this->addSprite("assets/Bunny.tga");

	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();

	this->position = Point2(mousex, mousey);
	this->rotation = Point2(180, 0);
	this->scale = Point2(2, 4);
}

MyBunny::~MyBunny()
{
	
}

void MyBunny::update(float deltaTime) 
{

}