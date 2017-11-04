#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// TODO 2: Place the camera one unit up in Y and one unit to the right
	// experiment with different camera placements, then use LookAt()
	// to make it look at the center

	vec3 center(0, 0, 0);

	App->camera->Position.Set(10, 10, 0);
	App->camera->Look(App->camera->Position,center,true);
	App->camera->LookAt(center);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 1: Create a Plane primitive. This uses the plane formula
	// so you have to express the normal of the plane to create 
	// a plane centered around 0,0. Make that it draw the axis for reference

	int x=0, y=0, z=0;

	Plane myplane;
	vec3 mynormal(x, y, z);
	
	myplane.normal = mynormal;
	myplane.axis = true;

	myplane.Render();

	// TODO 6: Draw a sphere of 0.5f radius around the center
	// Draw somewhere else a cube and a cylinder in wireframe
	vec3 axis_x(1, 0, 0);
	vec3 axis_y(0, 1, 0);
	vec3 axis_z(0, 0, 1);

	Color yellow(255, 255, 0, 0);

	Sphere mysphere;
	Cylinder mycylinder;
	Cube mycube;

	mycylinder.height = 10;
	mycube.color = yellow;

	mycube.SetPos(10, 0, 0);
	mycylinder.SetPos(0, 0, 10);

	mycylinder.wire = true;
	mycylinder.SetRotation(45,axis_y);

	mycube.Render();
	mycylinder.Render();
	mysphere.Render();

	return UPDATE_CONTINUE;
}

