#include "RenderParticle.h"

using namespace P6;

RenderParticle::RenderParticle(Model3D* object) : Position(0,0,0), Velocity(0,0,0), Acceleration(0,0,0), RenderObject(object)  {
	

}

void RenderParticle::UpdatePosition(float time) {

	float oneHalf = ((1.0f / 2.0f));

	this->Velocity.ScalarMultiplication(time);
	this->Acceleration.ScalarMultiplication(time * time);
	this->Acceleration.ScalarMultiplication(oneHalf);

	this->Position.Add(this->Velocity);
	this->Position.Add(this->Acceleration);

	this->RenderObject->position = glm::vec3(this->Position.x, this->Position.y, this->Position.z);

	this->totalTime += time;

}

void RenderParticle::UpdateVelocity(float time) {
	this->Acceleration.ScalarMultiplication(time);
	this->Velocity.Add(this->Acceleration);

}

void RenderParticle::Update(float time) {
	this->UpdatePosition(time);
	this->UpdateVelocity(time);
}

void RenderParticle::Complete() {
	this->isComplete = true;
}

void RenderParticle::Destroy() {

	this->isDestroyed = true;

}

bool RenderParticle::IsDestroyed() {
	return this->isDestroyed;
}

bool RenderParticle::IsCompleted() {
	return this->isComplete;
}