#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>
#include <random>

// Clase padre ABSTRACTA para los Particle Generators hijos:
// - Gaussian Generator.
// -
class ParticleGen{
public:
	ParticleGen(physx::PxVec3 p, physx::PxVec3 v, physx::PxVec3 d) : _vel(v), _dir(d){ // TODO probGen
		_tf = new physx::PxTransform(p);
	}

	virtual ~ParticleGen() { delete _tf; }

	virtual void generateP(std::vector<Particle*>& particles) = 0;

	// getters
	physx::PxVec3 getPos() { return _tf->p; }
	physx::PxVec3 getVel() { return _vel; }
	physx::PxVec3 getDir() { return _dir; }
	//int getProbGen() { return _probGen; }

	// setters
	void setPos(physx::PxVec3 p) { _tf->p = p; }
	void setVel(physx::PxVec3 v) { _vel = v; }
	void setDir(physx::PxVec3 d) { _dir = d; }
	//void setProbGen(int pg) { _probGen = pg; }

protected:
	physx::PxTransform* _tf; // TRANSFORM, desde donde se emiten las particulas (POS).
	physx::PxVec3 _vel; // a que velocidad se emiten las particulas (TODO: no podria haber algunas con mayor velocidad que otras. Ej.: fuego).
	physx::PxVec3 _dir; // direccion en la que se emiten las particulas
	int _probGen; // todo no se si es int.

	// Numero de particulas que genera en cada llamada
	const int N_PARTICLES = 50;

	/* Se usa como el motor de numeros aleatorios para alimentar a las distribuciones.
	 * Su rango es [0, 2^32) */
	std::mt19937 _mt;

	/* _u genera numeros aleatorios uniformemente distribuidos entre 0 y 1,
	 * sirve para generar variaciones en las propiedades de las particulas (pos, vel, dir...) */
	std::uniform_real_distribution<double> _u{ 0,1 };
};

