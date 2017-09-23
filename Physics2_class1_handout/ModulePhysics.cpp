#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include <time.h>
#include <iostream>
#include "Box2D\Box2D\Box2D.h"

#ifdef _DEBUG
#pragma comment (lib,"Box2D/libx86/Debug/Box2D.lib")
#endif // _DEBUG

#ifdef _RELEASE
#pragma comment (lib,"Box2D/libx86/Release/Box2D.lib")
#endif // _RELEASE

#define PIXELS_TO_METERS(x) (x/10)
#define METERS_TO_PIXELS(x) (x*10)

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	srand(time(NULL));

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	b2Vec2 gravity(0.0f, 20.0f);

	myworld = new b2World(gravity);


	// TODO 4: Create a a big static circle as "ground"
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXELS_TO_METERS(500), PIXELS_TO_METERS(400));

	b2Body* ground=myworld->CreateBody(&body);

	b2CircleShape circle;
	circle.m_radius = PIXELS_TO_METERS(300);
	b2FixtureDef fixture;
	fixture.shape = &circle;
	ground->CreateFixture(&fixture);

	//FLOOR
	b2BodyDef bodyfloor;
	bodyfloor.type = b2_staticBody;
	bodyfloor.position.Set(PIXELS_TO_METERS(0), PIXELS_TO_METERS(750));

	b2Body* groundfloor = myworld->CreateBody(&bodyfloor);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(1100), PIXELS_TO_METERS(50));
	b2FixtureDef fixturefloor;
	fixturefloor.shape = &box;
	groundfloor->CreateFixture(&fixturefloor);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	myworld->Step(1.0f / 60.0f, 8, 3);
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if (App->input->GetKey(SDL_SCANCODE_SPACE)==KEY_DOWN)
	{
		b2BodyDef body;
		body.type = b2_dynamicBody;
		body.position.Set(PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()));

		b2Body* ground = myworld->CreateBody(&body);

		b2CircleShape circle;
		circle.m_radius = PIXELS_TO_METERS(rand()%(21-10)+10); 
		b2FixtureDef fixture;
		fixture.shape = &circle;
		ground->CreateFixture(&fixture);

	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = myworld->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
					break;
				}
				case b2Shape::e_polygon:
				{
					b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					SDL_Rect myrect;
					myrect.w = METERS_TO_PIXELS(shape->m_vertices[1].x*2);
					myrect.h = METERS_TO_PIXELS(shape->m_vertices[2].y*2);
					myrect.x = METERS_TO_PIXELS(pos.x)-myrect.w/2;
					myrect.y = METERS_TO_PIXELS(pos.y)-myrect.h/2;
					App->renderer->DrawQuad(myrect,255,255,255,255,true);
					break;
				}
				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	if (myworld!=nullptr)
	{
		delete myworld;
		myworld = nullptr;
	}

	return true;
}
