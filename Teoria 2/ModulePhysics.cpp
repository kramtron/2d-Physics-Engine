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

	//enemic.add(createStaticRectangle(700, 0, 40, 300));
	//enemic.add(createStaticRectangle(580, 0, 40, 100));

	player.add(App->physics->createDinamicPlayer(300, 440, 30, 60,40,20));
	player.add(App->physics->createDinamicPlayer(800, 440, 30, 60,10,20));
	/*player.add(createStaticRectangle(300, 00, 30, 60));
	player.add(createStaticRectangle(800, 00, 30, 60));*/
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	//Ball Physics
	p2List_item<ObjectDef*>* current_ball = ball.getFirst();
	while (current_ball != NULL) {
		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
			current_ball->data->StopPhysics();
		}
		if (current_ball->data->physEnable) {
			current_ball->data->PhysicUpdate();
			App->physics->CollisionSolver(current_ball->data);
		}

		

		current_ball = current_ball->next;
	}

	//Player Physics
	p2List_item<ObjectDef*>* current_player = player.getFirst();
	while (current_player != NULL) {
		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
			current_player->data->StopPhysics();
		}
		if (current_player->data->physEnable) {
			current_player->data->PhysicUpdate();
			App->physics->CollisionSolver(current_player->data);
		}
		current_player = current_player->next;
	}


	return UPDATE_CONTINUE;
}
 

ObjectDef* ModulePhysics::createCircle(int x, int y, int r) {

	ObjectDef* pobject = new ObjectDef();

	pobject->app = App;

	pobject->x = x;
	pobject->y = y;
	pobject->r = r;

	pobject->physicObject = true;

	pobject->circle = true;

	return pobject;

}

ObjectDef* ModulePhysics::createStaticRectangle(float x, float y, float w,float h,float water) {

	ObjectDef* pobject = new ObjectDef();

	pobject->app = App;

	pobject->x = x;
	pobject->y = y;
	pobject->w = w;
	pobject->h = h;

	pobject->physicObject = false;
	
	pobject->rectangle = true;
	 
	if (water == 1) {
		pobject->water = true;
	}

	return pobject;

}

ObjectDef* ModulePhysics::createDinamicPlayer(float x, float y, float w, float h, float mass,float hp) {
	ObjectDef* pobject = new ObjectDef();

	pobject->app = App;

	pobject->x = x;
	pobject->y = y;
	pobject->w = w;
	pobject->h = h;

	pobject->mass = mass;

	pobject->cr = 0;

	pobject->physicObject = true;

	pobject->rectangle = true;

	pobject->player = true;

	pobject->hp = 50;

	return pobject;
}
update_status ModulePhysics::PostUpdate()
{
	//Codigo que borra una bola cunaod toca a un enemigo. No funciona por el momento
	/*if (App->player->playerNum == 1) {
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
	}*/

		

	

		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
			debug = !debug;

		if (!debug)
			return UPDATE_CONTINUE;


		SDL_Rect rect = { App->scene_intro->aigua->x , App->scene_intro->aigua->y , App->scene_intro->aigua->w , App->scene_intro->aigua->h };
		App->renderer->DrawQuad(rect, 0, 0, 250);

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
			
		
	if ((App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) && deltaTime == 0.0167f)
	{
		deltaTime = 0.0333f;
	}
	else
	{
		deltaTime = 0.0167f;
	}

	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		if (integrator == Integrator_Type::EULER_FORW)
			integrator = Integrator_Type::VERLET;

		else if (integrator == Integrator_Type::VERLET)
			integrator = Integrator_Type::EULER_BACK;

		else if (integrator == Integrator_Type::EULER_BACK)
			integrator = Integrator_Type::EULER_FORW;
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
	
	fgx = mass * app->physics->gravity_X;
	fgy = mass * app->physics->gravity_Y;
	

};


