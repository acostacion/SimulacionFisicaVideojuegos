#include <vector>
#include <iostream>
#include "Particle.h"
#include "Projectile.h"


class Scene{
public:
	Scene() = default;
	virtual ~Scene() = default;

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init() = 0;
	virtual void update(double t) = 0;
	virtual void handleKey(unsigned char key) = 0;
};

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ...

class Scene0 : public Scene {
public:
	~Scene0();
	void init() override;
	void update(double t) override;
	void handleKey(unsigned char key) override;

private:
	std::vector<Particle*> _particles;
};

//class Scene1 : public Scene {
//public:
//	void init() override;
//};

//class Scene2 : public Scene {
//public:
//	void init() override;
//};
//
//class Scene3 : public Scene {
//public:
//	void init() override;
//};
//
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