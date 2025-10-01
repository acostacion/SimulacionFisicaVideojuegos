#include "Particle.h"

Particle::Particle(physx::PxVec3 pos, physx::PxVec3 vel, integrateMode i, double size, Vector4 color)
: _vel(vel), _i(i), _size(size)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(_size));
	_tf = new physx::PxTransform(physx::PxVec3(pos.x, pos.y, pos.z));
	_color = { color.x, color.y, color.z, color.w };

	_renderItem = new RenderItem(shape, _tf, _color);

	RegisterRenderItem(_renderItem);

	// si decidimos hacerlo con verlet, la primera vuelta al principio no se ha dado (Euler).
	if (i == VERLET) _firstVerlet = false;
}

Particle::~Particle() {
	DeregisterRenderItem(_renderItem);
}

void Particle::integrate(double t){
	switch (_i){
	case EULER:
		integrateEuler(t);
		break;
	case SEMIEULER:
		integrateSemiEuler(t);
		break;
	case VERLET:
		integrateVerlet(t);
		break;
	default:
		break;
	}

	// VEL_n+1 = VEL_n * d^t damping (va en los tres metodos)
	_vel = _vel * std::pow(_damping, t);
}

/*
Euler explicito:
Muy barato computacionalmente, pero inestable y con errores acumulativos grandes.
Pocas veces se usa directamente en motores modernos, mas como ejemplo educativo.
*/
void Particle::integrateEuler(double t){
	// POS_n+1 = POS_n + VEL_n * t
	_tf->p = _tf->p + _vel * t;

	// VEL_n+1 = VEL_n + a * t, a: acceleration
	_vel = _vel + _a * t;
}

/*
Euler semiexplicito:
Mucho mas estable y conserva mejor la energia en sistemas dinamicos.
Muy usado en videojuegos porque es rapido y suficientemente robusto.
*/
void Particle::integrateSemiEuler(double t){
	// VEL_n+1 = VEL_n + a * t, a: acceleration
	_vel = _vel + _a * t;

	// POS_n+1 = POS_n + VEL_n * t
	_tf->p = _tf->p + _vel * t;
}

/*
Verlet:
No usa velocidades explicitamente (estas se obtienen como diferencia de posiciones).
Muy estable, popular en simulaciones con particulas.
Se usa en motores como Box2D y en tecnicas de simulacion de telas y fluidos.
*/
void Particle::integrateVerlet(double t){
	physx::PxVec3 currentPos = _tf->p;
	physx::PxVec3 prevPos;
	if (!_firstVerlet){ // si no se ha dado la primera vuelta de verlet aun...
		prevPos = _tf->p; // cogemos la pos anterior en la primera vuelta.
		integrateEuler(t);
		_firstVerlet = true; // primera vuelta con euler completada, pasamos a verlet...
	}
	else{ // verlet normal
		// POS_n+1 = 2*POS_n - POS_i-1 + t^2 * a, a: acceleration
		_tf->p = _tf->p * 2 - prevPos + _a * t * t;
		prevPos = currentPos; // hace que la actual sea la previa para la proxima vuelta.
	}

}
