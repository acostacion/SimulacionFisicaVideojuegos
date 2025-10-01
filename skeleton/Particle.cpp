#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, double size, Vector4 color)
: _pos(pos), _vel(vel), _size(size), _color(color)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(_size));
	const physx::PxTransform* tf = new physx::PxTransform(physx::PxVec3(_pos.getX(), _pos.getY(), _pos.getZ()));
	const Vector4 c = { _color.x, _color.y, _color.z, _color.w };

	_renderItem = new RenderItem(shape, tf, c);

	RegisterRenderItem(_renderItem);
}

Particle::~Particle() {
	DeregisterRenderItem(_renderItem);
}

void Particle::integrate(double t, integrateMode i){
	switch (i){
	case EULER:
		integrateEuler(t);
		break;
	case SEMIEULER:
		integrateSemiEuler(t);
		break;
	case VERLET:
		// integrateVerlet(t); TODO revisar si esta bien o no
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
	_pos = _pos + _vel * t;

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
	_pos = _pos + _vel * t;
}

/*
Verlet:
No usa velocidades explicitamente (estas se obtienen como diferencia de posiciones).
Muy estable, popular en simulaciones con particulas.
Se usa en motores como Box2D y en tecnicas de simulacion de telas y fluidos.
*/
void Particle::integrateVerlet(double t){
	// POS_n+1 = 2*POS_n - POS_i-1 + t^2 * a, a: acceleration
	Vector3D auxPos = _pos + _vel * (t - 1); // TODO no tengo claro como sacar POS_i-1
	_pos = _pos * 2 - auxPos + _a * t * t;

}
