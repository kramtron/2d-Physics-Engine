#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include <string>

using namespace std;

#define max_Objects 20

struct Object
{
	SDL_Texture* graphic;
	PhysBody* body;
	uint fx;

	Object() : graphic(NULL), body(NULL)
	{}
};


class ModulePlayer : public Module
{
public:
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



