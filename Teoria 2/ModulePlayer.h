#pragma once
#include "Module.h"
#include "Application.h"
#include "Animation.h"
#include "ModulePhysics.h"
#include "Globals.h"
#include <string>

using namespace std;

class ModulePlayer : public Module
{
public:

	enum class Type { GRENADE, ROCKET }objectType;

	class Object {
	public:
		ObjectDef* object = nullptr;
		Type objectType;
		int lifeTime = 0;
		SDL_Rect sprite;

	public:
		Object(ObjectDef* object, Type objectType){
			this->object = object;
			this->objectType = objectType;
			
			switch(objectType){
			case Type::GRENADE:
				this->sprite = {0, 0, 0, 0};
				this->lifeTime = 300;
				break;
			case Type::ROCKET:
				this->sprite = { 0, 0, 0, 0 };
				this->lifeTime = 1000;
				break;
			}
		}
	};
	p2List<Object*> objects;

	Object* CreateObject(int x, int y, int r, Type type);
	void ObjectUpdate();

	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	int angleCont = 0;
	int normalVelocityCont = 5;
	
	struct Cannon {
		int velocity=500;
		int angle=0;
	};
	Cannon cannonPlayer1;
	Cannon cannonPlayer2;
	float radiants;
	
	int playerNum = 1;// Num 1 player 1, num 2 player 2
public:

	SDL_Rect playerRect;
	SDL_Rect floor;
	
	
};



