#include "Scene.h"

#include "GaussianGen.h"


void Scene::init(){}
void Scene::update(double t){}
void Scene::handleKey(unsigned char key){}
void Scene::erase(){}

Scene0::~Scene0(){
	erase();
}

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ... 
void Scene0::update(double t)
{
	for (Particle* p : _particles) {
		p->integrate(t);

		/*std::cout << "PosX :" << (int)p->getPos().x << "   ";
		std::cout << "PosY :" << (int)p->getPos().y << "   ";
		std::cout << "PosZ :" << (int)p->getPos().z << std::endl;*/
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

void Scene0::erase(){
	for (Particle* p : _particles) {
		DeregisterRenderItem(p->getRenderItem());
		delete p;
	}
}

Scene1::~Scene1(){
	erase();
}

void Scene1::init()
{
	_pg = new GaussianGen(physx::PxVec3(0, 0, 0), physx::PxVec3(5, 5, 5), physx::PxVec3(0, 1, 0));
	_ps = new ParticleSystem();
	_ps->particleGenerators.push_back(_pg);
}

void Scene1::update(double t)
{
	_ps->update(t);
}

void Scene1::erase(){
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
	_p = new Particle(physx::PxVec3(0.0, 50.0, 0.0), physx::PxVec3(0.0));
	_gfg = new GravityForceGenerator();
	_pfr = new ParticleForceRegistry();
	_pfr->particles.push_back(_p);
	_pfr->forceGenerators.push_back(_gfg);
	
}

void Scene2::update(double t){
	_pfr->update(t);
	_p->integrate(t);
}

void Scene2::erase(){
	delete _gfg;
	_gfg = nullptr;

	delete _pfr;
	_pfr = nullptr;
}
