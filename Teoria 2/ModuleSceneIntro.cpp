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
	aigua = App->physics->createStaticRectangle(0, 505, 1200, 1000, 1);	//y=700 h=100

	srand(time(NULL));

	App->physics->wind_X = rand() % 101;
	App->physics->wind_X = App->physics->wind_X - 50;
	LOG("wind_X: %f", App->physics->wind_X);

	App->physics->wind_Y = rand() % 30;
	App->physics->wind_Y = App->physics->wind_Y - 15;
	LOG("wind_Y: %f", App->physics->wind_Y);

	return ret;
}

// Load assets
// Update: drabackground
update_status ModuleSceneIntro::Update()
{


	return UPDATE_CONTINUE;
}
update_status ModuleSceneIntro::PostUpdate() 
{

	
	return UPDATE_CONTINUE;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}