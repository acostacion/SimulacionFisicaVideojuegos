#pragma once
#include <random>
#include <foundation/PxVec3.h>

// Clase padre ABSTRACTA para los Particle Generators hijos:
// - Gaussian Generator.
// -
class ParticleGen{
public:
	virtual void generateP() = 0;

	// getters
	physx::PxVec3 getPos() { return _pos; }
	physx::PxVec3 getVel() { return _vel; }
	physx::PxVec3 getDir() { return _dir; }
	//int getProbGen() { return _probGen; }

	// setters
	void setPos(physx::PxVec3 p) { _pos = p; }
	void setVel(physx::PxVec3 v) { _vel = v; }
	void setDir(physx::PxVec3 d) { _dir = d; }
	//void setProbGen(int pg) { _probGen = pg; }

private:
	physx::PxVec3 _pos;
	physx::PxVec3 _vel;
	physx::PxVec3 _dir;
	int _probGen; // todo no se si es int.

	// todo no se si esto es publico o privado.
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0,1 };
};

