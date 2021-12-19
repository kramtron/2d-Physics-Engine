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

	nombres = App->textures->Load("Assets/numeros.png");
	vari = App->textures->Load("Assets/variables.png");
	inter = App->textures->Load("Assets/integradors.png");
	f_p_s = App->textures->Load("Assets/fps.png");
	arma = App->textures->Load("Assets/armas.png");

	//Suelos
	App->physics->enemic.add(App->physics->createStaticRectangle(75, 500, 250, 70));
	App->physics->enemic.add(App->physics->createStaticRectangle(700, 500, 250, 70));
	App->physics->enemic.add(App->physics->createStaticRectangle(380, 300, 250, 70));

	//Agua
	aigua = App->physics->createStaticRectangle(0, 700, 1200, 100, 1);	//y=700 h=100

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

		//Font Drawing
		//need dt, player selected, windx, windy, gravityx, gravityy, shot angle, shot velocity
		//FontDraw(App->physics->deltaTime, 5, 300, 60, 16, 0.5);
		FontDraw(App->physics->wind_X, 5, 326, 80, 16, 0.5);
		FontDraw(App->physics->wind_Y, 5, 326, 115, 16, 0.5);
		FontDraw(App->physics->gravity_X/100, 5, 326, 10, 16, 0.5);
		FontDraw(App->physics->gravity_Y/100, 5, 326, 45, 16, 0.5);

		SDL_Rect g_x = { 861, 140, 380, 55 };
		App->renderer->Blit(vari,76,10, &g_x, 0.4);
		SDL_Rect g_y = { 867, 212, 380, 55 };
		App->renderer->Blit(vari,76,45, &g_y, 0.4);
		SDL_Rect w_x = { 966, 284, 276, 55 };
		App->renderer->Blit(vari, 115, 80, &w_x, 0.4);
		SDL_Rect w_y = { 966, 356, 276, 55 };
		App->renderer->Blit(vari, 115, 115, &w_y, 0.4);

		if (App->player->playerNum == 1)
		{
			FontDraw(App->player->cannonPlayer1.angle, 5, 326, 150, 16, 0.5);
			FontDraw(App->player->cannonPlayer1.velocity, 5, 326, 185, 16, 0.5);
			SDL_Rect s_a = { 805, 425, 634, 55 };
			App->renderer->Blit(vari, 49, 150, &s_a, 0.4);
			SDL_Rect s_v = { 710, 502, 634, 55 };
			App->renderer->Blit(vari, 10, 185, &s_v, 0.4);
			if (App->player->cannonPlayer1.gun == 1)
			{
				SDL_Rect a_g = { 36, 69, 535, 60 };
				App->renderer->Blit(arma, 10, 290, &a_g, 0.3);
			}
			else if (App->player->cannonPlayer1.gun == 2)
			{
				SDL_Rect a_c = { 36, 141, 535, 60 };
				App->renderer->Blit(arma, 10, 290, &a_c, 0.3);
			}
		}
		else if (App->player->playerNum == 2)
		{
			FontDraw(App->player->cannonPlayer2.angle, 5, 326, 150, 16, 0.5);
			FontDraw(App->player->cannonPlayer2.velocity, 5, 326, 185, 16, 0.5);
			SDL_Rect s_a = { 805, 425, 634, 55 };
			App->renderer->Blit(vari, 49, 150, &s_a, 0.4);
			SDL_Rect s_v = { 710, 500, 634, 55 };
			App->renderer->Blit(vari, 10, 185, &s_v, 0.4);
			if (App->player->cannonPlayer2.gun == 1)
			{
				SDL_Rect a_g = { 36, 69, 535, 60 };
				App->renderer->Blit(arma, 10, 290, &a_g, 0.3);
			}
			else if (App->player->cannonPlayer2.gun == 2)
			{
				SDL_Rect a_c = { 36, 141, 535, 60 };
				App->renderer->Blit(arma, 10, 290, &a_c, 0.3);
			}
		}

		if (App->physics->integrator == ModulePhysics::Integrator_Type::VERLET)
		{
			SDL_Rect ver = { 24, 214, 1120, 55 };
			App->renderer->Blit(inter, 10, 220, &ver, 0.3);
		}
		else if (App->physics->integrator == ModulePhysics::Integrator_Type::EULER_BACK)
		{
			SDL_Rect ver = { 24, 142, 1120, 55 };
			App->renderer->Blit(inter, 10, 220, &ver, 0.3);
		}
		else if (App->physics->integrator == ModulePhysics::Integrator_Type::EULER_FORW)
		{
			SDL_Rect ver = { 24, 70, 1120, 55 };
			App->renderer->Blit(inter, 10, 220, &ver, 0.3);
		}

		if (App->physics->deltaTime == 0.0167f)
		{
			SDL_Rect fps60 = { 24, 69, 1120, 55 };
			App->renderer->Blit(f_p_s, 10, 255, &fps60, 0.3);
		}
		else if (App->physics->deltaTime == 0.0333f)
		{
			SDL_Rect fps30 = { 24, 141, 1120, 55 };
			App->renderer->Blit(f_p_s, 10, 255, &fps30, 0.3);
		}

		SDL_Rect f_g = { 861, 140, 40, 55 };
		App->renderer->Blit(vari, 697, 62, &f_g, 0.5);

		SDL_Rect f_w = { 966, 284, 55, 55 };
		App->renderer->Blit(vari, 855, 55, &f_w, 0.5);

		

		FontDraw(App->physics->player.getFirst()->data->hp, 2, App->physics->player.getFirst()->data->x + 17, App->physics->player.getFirst()->data->y - 20, 16, 0.4);
		FontDraw(App->physics->player.getLast()->data->hp, 2, App->physics->player.getLast()->data->x + 17, App->physics->player.getLast()->data->y - 20, 16, 0.4);

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

