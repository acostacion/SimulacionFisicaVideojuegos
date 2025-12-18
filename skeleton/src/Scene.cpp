#include "Scene.h"

void Scene::init() {
	//_axis = new Axis();
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
	delete _axis;
}

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ...

#pragma region Escena proyectiles
Scene0::~Scene0() { erase(); }

void Scene0::update(double t) {
	for (Particle* p : _particles) { // TODO fixear lo del lifetime.
		if (p != nullptr){
			_gravityGen->particles.push_back(p);
			p->integrate(t);
			_forceRegistry->update(t);

			// si ha superado su lifetime 
			if (p->isDead()) {
				_particles.erase(std::find(_particles.begin(), _particles.end(), p));
				DeregisterRenderItem(p->getRenderItem());
				delete p;
				p = nullptr;
			}
		}
	}
}

void Scene0::handleKey(unsigned char key)
{
	physx::PxVec3 cameraDir = GetCamera()->getDir();
	switch (toupper(key)) {
	case 'C': // c de cannon bullet (rojo)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), cameraDir, Projectile::CANNONBULLET, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		break;

	case 'T': // t de tank (verde)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), cameraDir, Projectile::TANKBULLET, Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		break;

	case 'G': // g de gun (azul)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), cameraDir, Projectile::GUN, Vector4(0.0f, 0.0f, 1.0f, 1.0f)));
		break;

	case 'L': // l de laser (morado)
		_particles.push_back(new Projectile(physx::PxVec3(0.0f), cameraDir, Projectile::LASERBLASTER, Vector4(1.0f, 0.0f, 1.0f, 1.0f)));
		break;

	default: break;
	}
}

