#pragma once
#include "Module.h"
#include "Globals.h"

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

	int nv = 0;//Velocidad normal

	int angle = 0;//Angulo de disparo de la pelota

	//Aerodynamics stuff
	int surface;//Effective wet surface
	int cl;//Lift coeficient
	int cd;//Drag Coeficient

	float cr = 0.6f;//Coeficiente de restitucion
	float cf = 0.8f;//Coeficiente de friccon

	bool physicObject = false;

	bool circle = false;
	bool rectangle = false;
	bool player = false;
public:
	
	ObjectDef();
	~ObjectDef();

	float angleToRadiants(int angle);

	void createStaticBody();//No fet

	void createCircle(int x, int y, int r);//No fet

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

	//Modifica la velocidad normal del objeto
	void SetNormalVelocity(int nv);

	//Modifica el angulo del objeto en caso de querer usarlo para tiros parabolicos
	void SetAngle(int angle);

	void StopPhysics();

	//Te devuelve la masa del objeto
	int GetPlayerMass();

	//Te devuelve la velocidad normal del objeto
	int GetNormalVelocity();

	//Te devuelve el angulo del objeto
	int GetAngle();



	//Procesos internos motor
private:
	//Calcula la gravedad de los objetos No tocar
	void Gravity();

	//Calcula la velocidad de los objetos No tocar
	void Velocity();

	//Calcula la acceleracion de los objetos No tocar
	void Acceleration();

	//Calcula la fuerza de los objetos No tocar
	void Force();

	

	bool physEnable=true;
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
private:

	bool debug;
};