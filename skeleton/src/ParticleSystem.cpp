#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
	for (Particle* p : particles) delete p;
	for (ParticleGen* pg : generators) delete pg;
}

void ParticleSystem::update(double t) // TODO modificar creo k esta mal.
{
	/* En cada update mi sistema de particulas tendra que:
	 * - Labores de mantenimiento de las particulas
	 *		- Actualizar el tiempo que lleva "vivo" -> cada particula actualiza su lifetime.············[DONE]
	 *		- Recorrer la lista de particulas y revisar si cada una de ellas ha de seguir viva o no:
	 *			- Se ha terminado su tiempo de vida·····················································[DONE]
	 *			- Esta fuera de la zona de interes······················································[TODO]
	 *		- Eliminar las particulas que "mueren"······················································[DONE]
	 *		- Llamar al update de cada particula························································[DONE]
	 * - Labores de generacion de particulas nuevas
	 *		- Recorrer los distintos generadores
	 *		- Generar las particulas nuevas
	 *		- Aniadirlas a la lista de particulas
	 */


	// 1 - GENERA - 
	// generacion de particulas
	for (ParticleGen* pg : generators)
	{
		if (pg != nullptr) {
			// particulas activas de un solo generador.
			pg->generateP(particles); // genera particulas y modifica el vector.
		}
	}
	
	// 2 - MANTIENE -
	// mantenimiento de particulas
	for (Particle* p: particles){
		// daba problemas de que llamaba a integrates de particulas muertas
		if (p != nullptr) { 
			setGravity(p, GRAVITY); // le pone la gravedad
			p->integrate(t); // updatea particula.

			// si ha superado su lifetime o se ha salido del espacio de accion (modificar espacio de accion)
			if ((p->getLifeTime() > MAX_LIFE_TIME) || (p->getPos().y >= ACTION_ZONE.y)) {
				// eliminamos del vector, deregistereamos, lo ponemos a nullptr y lo eliminamos.
				particles.erase(std::find(particles.begin(), particles.end(), p));
				DeregisterRenderItem(p->getRenderItem());
				p = nullptr;
				delete p; 
			}
		}
	}
}

void ParticleSystem::setGravity(Particle* p, float g){
	p->setAccel(physx::PxVec3(0.0f, -g, 0.0f));
}
