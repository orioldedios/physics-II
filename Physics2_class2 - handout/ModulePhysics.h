#pragma once
#include "Module.h"
#include "Globals.h"

#include "Box2D\Box2D\Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class b2World;
class b2Body;

class b2Vec2;

// TODO 6: Create a small class that keeps a pointer to tghe b2Body
// and has a method to request the position
// then write the implementation in the .cpp
// Then make your circle creation function to return a pointer to that class

class b2BodyPointer {

public:
	b2Body* body=nullptr;

	b2BodyPointer(){}
	b2BodyPointer(b2Body& body_aux){
		this->body = &body_aux;
	}

	b2Vec2 GetPositionBody();
};


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	// TODO 4: Move body creation to 3 functions to create circles, rectangles and chains
	b2BodyPointer* CreateCircle(int Mouse_x, int Mouse_y, int radius);
	void CreateRectangle(int Mouse_x, int Mouse_y, int width,int height);
	void CreateRick(int Mouse_x, int Mouse_y);

	p2List<b2BodyPointer> BodyList;

private:

	bool debug;
	b2World* world;
};