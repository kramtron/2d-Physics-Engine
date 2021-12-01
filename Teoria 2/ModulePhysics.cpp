#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "ModulePlayer.h"

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}


ObjectDef::ObjectDef() {
}
ObjectDef::~ObjectDef() {
	
}


bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	//App->physics->enemic.add(App->physics->createStaticRectangle(500.0f, 600.0f, 20.0f, -100.0f));
	
	/*enemic.add(createStaticRectangle(700, 300, 40, 300));
	enemic.add(createStaticRectangle(580, 500, 40, 100));*/

	enemic.add(createStaticRectangle(700, 0, 40, 300));
	enemic.add(createStaticRectangle(580, 0, 40, 100));

	player.add(App->physics->createDinamicPlayer(300, 540, 30, 60,40));
	player.add(App->physics->createDinamicPlayer(800, 535, 30, 60,10));
	/*player.add(createStaticRectangle(300, 00, 30, 60));
	player.add(createStaticRectangle(800, 00, 30, 60));*/
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	
	
	if (ball.getFirst() != NULL) {

		p2List_item<ObjectDef*>* storage = ball.getFirst();

		while (storage != NULL) {
			p2List_item<ObjectDef*>* storage2 = enemic.getFirst();
			p2List_item<ObjectDef*>* storage3 = player.getFirst();

			if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
				storage->data->StopPhysics();
			}
			if (storage2 != NULL) {
				if (storage->data->physicObject == true) {
					storage->data->PhysicUpdate();
					while (storage2 != NULL) {
						Colliders(storage, storage3, 90);
						Colliders(storage, storage2, 90);
						storage2 = storage2->next;
					}
				}
				storage = storage->next;

			}
			else {

				if (storage->data->physicObject == true) {

					storage->data->PhysicUpdate();
					Colliders(storage, storage2, 90);

				}
				storage = storage->next;


				storage2 = storage2->next;
			}
		}
	}
	p2List_item<ObjectDef*>* storage4 = player.getFirst();
	while (storage4 != NULL) {
		p2List_item<ObjectDef*>* storage2 = enemic.getFirst();
		if (storage4->data->physicObject) {

			storage4->data->PhysicUpdate();
		}
		while (storage2 != NULL) {


				Colliders(storage4, storage2, 90);

			
			storage2 = storage2->next;
		}
		storage4 = storage4->next;
	}

	//LOG("Numeros de objetos en la lista : %d", ball.count());

	return UPDATE_CONTINUE;
}
 

ObjectDef* ModulePhysics::createCircle(int x, int y, int r) {

	ObjectDef* pobject = new ObjectDef();

	pobject->x = x;
	pobject->y = y;
	pobject->r = r;

	pobject->physicObject = true;

	pobject->circle = true;

	return pobject;

}

ObjectDef* ModulePhysics::createStaticRectangle(float x, float y, float w,float h) {

	ObjectDef* pobject = new ObjectDef();

	pobject->x = x;
	pobject->y = y;
	pobject->w = w;
	pobject->h = h;

	pobject->physicObject = false;
	
	pobject->rectangle = true;
	 
	return pobject;

}
ObjectDef* ModulePhysics::createDinamicPlayer(float x, float y, float w, float h, float mass) {
	ObjectDef* pobject = new ObjectDef();

	pobject->x = x;
	pobject->y = y;
	pobject->w = w;
	pobject->h = h;

	pobject->mass = mass;

	pobject->physicObject = true;

	pobject->rectangle = true;

	pobject->player = true;

	return pobject;
}
update_status ModulePhysics::PostUpdate()
{
	//Codigo que borra una bola cunaod toca a un enemigo. No funciona por el momento
	if (App->player->playerNum == 1) {
		p2List_item<ObjectDef*>* bala = ball.getFirst();
		p2List_item<ObjectDef*>* object2 = player.getLast();
		bool exit = false;
		while (bala != NULL && !exit) {
			
				if (((bala->data->x + bala->data->r) > object2->data->x && bala->data->x < (object2->data->x + object2->data->w))
					&& (bala->data->y > object2->data->y && bala->data->y < (object2->data->y + object2->data->h))) {

					ObjectDef* b = bala->data;
					ball.del(ball.findNode(b));
					delete b;
					exit=true;

				}
				else {
					bala = bala->next;

				}
		}
	}
	if (App->player->playerNum == 2) {
		p2List_item<ObjectDef*>* bala = ball.getFirst();
		p2List_item<ObjectDef*>* object2 = player.getFirst();
		bool exit = false;
		while (bala != NULL && !exit) {

			if (((bala->data->x - bala->data->r) > object2->data->x && (bala->data->x-bala->data->r) < (object2->data->x + object2->data->w))
				&& (bala->data->y > object2->data->y && bala->data->y < (object2->data->y + object2->data->h))) {

				ObjectDef* b = bala->data;
				ball.del(ball.findNode(b));
				delete b;
				exit = true;

			}
			else {
				bala = bala->next;

			}
		}
	}

		

	

		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
			debug = !debug;

		if (!debug)
			return UPDATE_CONTINUE;


		if (ball.getFirst() != NULL) {

			p2List_item<ObjectDef*>* storage = ball.getFirst();

			while (storage != NULL) {

				if (storage->data->circle) {

					App->renderer->DrawCircle(storage->data->x, storage->data->y, storage->data->r, 200, 200, 10);

				}

				storage = storage->next;
			}
		}
	
	
	if (enemic.getFirst() != NULL) {

		p2List_item<ObjectDef*>* storageEnemics = enemic.getFirst();

		while (storageEnemics != NULL) {

			if (storageEnemics->data->rectangle) {
				SDL_Rect rect = { storageEnemics->data->x,storageEnemics->data->y,storageEnemics->data->w,storageEnemics->data->h };
				App->renderer->DrawQuad(rect, 250, 250, 0);
			}

			storageEnemics = storageEnemics->next;
		}
	}
		

	p2List_item<ObjectDef*>* playerListItem = player.getFirst();
	while (playerListItem != NULL) {
		SDL_Rect rect = { playerListItem->data->x,playerListItem->data->y,playerListItem->data->w,playerListItem->data->h };
		App->renderer->DrawQuad(rect, 250, 250, 40);
		playerListItem = playerListItem->next;
	}
			
		
	
	
			

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!

	return true;
}

