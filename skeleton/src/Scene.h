#include <vector>
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
#include "Slingshot.h"
#include "Plane.h"
#include "Axis.h"


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
	ParticleForceRegistry* _forceRegistry;
	ForceGenerator* _gravityGen;
	Axis* _axis;
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

// [Escena de la ENTREGA INTERMEDIA] TODO
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

private:
	Particle* _p1;
	Particle* _p2;

	void generateSpringDemo();
};
