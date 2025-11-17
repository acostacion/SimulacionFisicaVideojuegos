#pragma once
#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator {
public:
	ExplosionForceGenerator(double k = 1.0, physx::PxVec3 center = physx::PxVec3(0.0), float radius = 50.0f, double t = 1.0);
	void explode(){
		_isExploding = true;
		_currentTime = 0.0; // reinicia el contador.
	}
protected:
	// TODO de todas las que he hecho esta es la unica que necesita tiempo, hacer clase abstracta para solo las de tiempo y t ahorras un parametro...
	void updateForce(Particle* p, double t) override;
private: // TODO seguir x aki
	// propiedades
	float _R;			    // radio de la explosion
	physx::PxVec3 _center;	// centro de la explosion
	double _K;			    // intensidad de la explosion
	double _t;				// constante de tiempo de la explosion.
	// a partir de 4t la explosion practicamente se ha desvanecido.

	bool _isExploding;
	double _currentTime;
	const int EXPLOSION_DURATION = 5000; // lo que dura la explosion.
};