void ModuleSceneIntro::FontDraw(int score, int n, int posX, int posY, int separacio, float scale) {
	bool positive = true;
	if (score < 0) {
		positive = false;
		score = -score;
	}

	int scoreCopia = score;
	int scoreArray[10];	//max numbers
	for (int j = 0; j < n; ++j) {
		scoreArray[j] = scoreCopia % 10;
		scoreCopia /= 10;
	}

	SDL_Rect rect0 = { 259, 65, 33, 40 };
	SDL_Rect rect1 = { 25, 11, 20, 38 };
	SDL_Rect rect2 = { 80, 10, 29, 40 };
	SDL_Rect rect3 = { 141, 10, 30, 40 };
	SDL_Rect rect4 = { 200, 11, 31, 38 };
	SDL_Rect rect5 = { 261, 10, 29, 40 };
	SDL_Rect rect6 = { 19, 65, 32, 40 };
	SDL_Rect rect7 = { 82, 65, 26, 40 };
	SDL_Rect rect8 = { 140, 65, 31, 40 };
	SDL_Rect rect9 = { 199, 65, 32, 40 };
	SDL_Rect rect_ = { 0, 113, 31, 11 };

	for (int k = 0; k < n; ++k) {

		switch (scoreArray[k]) {
		case 0:
			App->renderer->Blit(nombres, posX, posY, &rect0, scale);
			break;
		case 1:
			App->renderer->Blit(nombres, posX, posY, &rect1, scale);
			break;
		case 2:
			App->renderer->Blit(nombres, posX, posY, &rect2, scale);
			break;
		case 3:
			App->renderer->Blit(nombres, posX, posY, &rect3, scale);
			break;
		case 4:
			App->renderer->Blit(nombres, posX, posY, &rect4, scale);
			break;
		case 5:
			App->renderer->Blit(nombres, posX, posY, &rect5, scale);
			break;
		case 6:
			App->renderer->Blit(nombres, posX, posY, &rect6, scale);
			break;
		case 7:
			App->renderer->Blit(nombres, posX, posY, &rect7, scale);
			break;
		case 8:
			App->renderer->Blit(nombres, posX, posY, &rect8, scale);
			break;
		case 9:
			App->renderer->Blit(nombres, posX, posY, &rect9, scale);
			break;
		}

		posX -= separacio; //Separació entre nombres
	}

	if (!positive) {
		App->renderer->Blit(nombres, posX, posY + 10, &rect_, scale);
	}
}