#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{

	/*ball.add(App->player->object2);
	ball.getLast()->data->createCircle(50,600,5);*/





	floor = { 0,600,1200,20 };

	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{

	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	/*if (App->physics->object[1].y - 60 == 600) {
		App->physics->object[1].vy = 0;
	}

	if (App->physics->object[2].y  < -700) {
		App->physics->object[2].x = -10;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) {
		App->physics->object[App->physics->obectNum].acceleration = true;

	}
	else {
		App->physics->object[2].acceleration = false;
	}*/

	
	//Modifica el angulo de disparo
	
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		playerNum = 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		playerNum = 2;
	}
	//Priemr Jugador
	if (playerNum == 1) {

		//Modifica la velocidad normal del disparo de cañon
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {

			if (cannonPlayer1.velocity >= 500 && cannonPlayer1.velocity < 1500) {
				cannonPlayer1.velocity += 50;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {

			if (cannonPlayer1.velocity > 500 && cannonPlayer1.velocity <= 1500) {
				cannonPlayer1.velocity -= 50;
			}
		}

		

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

			if (cannonPlayer1.angle >= 0 && cannonPlayer1.angle < 90) {
				cannonPlayer1.angle += 15;
			}
			radiants = cannonPlayer1.angle * M_PI / 180;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

			if (cannonPlayer1.angle > 0 && cannonPlayer1.angle <= 90) {
				cannonPlayer1.angle -= 15;
			}
			radiants = cannonPlayer1.angle * M_PI / 180;
		}
		/*LOG("Angle player 1 %d: ", cannonPlayer1.angle);
		LOG("Normal Velocity player 1 %d: ", cannonPlayer1.velocity);*/
		//Sitio para aplicar fuerzas al jugador por el momento se mueve solo con posiciones de x e y
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			App->physics->player.getFirst()->data->x+=3;

		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			App->physics->player.getFirst()->data->x-=3;

		}
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

			App->physics->ball.add(App->physics->createCircle(50, 540, 5));
			App->physics->ball.getLast()->data->SetPlayerMass(40);
			//Dispara laa pelota desde la posicion del player
			App->physics->ball.getLast()->data->SetPlayerPosition((App->physics->player.getFirst()->data->x + App->physics->player.getFirst()->data->w),
				App->physics->player.getFirst()->data->y);

			App->physics->ball.getLast()->data->SetVelocity(cannonPlayer1.velocity * cos(-radiants),
				cannonPlayer1.velocity * sin(-radiants));

		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			App->physics->player.getFirst()->data->SetForce(0, 100);
			App->physics->player.getFirst()->data->SetVelocity(0,-500);
		}
	}
	//Segundo jugador
	if (playerNum == 2) {

		//Modifica la velocidad normal del disparo de cañon
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {

			if (cannonPlayer2.velocity >= 500 && cannonPlayer2.velocity < 1500) {
				cannonPlayer2.velocity += 50;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {

			if (cannonPlayer2.velocity > 500 && cannonPlayer2.velocity <= 1500) {
				cannonPlayer2.velocity -= 50;
			}
		}

		

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

			if (cannonPlayer2.angle >= 0 && cannonPlayer2.angle < 90) {
				cannonPlayer2.angle += 15;
			}
			radiants = cannonPlayer2.angle * M_PI / 180;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

			if (cannonPlayer2.angle > 0 && cannonPlayer2.angle <= 90) {
				cannonPlayer2.angle -= 15;
			}
			radiants = cannonPlayer1.angle * M_PI / 180;
		}
		/*LOG("Angle player 1 %d: ", cannonPlayer2.angle);
		LOG("Normal Velocity player 1 %d: ", cannonPlayer2.velocity);*/
		//Sitio para aplicar fuerzas al jugador por el momento se mueve solo con posiciones de x e y
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			App->physics->player.getLast()->data->x += 3;

		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			App->physics->player.getLast()->data->x -= 3;

		}
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

			App->physics->ball.add(App->physics->createCircle(50, 540, 5));
			App->physics->ball.getLast()->data->SetPlayerMass(40);
			//Dispara laa pelota desde la posicion del player
			App->physics->ball.getLast()->data->SetPlayerPosition((App->physics->player.getLast()->data->x),
				App->physics->player.getLast()->data->y);

			App->physics->ball.getLast()->data->SetVelocity(-(cannonPlayer2.velocity * cos(-radiants)),
				(cannonPlayer2.velocity * sin(-radiants)));

		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			App->physics->player.getLast()->data->SetForce(0, 100);
			App->physics->player.getLast()->data->SetVelocity(0, -500);
		}
	}
	



	

	
	

	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
		//App->physics->enemic.add(App->physics->createStaticRectangle(500, 600, 20, -100));
	}
	//LOG("Radiants %f: ", radiants);


	

	App->renderer->DrawQuad(floor, 255, 255, 0);
	//GetPlayerPosition(player);

	
	playerRect = { 20,540,30,60 };
	App->renderer->DrawQuad(playerRect, 255, 0, 0);
	

	
	return UPDATE_CONTINUE;
}

 
update_status ModulePlayer::PostUpdate() {

	



	return UPDATE_CONTINUE;
}







