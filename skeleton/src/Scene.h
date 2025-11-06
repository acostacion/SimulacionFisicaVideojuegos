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
	void update(double t) override;
	void erase() override;
private:
	ParticleSystem* _particleSys;
	ParticleGen* _particleGen;
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
	void init() override;
	void handleKey(unsigned char key) override;

private:
	std::vector<Projectile*> _bullets;
};

//class Scene4 : public Scene {
//public:
//	void init() override;
//	bool handleKey(unsigned int key) override;
//
//private:
//	void rotateFarmer();
//	void orbitAHFarmer();
//	void orbitHFarmer();
//};
//
//class Scene5 : public Scene {
//public:
//	void init() override;
//};
//
//class Scene6 : public Scene {
//public:
//	void init() override;
//	void setBackgroundColor() override;
//};
//
//class Scene7 : public Scene {
//public:
//	void init() override;
//	void setBackgroundColor() override;
//
//	bool handleKey(unsigned int key) override;
//
//private:
//	void rotateTie();
//	void orbitTie();
//};
//
//class Scene8 : public Scene {
//public:
//	void init() override;
//};
//
//class Scene9 : public Scene {
//public:
//	void init() override;
//};