#include "myBunny.h"

MyBunny::MyBunny() : Entity()
{
	this->addSprite("assets/Bunny.tga");

	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();

	this->position = Point2(mousex, mousey);
	this->rotation = Point2(180, 0);
	this->scale = Point2(1, 2);

	this->health = 10;
	this->hunger = 0;
	this->hungerdelay = 5;

	ht.start();

	
	closestbush = nullptr;
}

MyBunny::~MyBunny()
{
	
}

MyBush* MyBunny::FindPlant(std::vector<MyBush*> & bl)
{
	float distanceToClosestBush = 100000000;

	closestbush = nullptr;

	for (MyBush* cb : bl)
	{
		Vector2 distanceToBush = cb->position - this->position;
		float dtb = distanceToBush.getLength();
		if (dtb < distanceToClosestBush)
		{
			distanceToClosestBush = dtb;
			closestbush = cb;
		}
	}
	return closestbush;
} 

void MyBunny::update(float deltaTime) 
{
	if (ht.seconds() > hungerdelay)
	{
		ht.start();
		this->hunger += 5;
	}
}