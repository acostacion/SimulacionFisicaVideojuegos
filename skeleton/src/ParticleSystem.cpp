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

	// mantenimiento de particulas
	for (Particle* p: particles){
		if (p->getLifeTime() > MAX_LIFE_TIME) delete p;

		p->integrate(t); // cuidao con integrar despues de eliminar!! TODO
	}


	// generacion de particulas
	for (ParticleGen* pg : generators)
	{
		// particulas activas de un solo generador.
		pg->generateP(particles); // genera particulas y modifica el vector.
	}
}
