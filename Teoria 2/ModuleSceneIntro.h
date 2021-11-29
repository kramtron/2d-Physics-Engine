#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

#define BOUNCER_TIME 200

struct Bouncer
{
	Bouncer() : body(NULL), texture(NULL), hit_timer(0), fx(0)
	{}

	PhysBody* body;
	SDL_Texture* texture;
	Uint32 hit_timer;
	uint fx;
};

enum lightTypes
{
	tiny,
	medium,
	big
};

class ModuleSceneIntro;

struct Light
{
	Light() : body(NULL), texture(NULL), on(false), fx(0)
	{}

	Light(ModuleSceneIntro* physics, int x, int y, lightTypes type);

	lightTypes type;
	PhysBody* body;
	SDL_Texture* texture;
	bool on;
	uint fx;
	int x, y;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	update_status PostUpdate();

	bool CleanUp();

public:
	SDL_Rect rect01;
	SDL_Rect rect02;
	SDL_Rect rect03;
	SDL_Rect rect04;
	SDL_Rect rect05;
	SDL_Rect rect06;
	SDL_Rect rect07;
	SDL_Rect rect08;
	SDL_Rect rect09;



	SDL_Rect planta;
	int plantaX = 800, plantaY=600;
	int contVibrPlanta = 0;
	bool VibracionPlanta = false;
	bool VibracionPlantaFast = true;
	int randNumMove = 0;

	SDL_Texture* graphics;
	PhysBody* background;

	Bouncer bouncer1;
	Bouncer bouncer2;

	Bouncer side_bouncer1;
	Bouncer side_bouncer2;

	SDL_Texture* tex_light_tiny;
	SDL_Texture* tex_light_medium;
	SDL_Texture* tex_light_big;
	
	uint fx_light_tiny;
	uint fx_light_medium;
	uint fx_light_big;

	p2DynArray<Light> lights;

	PhysBody* player_lose;
	uint player_lose_fx;
};
