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
	/*p2List_item<ObjectDef*>* current_ball = App->physics->ball.getFirst();
	while (current_ball != NULL)*/
	


		SDL_Rect leftInactiveArrow = { 800,60,40,20 };
		SDL_Rect leftActiveArrow = { 800,60,40,20 };
		mouse.x = App->input->GetMouseX();
		mouse.y = App->input->GetMouseY();

		if (mouse.x > leftInactiveArrow.x && mouse.x<(leftInactiveArrow.x + leftInactiveArrow.w)
			&& mouse.y>leftInactiveArrow.y && mouse.y < (leftInactiveArrow.y + leftInactiveArrow.h)) {

			App->renderer->DrawQuad(leftActiveArrow, 116, 190, 227);
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN) {
				App->renderer->DrawQuad(leftActiveArrow, 255, 0, 0);
				App->physics->wind_X -= 100;
				
			}
			


		}
		else {
				App->renderer->DrawQuad(leftInactiveArrow, 112, 33, 166);
			
		}
		
		SDL_Rect rightInactiveArrow = { 900,60,40,20 };
		SDL_Rect rightActiveArrow = { 900,60,40,20 };

		if (mouse.x > rightInactiveArrow.x && mouse.x<(rightInactiveArrow.x + rightInactiveArrow.w)
			&& mouse.y>rightInactiveArrow.y && mouse.y < (rightInactiveArrow.y + rightInactiveArrow.h)) {

			App->renderer->DrawQuad(rightInactiveArrow, 116, 190, 227);
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN) {
				App->renderer->DrawQuad(rightActiveArrow, 255, 0, 0);
				App->physics->wind_X += 100;
			}


		}
		else {
			
				App->renderer->DrawQuad(rightInactiveArrow, 112, 33, 166);
			
		}




		SDL_Rect upInactiveArrow = { 700,20,20,40 };
		SDL_Rect upActiveArrow = { 700,20,20,40 };
		mouse.x = App->input->GetMouseX();
		mouse.y = App->input->GetMouseY();

		if (mouse.x > upInactiveArrow.x && mouse.x<(upInactiveArrow.x + upInactiveArrow.w)
			&& mouse.y>upInactiveArrow.y && mouse.y < (upInactiveArrow.y + upInactiveArrow.h)) {

			App->renderer->DrawQuad(upInactiveArrow, 116, 190, 227);
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN) {
				App->renderer->DrawQuad(upInactiveArrow, 255, 0, 0);
				App->physics->gravity_Y -= 100;

			}



		}
		else {
			App->renderer->DrawQuad(upInactiveArrow, 112, 33, 166);

		}

		SDL_Rect downInactiveArrow = { 700,90,20,40 };
		SDL_Rect downtActiveArrow = { 700,90,20,40 };

		if (mouse.x > downInactiveArrow.x && mouse.x<(downInactiveArrow.x + downInactiveArrow.w)
			&& mouse.y>downInactiveArrow.y && mouse.y < (downInactiveArrow.y + downInactiveArrow.h)) {

			App->renderer->DrawQuad(downInactiveArrow, 116, 190, 227);
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN) {
				App->renderer->DrawQuad(downInactiveArrow, 255, 0, 0);
				App->physics->gravity_Y += 100;
			}


		}
		else {

			App->renderer->DrawQuad(downInactiveArrow, 112, 33, 166);

		}
		//current_ball = current_ball->next;
		LOG("Wind %.2f", App->physics->wind_X/10);
		LOG("Gravity %.2f", App->physics->gravity_Y/100);
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