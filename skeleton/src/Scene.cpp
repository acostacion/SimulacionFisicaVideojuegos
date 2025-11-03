#include "Scene.h"

#include "GaussianGen.h"

void Scene::init(){}
void Scene::update(double t){}
void Scene::handleKey(unsigned char key){}
void Scene::erase(){}


// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ... 
Scene0::~Scene0(){
	erase();
}

void Scene0::update(double t) {
	for (Particle* p : _particles) {
		p->integrate(t);
	}
}

void Scene0::handleKey(unsigned char key)
{
	switch (toupper(key)) {
	case 'C': // c de cannon bullet (rojo)
		_particles.push_back(
			new Projectile(physx::PxVec3(0.0f), Projectile::CANNONBULLET, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		break;

	case 'T': // t de tank (verde)
		_particles.push_back(
			new Projectile(physx::PxVec3(0.0f), Projectile::TANKBULLET, Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		break;

	case 'G': // g de gun (azul)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), Projectile::GUN, Vector4(0.0f, 0.0f, 1.0f, 1.0f)));
		break;

	case 'L': // l de laser (morado)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), Projectile::LASERBLASTER, Vector4(1.0f, 0.0f, 1.0f, 1.0f)));
		break;

	default: break;
	}
}

void Scene0::erase()
{
	for (Particle* p : _particles) {
		delete p;
	}
	_particles.clear();
}

Scene1::~Scene1(){
	erase();
}

void Scene1::init()
{
	_forceRegistry = new ParticleForceRegistry();
	_gravityGenerator = new GravityForceGenerator(physx::PxVec3(0.0, -10.0, 0.0));
	_pg = new GaussianGen(physx::PxVec3(0, 0, 0), physx::PxVec3(5, 5, 5), physx::PxVec3(0, 1, 0));


	for (Particle* p : _pg->particles){
		if (p != nullptr){
			_gravityGenerator->particles.push_back(p);
		}
	}
	_ps = new ParticleSystem();
	_forceRegistry->forceGenerators.push_back(_gravityGenerator);
	_ps->particleGenerators.push_back(_pg);
	
}

void Scene1::update(double t)
{

	_forceRegistry->update();
	_ps->update(t);
}

void Scene1::erase(){ // TODO
	delete _pg;
    _pg = nullptr;
	//_ps->particleGenerators.clear();

	delete _ps;
	_ps = nullptr;
	
}

Scene2::~Scene2(){
	erase();
}

void Scene2::init()
{
	_forceRegistry = new ParticleForceRegistry();
	_gravityGen = new GravityForceGenerator(); // default, el de la tierra.

	_p1 = new Particle(
		physx::PxVec3(0.0, 50.0, 0.0), 
		physx::PxVec3(0.0)
	);

	_gravityGen->particles.push_back(_p1);

	_forceRegistry->forceGenerators.push_back(_gravityGen);
}

void Scene2::update(double t){
	_forceRegistry->update();
	_p1->integrate(t);
}

void Scene2::erase(){
	// de lo especifico a lo general, de lo pequenio a lo grande...
	delete _p1;
	_p1 = nullptr;

	// el registro se encarga de borrar los generadoresw.
	delete _forceRegistry;
	_forceRegistry = nullptr;
}