void Scene0::erase()
{
	for (Particle* p : _particles) {
		delete p;
		p = nullptr;
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
	_gravityGen = new GravityForceGenerator(physx::PxVec3(0.0, 9.8, 0.0));
	/*_explosionGen = new ExplosionForceGenerator(50);*/
	// _whirlwindGen = new WhirlwindForceGenerator(physx::PxVec3(100.0f));
	_forceRegistry->forceGenerators.push_back(_gravityGen);
	_forceRegistry->forceGenerators.push_back(_explosionGen);
	// _forceRegistry->forceGenerators.push_back(_whirlwindGen);

	// crea el generador gaussiano y lo mete en el particlesystem!!
	_particleSys = new ParticleSystem();
	_particleGen = new GaussianGen(
		new Particle(physx::PxVec3(5.0), physx::PxVec3(0, 5, 0), 1.0, 1.0, { 0.0, 0.0, 1.0, 1.0 }, Particle::SEMIEULER),
		physx::PxVec3(0, 0, 0));
	_particleSys->particleGenerators.push_back(_particleGen);
}

void Scene1::handleKey(unsigned char key){
	switch (toupper(key)) {
	case 'E': // e de explosion
		if (_explosionGen != nullptr) _explosionGen->explode();
		break;

	default: break;
	}
}

void Scene1::update(double t) {
	// para que no vaya engordando el vector con particulas vacias,
	// elimina al principio y luego solo escoge las que son validas para que las fuerzas actuen sobnnre ellas...
	_gravityGen->particles.clear();
	_explosionGen->particles.clear();
	//_whirlwindGen->particles.clear();

	// mete en el gravityforcegenerator todas las particulas activas ahora.
	for (ParticleGen* pg : _particleSys->particleGenerators) {
		if (pg != nullptr) {
			for (Particle* p : pg->particles) {
				if (p != nullptr) {
					_gravityGen->particles.push_back(p);
					_explosionGen->particles.push_back(p);
					//_whirlwindGen->particles.push_back(p);
				}
			}
		}
	}

	_forceRegistry->update(t);
	_particleSys->update(t);
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
	_windGen = new WindForceGenerator(physx::PxVec3(30.0, 0.0, 0.0));

	// generadores de fuerzas al registro.
	_forceRegistry->forceGenerators.push_back(_gravityGen);
	_forceRegistry->forceGenerators.push_back(_windGen);

	// p1 y fuerzas que le afectan.
	_p1 = new Particle(physx::PxVec3(0.0, 50.0, 0.0), physx::PxVec3(0.0), 2.5);
	_gravityGen->particles.push_back(_p1);

	// p2 y fuerzas que le afectan.
	_p2 = new Particle(physx::PxVec3(0.0, 50.0, 0.0), physx::PxVec3(0.0), 5.0);
	_windGen->particles.push_back(_p2);
	_gravityGen->particles.push_back(_p2);
}

void Scene2::update(double t){
	_forceRegistry->update(t);
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

#pragma region Entrega Intermedia
Scene3::~Scene3() { erase(); }

void Scene3::init() { // TODO para el final mover la camara en lugar de mover los objetos.
	Scene::init();

	_plane = new Plane(physx::PxVec3(20.0), 50.0);
	_slingshot = new Slingshot(physx::PxVec3(_plane->getPos().x - 20, _plane->getPos().y + 0.25, _plane->getPos().z), 3.0);

	_particleSys = new ParticleSystem();
	initFountain();
	initWindForce();
}

void Scene3::update(double t){
	_particleSys->update(t);
	// mete en el forcegenerator todas las particulas activas ahora.
	for (ParticleGen* pg : _particleSys->particleGenerators) {
		if (pg != nullptr) {
			for (Particle* p : pg->particles) {
				if (p != nullptr) {
					_gravityGen->particles.push_back(p);
					_windGenerator->particles.push_back(p);
				}
			}
		}
	}
	_forceRegistry->update(t);

	for (Particle* p : _birds) {
		if (p != nullptr) {
			p->integrate(t);

			// si ha superado su lifetime 
			if (p->isDead()) {
				for (ForceGenerator* fg : _forceRegistry->forceGenerators){
					fg->particles.erase(std::find(fg->particles.begin(), fg->particles.end(), p));
				}
				_birds.erase(std::find(_birds.begin(), _birds.end(), p));
				DeregisterRenderItem(p->getRenderItem());
				delete p;
				p = nullptr;
			}
		}
	}
}

void Scene3::handleKey(unsigned char key)
{
	Projectile* bird;
	switch (toupper(key)) {
	case 'B': // disparo desde el tirachinas (pajaro normal)
		bird = new Projectile(_slingshot->getPos(), physx::PxVec3(0.25, 1.0, 0.0), Projectile::ANGRYBIRD, { 1,0,0,1 }, Particle::SEMIEULER, 1.0);
		_birds.push_back(bird);
		_gravityGen->particles.push_back(bird);
		_windGenerator->particles.push_back(bird);
		break;

	case 'C': // disparo desde la camara (aguila)
		bird = new Projectile(GetCamera()->getTransform().p, GetCamera()->getDir(), Projectile::ANGRYBIRD, { 1,1,1,1 }, Particle::SEMIEULER, 2.0);
		_birds.push_back(bird);
		_gravityGen->particles.push_back(bird);
		_windGenerator->particles.push_back(bird);
		break;

	case 'G': // activar/desactivar generador de gravedad
		_gravityGen->setActive(!_gravityGen->isActive());
		break;

	case 'V': // activar/desactivar generador de viento
		_windGenerator->setActive(!_windGenerator->isActive());
		break;
	default: break;
	}
}

void Scene3::erase(){
	delete _plane;
	_plane = nullptr;

	delete _slingshot;
	_slingshot = nullptr;

	delete _particleSys;
	_particleSys = nullptr;

	Scene::erase();
}
void Scene3::initWindForce() {
	_windGenerator = new WindForceGenerator(physx::PxVec3(50.0, 0.0, 0.0));
	_forceRegistry->forceGenerators.push_back(_windGenerator);
}
void Scene3::initFountain()
{
	_fountain = new GaussianGen(
		new Particle(_slingshot->getPos(), physx::PxVec3(0.0, 20.0, 0.0), 1.0, 1.0, {0.5, 0.5, 1.0, 1.0}, Particle::SEMIEULER), _slingshot->getPos());
	_particleSys->particleGenerators.push_back(_fountain);
}
#pragma endregion

// TODO eliminar todas las cosas que hagan new.
#pragma region Muelles y flotacion
Scene4::~Scene4() {
	erase();
}

void Scene4::init() {
	Scene::init();
	//generateSpringDemo();
	//generateAnchoredSpringDemo();
	generateBuoyancyDemo();
}

void Scene4::update(double t) {
	_forceRegistry->update(t);
	if (_p1) _p1->integrate(t);
	if (_p2) _p2->integrate(t);
	if (_p3) _p3->integrate(t);
	if (_p4) _p4->integrate(t);
}

void Scene4::erase() {
	delete _p1; _p1 = nullptr;
	delete _p2; _p2 = nullptr;
	delete _p3; _p3 = nullptr;
	delete _p4; _p4 = nullptr;

	Scene::erase();
}

void Scene4::generateSpringDemo() {
	// First one standard spring uniting 2 particles.
	_p1 = new Particle(physx::PxVec3(-10.0f, 10.0f, 0.0f), physx::PxVec3(0.0), 2.0);
	_p2 = new Particle(physx::PxVec3(10.0f, 10.0f, 0.0f), physx::PxVec3(0.0), 2.0);

	/*SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, _p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, _p1);*/

	/*f1->particles.push_back(_p1);
	f2->particles.push_back(_p2);

	_forceRegistry->forceGenerators.push_back(f1);
	_forceRegistry->forceGenerators.push_back(f2);*/

	// que afecte la gravedad
	_gravityGen->particles.push_back(_p1);
	_gravityGen->particles.push_back(_p2);
}

void Scene4::generateAnchoredSpringDemo() {
	// Then one spring with one fixed side
	_p3 = new Particle(physx::PxVec3(-10.0f, 20.0f, 0.0f), physx::PxVec3(0.0), 0.5);
	//AnchoredSpringForceGenerator* f3 = new AnchoredSpringForceGenerator(1, 10, physx::PxVec3(10.0f, 20.0f, 0.0f));
	/*f3->particles.push_back(_p3);
	_forceRegistry->forceGenerators.push_back(f3);*/
	_gravityGen->particles.push_back(_p3);
}
void Scene4::generateBuoyancyDemo()
{
	_p4 = new Particle(
		physx::PxVec3(0.0f, 5.0f, 0.0f),
		physx::PxVec3(0.0),
		2.0,
		1,
		Vector4(1.0, 0.0, 0.5, 1.0),
		Particle::SEMIEULER,
		Particle::CUBE
	);

	BuoyancyForceGenerator* f4 = new BuoyancyForceGenerator(2.0f, 0.009f, 1000.0f);
	f4->particles.push_back(_p4);
	_forceRegistry->forceGenerators.push_back(f4);
	_gravityGen->particles.push_back(_p4);
}
#pragma endregion

// NOTA: LOS SOLIDOS RIGIDOS YA APARECEN CON GRAVEDAD DE BASE.
#pragma region Solidos rigidos
Scene5::Scene5(physx::PxPhysics* physics, physx::PxScene* pxscene)
	: _physics(physics), _pxscene(pxscene) {
}

Scene5::~Scene5() {
	erase();
}

void Scene5::init() {
	Scene::init();
	createFloor();
	generateSolidRigidDemo();
}

void Scene5::update(double t) {
	_solidSystem->update(t);
	_forceRegistry->update(t); // TODO aqui me he quedao
}

void Scene5::erase() {
	delete _solidSystem;
	_solidSystem = nullptr;

	Scene::erase();
}

void Scene5::createFloor() {
	// Generar suelo
	physx::PxRigidStatic* suelo = _physics->createRigidStatic(physx::PxTransform( 0, 0, 0 ));
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	_pxscene->addActor(*suelo);

	RenderItem* item = new RenderItem(shape, suelo, { 0.8, 0.8, 0.8, 1 });
}

void Scene5::generateSolidRigidDemo()
{
	_solidSystem = new SolidSystem();

	//SolidGen* boxGen = new SolidBoxGen(_physics, _pxscene, physx::PxTransform(physx::PxVec3(0, 10, 0)));
	SolidGen* sphereGen = new SolidSphereGen(_physics, _pxscene, physx::PxTransform(physx::PxVec3(0, 12, 0)));

	//_solidSystem->solidGenerators.push_back(boxGen);
	_solidSystem->solidGenerators.push_back(sphereGen);

	// VIENTO A LAS ESFERAS.
	_wind = new WindForceGenerator(physx::PxVec3(100.0f, 0.0f, 0.0f), 1.0);

	for (physx::PxRigidDynamic* s : sphereGen->solids) {
		_wind->solids.push_back(s);
	}
}

#pragma endregion

#pragma region Entrega Final
//Scene6::Scene6(physx::PxPhysics* physics, physx::PxScene* pxscene)
//	: _physics(physics), _pxscene(pxscene){
//}
//Scene6::~Scene6() { erase(); }
//
//void Scene6::init() { // TODO para el final mover la camara en lugar de mover los objetos.
//	Scene::init();
//
//	_axis = new Axis();
//	_plane = new Plane(physx::PxVec3(20.0), 50.0);
//	_slingshot = new Slingshot(physx::PxVec3(_plane->getPos().x - 20, _plane->getPos().y + 0.25, _plane->getPos().z), 3.0);
//	
//	_particleSys = new ParticleSystem();
//	initFountain();
//	initWindForce();
//}
//
//void Scene6::update(double t) {
//	_particleSys->update(t);
//	// mete en el forcegenerator todas las particulas activas ahora.
//	for (ParticleGen* pg : _particleSys->particleGenerators) {
//		if (pg != nullptr) {
//			for (Particle* p : pg->particles) {
//				if (p != nullptr) {
//					_gravityGen->particles.push_back(p);
//					_windGenerator->particles.push_back(p);
//				}
//			}
//		}
//	}
//	_forceRegistry->update(t);
//
//	for (Particle* p : _birds) {
//		if (p != nullptr) {
//			p->integrate(t);
//
//			// si ha superado su lifetime 
//			if (p->isDead()) {
//				for (ForceGenerator* fg : _forceRegistry->forceGenerators) {
//					fg->particles.erase(std::find(fg->particles.begin(), fg->particles.end(), p));
//				}
//				_birds.erase(std::find(_birds.begin(), _birds.end(), p));
//				DeregisterRenderItem(p->getRenderItem());
//				delete p;
//				p = nullptr;
//			}
//		}
//	}
//}
//
//void Scene6::handleKey(unsigned char key)
//{
//	//physx::PxRigidDynamic* bird;
//	//switch (toupper(key)) {
//	//case 'B': // disparo desde el tirachinas (pajaro normal)
//
//	//	_birds.push_back(bird);
//	//	_gravityGen->particles.push_back(bird);
//	//	_windGenerator->particles.push_back(bird);
//	//	break;
//
//	//case 'C': // disparo desde la camara (aguila)
//	//	//bird = new Projectile(GetCamera()->getTransform().p, GetCamera()->getDir(), Projectile::ANGRYBIRD, { 1,1,1,1 }, Particle::SEMIEULER, 2.0);
//	//	//_birds.push_back(bird);
//	//	//_gravityGen->particles.push_back(bird);
//	//	//_windGenerator->particles.push_back(bird);
//	//	break;
//
//	//case 'G': // activar/desactivar generador de gravedad
//	//	_gravityGen->setActive(!_gravityGen->isActive());
//	//	break;
//
//	//case 'V': // activar/desactivar generador de viento
//	//	_windGenerator->setActive(!_windGenerator->isActive());
//	//	break;
//	//default: break;
//	//}
//}
//
//void Scene6::erase() {
//	delete _plane;
//	_plane = nullptr;
//
//	delete _slingshot;
//	_slingshot = nullptr;
//
//	delete _particleSys;
//	_particleSys = nullptr;
//
//	Scene::erase();
//}
//physx::PxRigidDynamic* Scene6::createBird(physx::PxVec3 pos) {
//	physx::PxRigidDynamic* bird = _physics->createRigidDynamic(physx::PxTransform(pos));
//	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
//	bird->attachShape(*shape);
//	physx::PxRigidBodyExt::updateMassAndInertia(*bird, 1.0f);
//	_pxscene->addActor(*bird);
//	new RenderItem(shape, bird, { 1, 0, 0, 1 });
//	return bird;
//}
//void Scene6::initWindForce() {
//	_windGenerator = new WindForceGenerator(physx::PxVec3(50.0, 0.0, 0.0));
//	_forceRegistry->forceGenerators.push_back(_windGenerator);
//}
//void Scene6::initFountain()
//{
//	_fountain = new GaussianGen(
//		new Particle(_slingshot->getPos(), physx::PxVec3(0.0, 20.0, 0.0), 1.0, 1.0, { 0.5, 0.5, 1.0, 1.0 }, Particle::SEMIEULER), _slingshot->getPos());
//	_particleSys->particleGenerators.push_back(_fountain);
//}
#pragma endregion