void ObjectDef::Drag() {

	//vel relativa del obj
	v_relativa_x = app->physics->wind_X - vx;
	v_relativa_y = app->physics->wind_Y - vy;

	//modul del vector v_relativa
	float v_relativa = sqrt((v_relativa_x * v_relativa_x) + (v_relativa_y * v_relativa_y));
		
	//drag a l'aigua
	float f_Drag = 0;
	if (fb == 0) {
		f_Drag = 0.5 * densitat * v_relativa * superficie_Drag * cd * 500;	//500 air drag coeficient
	}
	else {	//in water
		float v = sqrt((vx * vx) + (vy * vy));
		if (player) {
			f_Drag = 6.0f * 3.14f * ((w + h) / 4) * v; //radi = mitjana entre (w i h) / 2;
		}
		else {
			f_Drag = 6.0f * 3.14f * r * v;
		}
	}

	//modul de la força de drag
	//vector unitari de les velocitats relatives
	v_relativa_x = v_relativa_x / v_relativa;
	v_relativa_y = v_relativa_y / v_relativa;

	//f_drag separada
	f_Drag_x = f_Drag * v_relativa_x;
	f_Drag_y = f_Drag * v_relativa_y;
	

	LOG("Drag: %f", f_Drag);

}

int ObjectDef::Volume() {
	int vol = 0;
	if (player) {
		if (y > app->scene_intro->aigua->y) {
			vol = w * h;
		}
		else {
			vol = (y + h - app->scene_intro->aigua->y) * w;
		}
	}
	else {
		if ((y - r) > app->scene_intro->aigua->y) {
			vol = 4 * r * r;
		}
		else {
			vol = (y + r - app->scene_intro->aigua->y) * (r + r);
		}
	}
	

	return vol;
}

void ObjectDef::Buoyancy() {
	bool inwater = false;
	if (player) {
		inwater = app->physics->Collision_Rectangle_Detection(f_Rect(x, y, w, h),
			f_Rect(app->scene_intro->aigua->x, app->scene_intro->aigua->y, app->scene_intro->aigua->w, app->scene_intro->aigua->h));
	}
	else {
		inwater = app->physics->Collision_Rectangle_Detection(f_Rect(x, y, r, r),
			f_Rect(app->scene_intro->aigua->x, app->scene_intro->aigua->y, app->scene_intro->aigua->w, app->scene_intro->aigua->h));
	}

	if (inwater) {
		volume = Volume();

		fb = -f_density * volume * app->physics->gravity_Y;
		LOG("volume = %.2f", volume);
	}
	else
		fb = 0;
}

