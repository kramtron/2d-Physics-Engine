#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "time.h"
#include "stdlib.h"
#include "math.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{

	
	LOG("Loading Intro assets");
	bool ret = true;
	//Suelos
	App->physics->enemic.add(App->physics->createStaticRectangle(75, 500, 250, 70));
	App->physics->enemic.add(App->physics->createStaticRectangle(700, 500, 250, 70));
	App->physics->enemic.add(App->physics->createStaticRectangle(380, 300, 250, 70));

	//Agua
	App->physics->enemic.add(App->physics->createStaticRectangle(0, 700, 1200, 100));


	return ret;
}

// Load assets
// Update: drabackground
update_status ModuleSceneIntro::Update()
{
	

	return UPDATE_CONTINUE;
}
update_status ModuleSceneIntro::PostUpdate() {

	
	return UPDATE_CONTINUE;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}