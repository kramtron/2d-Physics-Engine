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

		//Modifica la velocidad normal del disparo de ca�on
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
			/*App->physics->player.getFirst()->data->SetForce(-10, 0);
			App->physics->player.getFirst()->data->SetForce(-100000, 0);*/
			App->physics->player.getFirst()->data->x -= 3;


		}
		if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {//Puedes cambiar entre las 2 armas. 
			if (cannonPlayer1.gun == 1) {
				cannonPlayer1.gun = 2;
			}
			else if (cannonPlayer1.gun == 2) {
				cannonPlayer1.gun = 1;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
			//Dependiendo del tipo de arma que hayas elegido en el if de la linea 107 te crea un tipo u otro de proyectil
			switch (cannonPlayer1.gun)
			{
			case 1:
				CreateObject((App->physics->player.getFirst()->data->x + App->physics->player.getFirst()->data->w + 10), 
							  App->physics->player.getFirst()->data->y, 5,40, Type::GRENADE);
				break;
			case 2:
				CreateObject((App->physics->player.getFirst()->data->x + App->physics->player.getFirst()->data->w + 10),
							  App->physics->player.getFirst()->data->y, 5,40, Type::ROCKET);
				break;
			}
			//App->physics->ball.add(App->physics->createCircle(50, 540, 5));

			App->physics->ball.getLast()->data->SetVelocity(cannonPlayer1.velocity * cos(-radiants),
				cannonPlayer1.velocity * sin(-radiants));
			playerNum = 3;

		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			//App->physics->player.getFirst()->data->SetForce(0, 100);
			App->physics->player.getFirst()->data->SetVelocity(0,-500);
		}
	}
	//Segundo jugador
	if (playerNum == 2) {

		//Modifica la velocidad normal del disparo de ca�on
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
		if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {//Puedes cambiar entre las 2 armas. 
			if (cannonPlayer2.gun == 1) {
				cannonPlayer2.gun = 2;
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
				CreateObject(App->physics->player.getLast()->data->x, App->physics->player.getLast()->data->y, 5,40, Type::GRENADE);
				break;
			case 2:
				CreateObject(App->physics->player.getLast()->data->x, App->physics->player.getLast()->data->y, 5,40, Type::ROCKET);
				break;
			}

			App->physics->ball.getLast()->data->SetVelocity(-(cannonPlayer2.velocity * cos(-radiants)),
				(cannonPlayer2.velocity * sin(-radiants)));
			playerNum = 4;


		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			//App->physics->player.getLast()->data->SetForce(0, 100);
			App->physics->player.getLast()->data->SetVelocity(0, -500);
		}
	}
	
	if (playerNum == 3) {
		gameStoped++;
		if (gameStoped == 200) {
			playerNum = 2;
			gameStoped = 0;
		}
	}
	if (playerNum == 4) {
		gameStoped++;
		if (gameStoped == 200) {
			playerNum = 1;
			gameStoped = 0;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
		//App->physics->enemic.add(App->physics->createStaticRectangle(500, 600, 20, -100));
	}
	//LOG("Radiants %f: ", radiants);

	//object funtions
	ObjectUpdate();
	if (end) {
		return UPDATE_STOP;
	}
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
						currentPlayer->data->hp -= currentObject->data->damage;
						if (currentPlayer->data->hp <= 0) {
							ObjectDef* b = currentPlayer->data;
							currentPlayer = currentPlayer->next;
							App->physics->player.del(App->physics->player.findNode(b));
							App->physics->ball.del(App->physics->ball.findNode(b));
							end = true;
						}
						else {
							currentPlayer = currentPlayer->next;
						}
						App->renderer->DrawQuad(rect, 250, 100, 0, 255, false);
					}
					else {
						currentPlayer = currentPlayer->next;
					}
				}
			}

			break;
		case Type::ROCKET:

			if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
				currentObject->data->object->force = true;
			}

			if (currentObject->data->object->colliding) {
				currentObject->data->lifeTime = 0;
			}

			if (currentObject->data->lifeTime <= 0) {
				SDL_Rect rect = { int(currentObject->data->object->x) - currentObject->data->explosionRadius,
								  int(currentObject->data->object->y) - currentObject->data->explosionRadius,
								  2 * currentObject->data->explosionRadius,
								  2 * currentObject->data->explosionRadius };
				
				p2List_item<ObjectDef*>* currentPlayer = App->physics->player.getFirst();
				while (currentPlayer != NULL) {
					if (App->physics->Collision_Rectangle_Detection(rect, f_Rect(currentPlayer->data->x, currentPlayer->data->y,
						currentPlayer->data->w, currentPlayer->data->h))) {
						//player hurt
						currentPlayer->data->hp -= currentObject->data->damage;
						if (currentPlayer->data->hp <= 0) {
							ObjectDef* b = currentPlayer->data;
							currentPlayer = currentPlayer->next;
							App->physics->player.del(App->physics->player.findNode(b));
							App->physics->ball.del(App->physics->ball.findNode(b));
							end = true;
						}
						else {
							currentPlayer = currentPlayer->next;
						}
						App->renderer->DrawQuad(rect, 0, 250, 0, 255, false);


					}
					else {
						currentPlayer = currentPlayer->next;
					}
				}
				App->renderer->DrawQuad(rect, 0, 250, 0, 255, false);
			}
			
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