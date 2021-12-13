#pragma once
#include "Module.h"
#include "Globals.h"

struct f_Rect {
	float x = 0.0f, y = 0.0f, w = 0.0f, h = 0.0f;
	f_Rect(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

class ObjectDef {
public:

	//std::string ObjectType;

	float r = 0;//radio de circulos

	float x = 0, y = 0;//Possition

	float w = 0, h = 0;

	float mass = 0;//Mass

	float vx = 0, vy = 0;//Velocity

	float ax = 0, ay = 0;//Acceleration

	float fx = 0, fy = 0;//Force

	float fgx = 0, fgy = 0;

	float v_vent = 10;

	float f_Drag = 0, densitat = 1, v_relativa_x = 0, superficie_Drag = 0.3f, cd = 0.2f;

	//fb = f_density * volume * 9.81
	//density of water = 1g/cm^3 = 1000kg/m^3
	//volume = volumen sumergido del objeto
	float fb = 0, f_density = 0, volume = 0;

	//Aerodynamics stuff
	//int surface;//Effective wet surface
	//int cl;//Lift coeficient
	//int cd;//Drag Coeficient

	float cr = 0.6f;//Coeficiente de restitucion
	float cf = 0.8f;//Coeficiente de friccon

	bool physicObject = false;
	bool physEnable = true;

	bool circle = false;
	bool rectangle = false;
	bool player = false;
public:
	
	ObjectDef();
	~ObjectDef();

	float angleToRadiants(int angle);

	//Modifica la posición del objeto
	void SetPlayerPosition(int x, int y);

	//Modifica la masa del objeto
	void SetPlayerMass(int mass);

	//Modifica la velocidad del objeto
	void SetVelocity(int x, int y);

	//Modifica la acceleracion del objeto
	void SetAcceleration(int x, int y);

	//Modifica la fuerza dada al objeto
	void SetForce(int x, int y);


	void StopPhysics();

	//Te devuelve la masa del objeto
	int GetPlayerMass();

	



	//Procesos internos motor
private:
	//Calcula la gravedad de los objetos No tocar
	void Gravity();

	//Calcula el Drag
	void Drag();

	//Calcula la velocidad de los objetos No tocar
	void Velocity();

	//Calcula la acceleracion de los objetos No tocar
	void Acceleration();

	//Calcula la fuerza de los objetos No tocar
	void Force();

	//Integrador por verlet
	void Integrator_Verlet();
public:
	//Funcion para calcular todas las fuerzas del objeto LLamar siempre que el objeto no sea estatico
	void PhysicUpdate();
};


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	//ObjectDef* createCircle(int x, int y, int r);//No fet
	ObjectDef* createCircle(int x, int y, int r);//Crea un circulo con fisicas
	ObjectDef* createStaticRectangle(float x, float y, float w, float h);//Crea un rectangulo sin fisicas
	ObjectDef* createDinamicPlayer(float x, float y, float w, float h, float mass);//Crea un rectangulo con fisicas
	ObjectDef* UpdatePhysics();//No fet
	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	bool physicSwitch = true;
	p2List<ObjectDef*>ball;
	p2List<ObjectDef*>enemic;
	p2List<ObjectDef*>player;
	//ObjectDef* object2;
	int obectNum = 2;
	enum class Type { circle, rectangle }circle = Type::circle, rectangle = Type::rectangle;

	float x = 0;

	//ObjectDef* OnCollisions(p2List<ObjectDef*>object1, p2List<ObjectDef*> object2);

	//Calcula los colliders de los objetos No tocar
	ObjectDef* Colliders(p2List_item<ObjectDef*>* object, p2List_item<ObjectDef*>* object2,int a);
	void CollisionSolver(ObjectDef* b);
	void Collision_BallBall(ObjectDef* b, ObjectDef* b2);
	void Collision_BallEnemy(ObjectDef* b, ObjectDef* e);
	void Collision_PlayerEnemy(ObjectDef* p, ObjectDef* e);
	bool Collision_Rectangle_Detection(f_Rect r1, f_Rect r2);

private:

	bool debug;
};