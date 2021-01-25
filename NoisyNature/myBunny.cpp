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
	this->speed = 100;
	this->hunger = 0;
	this->hungerdelay = 3;
	this->eatingtime = 5;

	velocity.x = 1;
	velocity.y = 1;

	ht.start();

	
	closestbush = nullptr;
	Point2 test(10, 10);
}

MyBunny::~MyBunny()
{
	
}

//searches for the closest bush to the bunny
MyBush* MyBunny::FindPlant(std::vector<MyBush*> & bl)
{
	//closestbush = nullptr;

	for (MyBush* cb : bl)
	{
		Vector2 distanceToBush = cb->position - this->position;
		dtb = distanceToBush.getLength();
		if (dtb < distanceToClosestBush)
		{
			distanceToClosestBush = dtb;
			closestbush = cb;
		}
	}
	return closestbush;
} 

//lets the bunny walk
void MyBunny::WalktoPlant(float deltaTime)
{
	if (closestbush != nullptr && this->position != closestbush->position)
	{
		Vector2 np = this->position - closestbush->position;
		this->position -= np.getNormalized() * (speed * deltaTime);
	}
}

bool MyBunny::Eat()
{
	if (inEatingDistance && eating == false) {
		eb.start();
		eating = true;
	}

	if (eb.seconds() >= 5)
	{
		inEatingDistance = false;
		doneEating = true;
		eating = false;
		
		
	}
	return doneEating;
}

void MyBunny::update(float deltaTime) 
{

	if (ht.seconds() > hungerdelay)
	{
		ht.start();
		this->hunger += 5;
	}

	if (hunger >= 20 && eating == false)
	{
		WalktoPlant(deltaTime);
	}

	if (closestbush != nullptr)
	{
		if (distanceToClosestBush <= 5)
		{
			inEatingDistance = true;
			Eat();
		}
	}
}