//Modulo fuerza gravedad personaje



float ObjectDef::angleToRadiants(int angle) {

	float radiants;

	radiants = angle * M_PI / 180;
	return radiants;
}

void ObjectDef::SetPlayerPosition(int x, int y) {
	this->x = x;
	this->y = y;
}
void ObjectDef::SetPlayerMass(int mass) {
	this->mass = mass;
}

int ObjectDef::GetPlayerMass() {
	return mass;
}


void ObjectDef::Gravity() {

	//Gravedad basica
	
	fgx = mass * 0.0f;
	fgy = mass * gravity;
	

};


void ObjectDef::Force() {

	
	fx += fgx;
	fy += fgy;


};


void ObjectDef::Velocity() {

	

}


void ObjectDef::Acceleration() {

	ax = fx / mass;
	ay = fy / mass;

}


void ObjectDef::SetVelocity(int x, int y) {

	vx = x;
	vy = y;

}


void ObjectDef::SetAcceleration(int x, int y) {
	ax = x;
	ay = y;

}


void ObjectDef::SetForce(int x, int y) {
	
	fx = x;
	fy = y;
	//LOG("Aditional force %f",fy);
};








void ObjectDef::Integrator_Verlet() {


	x += (vx * DELTA_TIME) + (0.5f * ax) * (DELTA_TIME) * (DELTA_TIME);
	y += (vy * DELTA_TIME) + (0.5f * ay) * (DELTA_TIME) * (DELTA_TIME);
	vx += (ax * DELTA_TIME);
	vy += (ay * DELTA_TIME);
	//LOG("Delta Time :%f", DELTA_TIME);
}
/*ObjectDef* ModulePhysics::OnCollisions(p2List<ObjectDef*> Object1, p2List<ObjectDef*> object2) {
	
	p2List_item<ObjectDef*>* Storage1 = Object1.getFirst();
	while (Storage1 != NULL) {
		p2List_item<ObjectDef*>* Storage2 = object2.getFirst();
		while (Storage2!=NULL) {
			Colliders(Storage1, Storage2, 90);
			Storage2 = Storage2->next;
		}
		Storage1 = Storage1->next;
	}
	
	ObjectDef* def = nullptr;
	return def;

}*/
ObjectDef* ModulePhysics::Colliders(p2List_item<ObjectDef*>* bala, p2List_item<ObjectDef*>* object2,int a) {
	//Mira si el primer objeto es un player
		if (bala->data->player) {
			//bala->data->cr = 0,6;
			//Mira si colisiona con el suelo. Mas adelante se tiene que hacer que el suelo sea parte de object2
			if (bala->data->y + bala->data->h > App->player->floor.y) {
				bala->data->y += App->player->floor.y - (bala->data->y + bala->data->h);
				bala->data->vy = (- bala->data->vy * bala->data->cr)/bala->data->mass;
				bala->data->vx = bala->data->vx * bala->data->cf;

			}
			//Mira si está colidiendo con algun objeto del mapa
			if ((bala->data->x > object2->data->x && bala->data->x < (object2->data->x + object2->data->w))
				&& (bala->data->y > object2->data->y && bala->data->y < (object2->data->y + object2->data->h))
				|| ((bala->data->x + bala->data->w) > object2->data->x && (bala->data->x + bala->data->w) < (object2->data->x + object2->data->w))
				&& (bala->data->y > object2->data->y && bala->data->y < (object2->data->y + object2->data->h))) {

				//Colision por el Lado izquierdo
				if ((bala->data->x + bala->data->w) - (object2->data->w / 2) < (object2->data->x) /* && bala->data->y < (object2->data->y + object2->data->h) && bala->data->y > object2->data->y */) {


					bala->data->x += object2->data->x - (bala->data->x + bala->data->w);

					bala->data->vy = -bala->data->vy * bala->data->cr;
					bala->data->vx = -bala->data->vx * bala->data->cf;

					bala->data->vx = ((cos(a * M_PI / 180) * -(bala->data->vx)) + (-sin(a * M_PI / 180) * bala->data->vy));
					bala->data->vy = (sin(a * M_PI / 180) * -bala->data->vx) + (cos(a * M_PI / 180) * bala->data->vy);
				}
				//Colision por el Lado derecho
				if (bala->data->x + (object2->data->w / 2) > (object2->data->x + object2->data->w) /* && (object2->data->y + object2->data->h) < object2->data->h && bala->data->y > object2->data->y*/) {

					bala->data->x -= bala->data->x - (object2->data->x + object2->data->w);

					bala->data->vy = -bala->data->vy * bala->data->cr;
					bala->data->vx = bala->data->vx * bala->data->cf;

					bala->data->vx = (cos(a * M_PI / 180) * bala->data->vx) + (-sin(a * M_PI / 180) * bala->data->vy);
					bala->data->vy = (sin(a * M_PI / 180) * bala->data->vx) + (cos(a * M_PI / 180) * bala->data->vy);
				}

			}
		}
		else {


			if (bala->data->y > App->player->floor.y) {
				bala->data->y += App->player->floor.y - bala->data->y;
				bala->data->vy = -bala->data->vy * bala->data->cr;
				bala->data->vx = bala->data->vx * bala->data->cf;
			}
			if ((bala->data->x > object2->data->x && bala->data->x < (object2->data->x + object2->data->w))
				&& (bala->data->y > object2->data->y && bala->data->y < (object2->data->y + object2->data->h))) {

				
				if (bala->data->x - (object2->data->w / 2) < (object2->data->x) /* && bala->data->y < (object2->data->y + object2->data->h) && bala->data->y > object2->data->y */) {


					bala->data->x += object2->data->x - (bala->data->x);

					bala->data->vy = -bala->data->vy * bala->data->cr;
					bala->data->vx = -bala->data->vx * bala->data->cf;

					bala->data->vx = ((cos(a * M_PI / 180) * -(bala->data->vx)) + (-sin(a * M_PI / 180) * bala->data->vy));
					bala->data->vy = (sin(a * M_PI / 180) * -bala->data->vx) + (cos(a * M_PI / 180) * bala->data->vy);
				}

				if (bala->data->x + (object2->data->w / 2) > (object2->data->x + object2->data->w) /* && (object2->data->y + object2->data->h) < object2->data->h && bala->data->y > object2->data->y*/) {

					bala->data->x -= bala->data->x - (object2->data->x + object2->data->w);

					bala->data->vy = -bala->data->vy * bala->data->cr;
					bala->data->vx = bala->data->vx * bala->data->cf;

					bala->data->vx = (cos(a * M_PI / 180) * bala->data->vx) + (-sin(a * M_PI / 180) * bala->data->vy);
					bala->data->vy = (sin(a * M_PI / 180) * bala->data->vx) + (cos(a * M_PI / 180) * bala->data->vy);
				}

			}
		}
		/*if (bala->data->y > (object2->data->y + (object2->data->h - 10)) && bala->data->y<(object2->data->y + object2->data->h) && bala->data->x >object2->data->x && bala->data->x<object2->data->x + object2->data->w) {
			bala->data->y += object2->data->y - bala->data->y;
			bala->data->vy = -bala->data->vy * bala->data->cr;
			bala->data->vx = bala->data->vx * bala->data->cf;
		}*/

	
	ObjectDef* def=nullptr;
	return def;
}

void ObjectDef::StopPhysics() {
	if (physEnable) {
		physEnable = false;
	}
	else if (!physEnable){
		physEnable = true;
	}

}

void ObjectDef::PhysicUpdate() {
	
	if (physEnable) {
		fx = fy = 0.0f;
		ax = ay = 0.0f;


		Gravity();
		Force();
		Velocity();
		Acceleration();
		Integrator_Verlet();
	}
}