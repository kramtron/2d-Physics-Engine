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
		if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {//Puedes cambiar entre las 2 armas. Se tiene que descomentar la parte comentada para que funcione. 
			//No descomentar hasta que los 2 tipos de armas esten inplemtentados porque salta un null si intentas crear un arma de tipo rocket.
			if (cannonPlayer1.gun == 1) {
				//cannonPlayer1.gun = 2;
			}
			else if (cannonPlayer1.gun == 2) {
				cannonPlayer1.gun = 1;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) {
			//Dependiendo del tipo de arma que hayas elegido en el if de la linea 107 te crea un tipo u otro de proyectil
			switch (cannonPlayer1.gun)
			{
			case 1:
				CreateObject(50, 540, 5,40, Type::GRENADE);
				break;
			case 2:
				CreateObject(50, 540, 5,40, Type::ROCKET);
				break;
			}
			//App->physics->ball.add(App->physics->createCircle(50, 540, 5));
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
		if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {//Puedes cambiar entre las 2 armas. Se tiene que descomentar la parte comentada para que funcione. 
			//No descomentar hasta que los 2 tipos de armas esten inplemtentados porque salta un null si intentas crear un arma de tipo rocket.
			if (cannonPlayer2.gun == 1) {
				//cannonPlayer2.gun = 2;
			}
			else if (cannonPlayer2.gun == 2) {
				cannonPlayer2.gun = 1;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
			//Dependiendo del tipo de arma que hayas elegido en el if de la linea 107 te crea un tipo u otro de proyectil
			switch (cannonPlayer2.gun)
			{
			case 1:
				CreateObject(50, 540, 5,40, Type::GRENADE);
				break;
			case 2:
				CreateObject(50, 540, 5,40, Type::ROCKET);
				break;
			}

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

	//object funtions
	ObjectUpdate();

	return UPDATE_CONTINUE;
}

 
update_status ModulePlayer::PostUpdate() {

	
	return UPDATE_CONTINUE;
}

ModulePlayer::Object* ModulePlayer::CreateObject(int x, int y, int r,int mass, Type type) {
	ObjectDef* b = App->physics->createCircle(x, y, r);
	b->mass = mass;
	App->physics->ball.add(b);
	Object* a = new Object(b, type);
	objects.add(a);
	return a;
}

void ModulePlayer::ObjectUpdate() {
	
	p2List_item<Object*>* currentObject = objects.getFirst();
	while (currentObject != NULL) {
		currentObject->data->lifeTime--;

		switch (currentObject->data->objectType) {
		case Type::GRENADE:
			
			//Explode Grenade
			if (currentObject->data->lifeTime <= 0) {
				SDL_Rect rect = { int(currentObject->data->object->x) - currentObject->data->explosionRadius,
								  int(currentObject->data->object->y) - currentObject->data->explosionRadius,
								  2 * currentObject->data->explosionRadius,
								  2 * currentObject->data->explosionRadius };

				App->renderer->DrawQuad( rect, 255, 150, 0, 255, false);

				p2List_item<ObjectDef*>* currentPlayer = App->physics->player.getFirst();
				while (currentPlayer != NULL) {
					if (App->physics->Collision_Rectangle_Detection(rect, f_Rect(currentPlayer->data->x, currentPlayer->data->y,
																				 currentPlayer->data->w, currentPlayer->data->h))) {
						//player hurt
						//App->renderer->DrawQuad(rect, 0, 250, 0, 255, false);
					}
					currentPlayer = currentPlayer->next;
				}
			}

			break;
		case Type::ROCKET:

			break;
		}

		if (currentObject->data->lifeTime <= 0) {
			Object* b = currentObject->data;
			currentObject = currentObject->next;
			objects.del(objects.findNode(b));
			App->physics->ball.del(App->physics->ball.findNode(b->object));
		}
		else {
			currentObject = currentObject->next;
		}
	}
}