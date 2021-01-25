#include <fstream>
#include <sstream>
#include <algorithm>

#include "myscene.h"

 //RGBAColor terrain[3] = { water, grass, wetgrass }; // debug
RGBAColor terrain[3] = { water, grass, wetgrass }; 

MyScene::MyScene() : Scene()
{
	t.start();

	srand((unsigned)time(nullptr));

	// Create a PerlinNoise object with a random permutation vector generated with seed
	unsigned int seed = rand() % 1000;
	//unsigned int seed = 242;
	pn = new PerlinNoise(seed);

	// container for Sprite with custom Texture
	entity = new BasicEntity();
	entity->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	entity->scale = Point2(32.0f, 32.0f);
	// width, height, bitdepth, filter, wrap
	PixelBuffer pixels = PixelBuffer(32, 32, 3, 0, 0);
	entity->addDynamicSprite(&pixels);

	contrast = true;
	posterize = true;
	colorize = true;

	

	this->addChild(entity);


	
}

MyScene::~MyScene()
{
	this->removeChild(entity);
	delete entity;

	for(MyBunny* b : bunnylist) 
	{
		this->removeChild(b);
		delete b;
	}

	for (MyBush* bu : bushlist)
	{
		this->removeChild(bu);
		delete bu;
	}

	delete pn;
}

void MyScene::update(float deltaTime)
{
	

	if (t.seconds() > 0.02f) {
		PixelBuffer* pixels = entity->sprite()->texture()->pixels();

		unsigned int width = pixels->width;
		unsigned int height = pixels->height;

		long counter = 0;
		// Visit every pixel of the image and assign a color generated with Perlin noise
		for (unsigned int i = 0; i < height; ++i) {     // y
			for (unsigned int j = 0; j < width; ++j) {  // x
				// map width and height between 0 and 1
				double x = (double)j / ((double)width);
				double y = (double)i / ((double)height);
				double z = 0.0f;


				// find a nice noise for our purpose
				// pn->noise(xsize, ysize, zsize) * multiplier;
				double a = pn->noise(1 * x, 1 * y, 1 * z) * 2;
				double b = pn->noise(5 * x, 5 * y, 5 * z) * 3;
				double c = pn->noise(9 * x, 9 * y, 9 * z) * 1;

				// average of noises ("octaves")
				double n = (a + b + c) / 7;

				// make an int in range 0-255 from n
				int p = floor(255 * n);

				// the color. no contrast, not posterized, not colored.
				RGBAColor color = RGBAColor(p, p, p, 255);

				// map for contrast. Averaging above made the image duller
				if (contrast) {
					p = map(p, 48, 208, 0, 255); // WARNING magic numbers
					color = RGBAColor(p, p, p, 255);
				}

				// posterize
				if (posterize) {
					int numcolors = 3; // ... and another one. Make sure there are enough colors in array above
					p = map(p, 0, 255, 0, numcolors);
					// colorize (only colorize if posterized)
					if (colorize) {
						color = terrain[p];
					}
					else {
						// restore and set color
						p = map(p, 0, numcolors, 0, 255);
						color = RGBAColor(p, p, p, 255);
					}
				}

				// color the pixel
				pixels->data[counter + 0] = color.r;
				pixels->data[counter + 1] = color.g;
				pixels->data[counter + 2] = color.b;
				if (pixels->bitdepth == 4) {
					pixels->data[counter + 3] = color.a;
				}
				counter += pixels->bitdepth;
			}
		}

		t.start();
	}

	//lets you spawn a bunny with the B button
	if (input()->getKeyDown(KeyCode::B))
	{
		MyBunny* bunny = new MyBunny();

		this->addChild(bunny);
		bunnylist.push_back(bunny);
	}

	//lets every bunny find the closest bush there is
	for (MyBunny* bunny :bunnylist)
	{
		bunny->FindPlant(bushlist);
	}

	//lets you spawn a bush with the U button
	if (input()->getKeyDown(KeyCode::U))
	{
		MyBush* bush = new MyBush();

		this->addChild(bush);
		bushlist.push_back(bush);

	}

	for (MyBunny* b : bunnylist)
	{
		if (b->doneEating)
		{
			//this->removeChild(b->closestbush);
			//delete b->closestbush;

			b->closestbush->isEaten = true;

			b->closestbush = nullptr;
			b->distanceToClosestBush = 10000000;
			b->doneEating = false;
		}
	}

	for (MyBush* b : bushlist) 
	{
		if (b->childBirth == true)
		{
			MyBush* bush = new MyBush();

			bush->position.x = std::rand() % 90 + 11 + b->position.x;
			bush->position.y = std::rand() % 90 + 11 + b->position.y;

			this->addChild(bush);
			bushlist.push_back(bush);
			b->childBirth = false;
		}

		if (b->isEaten) 
		{
			this->removeChild(b);

			std::vector<MyBush*>::iterator iterator = std::find(bushlist.begin(), bushlist.end(), b);

			if (iterator != bushlist.cend()) 
			{
				int index = std::distance(bushlist.begin(), iterator);
				bushlist.erase(bushlist.begin() + index);
			}
			delete b;
		}
	}
}