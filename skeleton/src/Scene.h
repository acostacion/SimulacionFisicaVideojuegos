#include <vector>
#include "../callbacks.hpp"
#include <iostream>
#include "Particle.h"
#include "Projectile.h"
#include "GaussianGen.h"
#include "NormalGen.h"
#include "ParticleSystem.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "Slingshot.h"
#include "Plane.h"
#include "Axis.h"
#include "SolidSystem.h"
#include "SolidGen.h"
#include "SolidBoxGen.h"
#include "SolidSphereGen.h"

class Scene{
public:
	Scene() = default;
	virtual ~Scene() = default;

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();
	virtual void update(double t);
	virtual void handleKey(unsigned char key);
	virtual void erase(); // limpia pero no elimina.

protected:
	ParticleForceRegistry* _forceRegistry = nullptr;
	ForceGenerator* _gravityGen = nullptr;
	Axis* _axis = nullptr;

};

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ...

class Scene0 : public Scene {
public:
	~Scene0() override;

	void update(double t) override;
	void handleKey(unsigned char key) override;
	void erase() override;

private:
	std::vector<Particle*> _particles;
};

class Scene1 : public Scene {
public: 
	~Scene1() override;
	void init() override;
	void handleKey(unsigned char key) override;
	void update(double t) override;
	void erase() override;
private:
	ParticleSystem* _particleSys;
	ParticleGen* _particleGen;
	//ForceGenerator* _whirlwindGen;
	ExplosionForceGenerator* _explosionGen;
};

class Scene2 : public Scene {
public:
	~Scene2() override;
	void init() override;
	void update(double t) override;
	void erase() override;
private:
	ForceGenerator* _windGen;
	Particle* _p1;
	Particle* _p2;
};

// [Escena de la ENTREGA INTERMEDIA] 
class Scene3 : public Scene {
public:
	~Scene3() override;
	void init() override;
	void update(double t) override;
	void handleKey(unsigned char key) override;
	void erase() override;

private:
	ForceGenerator* _windGenerator;
	ParticleSystem* _particleSys;
	ParticleGen* _fountain; 
	Plane* _plane;
	Slingshot* _slingshot;
	std::vector<Projectile*> _birds;

	void initWindForce();
	void initFountain();
};

class Scene4 : public Scene {
public:
	~Scene4() override;
	void init() override;
	void update(double t) override;
	void erase() override;

private:
	Particle* _p1;
	Particle* _p2;
	Particle* _p3;
	Particle* _p4;

	void generateSpringDemo();
	void generateAnchoredSpringDemo();
	void generateBuoyancyDemo();
};

class Scene5 : public Scene {
public:
	Scene5(physx::PxPhysics* physics, physx::PxScene* pxscene); // TODO hacer esto pa maniana
	~Scene5() override;
	void init() override;
	void update(double t) override;
	void erase() override;

private:
	physx::PxPhysics* _physics;
	physx::PxScene* _pxscene;

	SolidSystem* _solidSystem;

	void createFloor();
	void generateSolidRigidDemo();
};

//// [Escena de la ENTREGA FINAL] TODO
//class Scene6 : public Scene {
//public:
//	Scene6(physx::PxPhysics* physics, physx::PxScene* pxscene);
//	~Scene6() override;
//	void init() override;
//	void update(double t) override;
//	void handleKey(unsigned char key) override;
//	void erase() override;
//
//
//private:
//	physx::PxPhysics* _physics;
//	physx::PxScene* _pxscene;
//
//	ForceGenerator* _windGenerator;
//	ParticleSystem* _particleSys;
//	ParticleGen* _fountain;
//	Plane* _plane;
//	Slingshot* _slingshot;
//	std::vector<physx::PxRigidDynamic*> _birds;
//
//	physx::PxRigidDynamic* createBird(physx::PxVec3 pos);
//	void initWindForce();
//	void initFountain();
//};
