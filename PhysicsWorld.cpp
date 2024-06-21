#include "PhysicsWorld.h"

using namespace P6;

void PhysicsWorld::AddParticle(RenderParticle* toAdd){

	Particles.push_back(toAdd);
}

void PhysicsWorld::Update(float time) {

	UpdateParticleList();

	for (std::list<RenderParticle*>::iterator p = Particles.begin();
		//Continue looping
		p != Particles.end();
		//Move to the next particle.
		p++
		)
	{
		//Call the particle's update
		(*p)->Update(time);
		

		
	}
}

void PhysicsWorld::UpdateParticleList() {
	//Removes all particles in the list that return true to the function
	Particles.remove_if([](RenderParticle* p) {
			return p->IsDestroyed();

		}
	);
}


