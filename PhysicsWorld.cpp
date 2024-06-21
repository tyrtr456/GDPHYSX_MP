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

void PhysicsWorld::checkRanking() {

	for (std::list<RenderParticle*>::iterator p = Particles.begin();
		//Continue looping
		p != Particles.end();
		//Move to the next particle.
		p++
		)
	{
		if ((*p)->totalTime >= (*p++)->totalTime && (*p++)->totalTime >= (*p + 2)->totalTime && (*p + 2)->totalTime >= (*p + 3)->totalTime) {
			(*p)->ranking = 1;
			(*p++)->ranking = 2;
			(*p + 2)->ranking = 3;
			(*p + 3)->ranking = 4;

		}

		else if ((*p++)->totalTime >= (*p)->totalTime && (*p)->totalTime >= (*p + 2)->totalTime && (*p + 2)->totalTime >= (*p + 3)->totalTime) {
			(*p)->ranking = 2;
			(*p++)->ranking = 1;
			(*p + 2)->ranking = 3;
			(*p + 3)->ranking = 4;

		}

		else if ((*p+2)->totalTime >= (*p)->totalTime && (*p)->totalTime >= (*p++)->totalTime && (*p++)->totalTime >= (*p + 3)->totalTime) {
			(*p)->ranking = 2;
			(*p++)->ranking = 3;
			(*p + 2)->ranking = 1;
			(*p + 3)->ranking = 4;
		}

		else {
			(*p)->ranking = 4;
			(*p++)->ranking = 3;
			(*p + 2)->ranking = 2;
			(*p + 3)->ranking = 1;
		}
	}

}
void PhysicsWorld::UpdateParticleList() {
	//Removes all particles in the list that return true to the function
	Particles.remove_if([](RenderParticle* p) {
			return p->IsDestroyed();

		}
	);
}


