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