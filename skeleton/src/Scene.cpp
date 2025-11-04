#include "Scene.h"

#include "GaussianGen.h"

void Scene::init() {
	_forceRegistry = new ParticleForceRegistry();
	_gravityGen = new GravityForceGenerator(); // default, el de la tierra.
	_forceRegistry->forceGenerators.push_back(_gravityGen);
}
void Scene::update(double t){}
void Scene::handleKey(unsigned char key){}
void Scene::erase(){
	// esto borra los generadores de fuerzas tambien.
	delete _forceRegistry;
	_forceRegistry = nullptr;
}


// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ...

#pragma region Escena proyectiles
Scene0::~Scene0(){
	erase();
}

void Scene0::update(double t) {
	for (Particle* p : _particles) {
		_gravityGen->particles.push_back(p);
		p->integrate(t);
		_forceRegistry->update();
	}
}

void Scene0::handleKey(unsigned char key)
{
	switch (toupper(key)) {
	case 'C': // c de cannon bullet (rojo)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), Projectile::CANNONBULLET, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		break;

	case 'T': // t de tank (verde)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), Projectile::TANKBULLET, Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
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

	Scene::erase();
}
#pragma endregion

#pragma region Escena generador de particulas
Scene1::~Scene1(){
	erase();
}

void Scene1::init(){
	// este no llama al init del padre porque la gravedad es distinta.

	// crea la gravittoria y la mete en el registro!
	_forceRegistry = new ParticleForceRegistry();
	_gravityGen = new GravityForceGenerator(physx::PxVec3(0.0, 10.0, 0.0));
	_forceRegistry->forceGenerators.push_back(_gravityGen);

	// crea el generador gaussiano y lo mete en el particlesystem!!
	_particleSys = new ParticleSystem();
	_particleGen = new GaussianGen(physx::PxVec3(0, 0, 0), physx::PxVec3(5, 5, 5), physx::PxVec3(0, 1, 0));
	_particleSys->particleGenerators.push_back(_particleGen);
}

void Scene1::update(double t)
{
	// mete en el gravityforcegenerator todas las particulas activas ahora.
	for (ParticleGen* pg : _particleSys->particleGenerators) {
		if (pg != nullptr) {
			for (Particle* p : pg->particles) {
				if (p != nullptr) {
					_gravityGen->particles.push_back(p);
				}
			}
		}
	}

	_particleSys->update(t);
	_forceRegistry->update();
}

void Scene1::erase(){
	delete _particleSys; // borra particulas y generadores, borra todo, esta muy bien montado.
	Scene::erase();
}
#pragma endregion

#pragma region Escena de pruebas para fuerzas
Scene2::~Scene2(){
	erase();
}

void Scene2::init()
{
	Scene::init();
	_windGen = new WindForceGenerator(physx::PxVec3(5.0, 0.0, 0.0));

	// generadores de fuerzas al registro.
	_forceRegistry->forceGenerators.push_back(_gravityGen);
	_forceRegistry->forceGenerators.push_back(_windGen);

	// p1 y fuerzas que le afectan.
	_p1 = new Particle(physx::PxVec3(0.0, 50.0, 0.0), physx::PxVec3(0.0), 5.0);
	_gravityGen->particles.push_back(_p1);

	// p2 y fuerzas que le afectan.
	_p2 = new Particle(physx::PxVec3(0.0, 50.0, 0.0), physx::PxVec3(0.0), 5.0);
	_windGen->particles.push_back(_p2);
	_gravityGen->particles.push_back(_p2);
}

void Scene2::update(double t){
	_forceRegistry->update();
	_p1->integrate(t);
	_p2->integrate(t);
}

void Scene2::erase(){
	// de lo especifico a lo general, de lo pequenio a lo grande...
	delete _p1;
	_p1 = nullptr;

	delete _p2;
	_p2 = nullptr;

	Scene::erase();
}
#pragma endregion