void ObjectDef::Force() {

	fx += fgx + f_Drag_x;
	fy += fgy + f_Drag_y + fb;
	
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


void ObjectDef::Integrator_Euler_Forward() {
	
	vx += (ax * (app->physics->deltaTime));
	vy += (ay * (app->physics->deltaTime));
	x += (vx * (app->physics->deltaTime));
	y += (vy * (app->physics->deltaTime));

}


void ObjectDef::Integrator_Euler_Backward() {
	
	x += (vx * (app->physics->deltaTime));
	y += (vy * (app->physics->deltaTime));
	vx += (ax * (app->physics->deltaTime));
	vy += (ay * (app->physics->deltaTime));

}


void ObjectDef::Integrator_Verlet() {

	x += (vx * app->physics->deltaTime) + (0.5f * ax) * (app->physics->deltaTime) * (app->physics->deltaTime);
	y += (vy * app->physics->deltaTime) + (0.5f * ay) * (app->physics->deltaTime) * (app->physics->deltaTime);
	vx += (ax * app->physics->deltaTime);
	vy += (ay * app->physics->deltaTime);
	//LOG("Delta Time :%f", app->physics->deltaTime);
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
	fx = fy = 0.0f;
	ax = ay = 0.0f;
	fb = 0.0f;
	f_Drag_x = f_Drag_y = 0.0f;
	colliding = false;

	if (force)
	{
		fy = 1000000;
		force = false;
	}

	//LOG("Force %.2f", fy);
	Gravity();
	Buoyancy();
	Drag();	//es calcula la ultima abans de fer el sumatori de forces
	Force();
	Acceleration();

	switch (app->physics->integrator) {
	case ModulePhysics::Integrator_Type::VERLET:
		Integrator_Verlet();
		break;
	case ModulePhysics::Integrator_Type::EULER_FORW:
		Integrator_Euler_Forward();
		break;
	case ModulePhysics::Integrator_Type::EULER_BACK:
		Integrator_Euler_Backward();
		break;
	}

	//LOG("Fy= %f", fy);
	
}

void ModulePhysics::CollisionSolver(ObjectDef* b) {
	if (b->player) {	//player
		p2List_item<ObjectDef*>* current_enemy = enemic.getFirst();
		while (current_enemy != NULL) {
			Collision_PlayerEnemy(b, current_enemy->data);
			current_enemy = current_enemy->next;
		}
	}
	else {			//ball
		p2List_item<ObjectDef*>* current_enemy = enemic.getFirst();
		while (current_enemy != NULL) {
			Collision_BallEnemy(b, current_enemy->data);
			current_enemy = current_enemy->next;
		}
		p2List_item<ObjectDef*>* current_player = player.getFirst();
		while (current_player != NULL) {
			Collision_BallEnemy(b, current_player->data);
			current_player = current_player->next;
		}
		/*p2List_item<ObjectDef*>* current_ball = ball.getFirst();
		while (current_ball != NULL) {
			if (current_ball->data != b)
				Collision_BallBall(b, current_ball->data);
			current_ball = current_ball->next;
		}*/
	}
}

void ModulePhysics::Collision_BallBall(ObjectDef* b, ObjectDef* b2) {	//ball against ball

}

void ModulePhysics::Collision_BallEnemy(ObjectDef* b, ObjectDef* e) {	//ball against collider(collider sent)
	if (Collision_Rectangle_Detection(f_Rect(b->x, b->y, b->r, b->r), f_Rect(e->x, e->y, e->w, e->h))) {
		if (Collision_Rectangle_Detection(f_Rect(b->x, b->y - (b->vy * deltaTime), b->r, b->r), f_Rect(e->x, e->y, e->w, e->h))) {
			if (b->vx > 0) { //Right colision
				b->x -= 2 * (b->x - (e->x - b->r));
			}
			else { //Left colision
				b->x += 2 * (-b->x + (e->x + e->w + b->r));
			}
			b->vy = b->vy * b->cr;
			b->vx = -b->vx * b->cr;
		}
		else if (Collision_Rectangle_Detection(f_Rect(b->x - (b->vx * deltaTime), b->y, b->r, b->r), f_Rect(e->x, e->y, e->w, e->h))) {
			if (b->vy > 0) { //Floor colision
				b->y -= 2 * (b->y - (e->y - b->r));
			}
			else { //Ceiling colision
				b->y += 2 * (-b->y + (e->y + e->h + b->r));
			}
			b->vy = -b->vy * b->cr;
			b->vx = b->vx * b->cr;
		}
		b->colliding = true;
	}
}

void ModulePhysics::Collision_PlayerEnemy(ObjectDef* p, ObjectDef* e) {	//ball against collider(collider sent)
	if (Collision_Rectangle_Detection(f_Rect(p->x, p->y, p->w, p->h), f_Rect(e->x, e->y, e->w, e->h))) {
		if (Collision_Rectangle_Detection(f_Rect(p->x, p->y - (p->vy * deltaTime), p->w, p->h), f_Rect(e->x, e->y, e->w, e->h))) {
			if (p->vx > 0) { //Right colision
				p->x = (e->x - p->w);
			}
			else { //Left colision
				p->x = (e->x + e->w);
			}
			p->vy = p->vy * p->cr;
			p->vx = -p->vx * p->cr;
		}
		else if (Collision_Rectangle_Detection(f_Rect(p->x - (p->vx * deltaTime), p->y, p->w, p->h), f_Rect(e->x, e->y, e->w, e->h))) {
			if (p->vy > 0) { //Floor colision
				p->y = (e->y - p->h);
			}
			else { //Ceiling colision
				p->y = (e->y + e->h);
			}
			p->vy = -p->vy * p->cr;
			p->vx = p->vx * p->cr;
		}
		/*else {
			if (p->vy >= 0) { //floor colision
				p->y = e->y - p->h;
			}
			else {	//ceiling colision
				p->y = e->y + e->h + p->h;
			}

			p->vy = -p->vy * p->cr;
			p->vx = -p->vx * p->cr;
		}*/
	}
}

bool ModulePhysics::Collision_Rectangle_Detection(f_Rect r1, f_Rect r2) {
	return (((r1.x + r1.w) > r2.x) && (r1.x < (r2.x + r2.w)) && ((r1.y + r1.h) > r2.y) && (r1.y < (r2.y + r2.h)));
}

bool ModulePhysics::Collision_Rectangle_Detection(SDL_Rect r1, f_Rect r2) {
	return (((r1.x + r1.w) > r2.x) && (r1.x < (r2.x + r2.w)) && ((r1.y + r1.h) > r2.y) && (r1.y < (r2.y + r2.h)));
}
