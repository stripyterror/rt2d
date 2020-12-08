#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <rt2d/noise.h>
#include <rt2d/util.h>
#include "myBunny.h"

class BasicEntity : public Entity
{
public:
	BasicEntity() : Entity() { };
	virtual ~BasicEntity() { };

	virtual void update(float deltaTime) { };
};


#define water RGBAColor(127, 127, 215)
#define grass RGBAColor(100, 185, 90)
#define wetgrass RGBAColor(64, 127, 64)


class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	Timer t;
	BasicEntity* entity;

	MyBunny* mybunny;

	PerlinNoise* pn;

	bool contrast;
	bool posterize;
	bool colorize;
};

#endif /* MYSCENE_H */
