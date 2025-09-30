#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	enum integrateMode{
		EULER,
		SEMIEULER,
		VERLET
	};

	Particle(
		Vector3D pos, 
		Vector3D vel, 
		float size = 1.0f, 
		Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f }
	);

	~Particle();

	void integrate(double t, integrateMode i);
private:
	RenderItem* _renderItem;
	Vector3D _pos; // position
	Vector3D _vel; // velocity
	Vector3D _a;   // acceleration
	float _size;
	Vector4 _color;

	// metodos integrar
	void integrateEuler(double t);
	//void integrateSemiEuler(double t); TODO
	//void integrateVerlet(double t); TODO

	// TODO hacer getters y setters de las cosas


};

