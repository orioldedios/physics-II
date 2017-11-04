#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

#include "Box2D\Box2D\Box2D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");

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
	// TODO 5: Move all creation of bodies on 1,2,3 key press here in the scene
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{

		App->physics->CreateRick(App->input->GetMouseX(), App->input->GetMouseY());
	}
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->physics->BodyList.add(*App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 50));

	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 25, 50);

	}
	// TODO 7: Draw all the circles using "circle" texture


	for (p2List_item<b2BodyPointer>* body_iterator=App->physics->BodyList.getFirst();body_iterator!=nullptr;body_iterator=body_iterator->next)
	{
		App->renderer->Blit(circle,body_iterator->data.GetPositionBody().x, body_iterator->data.GetPositionBody().y);

		
	}


	return UPDATE_CONTINUE;
}
