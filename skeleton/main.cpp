#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "Render/RenderUtils.hpp"
#include "callbacks.hpp"
#include "Vector3D.h"
#include "Objects/Particle.h"
#include "Objects/Projectile.h"

#include <iostream>

std::string display_text = "Simulador de disparo ('C', 'T', 'G', 'L').";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback   gContactReportCallback;

RenderItem*			    gRenderItem = NULL;

std::vector<Particle*>  gParticles;

void generateBall(float radius, Vector3D pos, Vector4 color) {
	physx::PxShape* _shape = CreateShape(PxSphereGeometry(radius));
	const physx::PxTransform* _trans = new physx::PxTransform(physx::PxVec3(pos.getX(), pos.getY(), pos.getZ()));
	const Vector4 _color = { color.x, color.y, color.z, color.w };

	gRenderItem = new RenderItem(_shape, _trans, _color);
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// Escribir aqui movidas en la practica 0.
	//generateBall(5.0f, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.0f, 1.0f, 1.0f });

	/*
	generateBall(1.0f, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }); // 0.
	generateBall(1.0f, { 7.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }); // X.
	generateBall(1.0f, { 0.0f, 7.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }); // Y.
	generateBall(1.0f, { 0.0f, 0.0f, 7.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }); // Z.
	*/

	
	/*_particle = new Particle(
		{ 7.0, 0.0, 10.0 },
		{ 0.0, 4.0, 0.0 },
		Particle::SEMIEULER
	);*/

	//_particle->setAccel(PxVec3(0.0, 5.0, 0.0));
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	for (Particle* p : gParticles) {
		p->integrate(t);

		std::cout << "PosX :" << (int)p->getPos().x << "   ";
		std::cout << "PosY :" << (int)p->getPos().y << "   ";
		std::cout << "PosZ :" << (int)p->getPos().z << std::endl;
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	//gRenderItem->release(); si no hay gRenderItem no activar

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	for (Particle* p : gParticles) delete p;
}



// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key)) {
	case 'C': // c de cannon bullet (rojo)
		gParticles.push_back(
			new Projectile(physx::PxVec3(0.0f),Projectile::CANNONBULLET,	Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
			break;

	case 'T': // t de tank (verde)
		gParticles.push_back(
			new Projectile(physx::PxVec3(0.0f),Projectile::TANKBULLET, Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		break;

	case 'G': // g de gun (azul)
		gParticles.push_back(new Projectile(physx::PxVec3(0.0f),Projectile::GUN, Vector4(0.0f, 0.0f, 1.0f, 1.0f)));
		break;

	case 'L': // l de laser (morado)
		gParticles.push_back(new Projectile(physx::PxVec3(0.0f), Projectile::LASERBLASTER, Vector4(1.0f, 0.0f, 1.0f, 1.0f)));
		break;

	case ' ': break;
	default: break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}