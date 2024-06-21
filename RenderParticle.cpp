#include "RenderParticle.h"

using namespace P6;

RenderParticle::RenderParticle(Model3D* object, float lifespan) : AccumulatedForce(0,0,0), Position(0,0,0), Velocity(0,0,0), Acceleration(0,0,0), RenderObject(object)  {
	
	this->lifespan = lifespan;
}

void RenderParticle::UpdatePosition(float time) {

	float oneHalf = ((1.0f / 2.0f));

	//calculates for the formula needed to apply speed
	glm::vec3 scaledVel = this->Velocity.ScalarMultiplication(time);
	glm::vec3 acceleration = this->Acceleration.ScalarMultiplication(time * time);
	MyVector accel = MyVector(acceleration.x * oneHalf, acceleration.y * oneHalf, acceleration.z * oneHalf);
	MyVector vel = MyVector(scaledVel.x, scaledVel.y, scaledVel.z);

	//updates the position
	vel.Add(accel);
	this->Position.Add(vel);
	this->RenderObject->position = glm::vec3(this->Position.x, this->Position.y, this->Position.z);

	this->totalTime += time;

}

void RenderParticle::UpdateVelocity(float time) {
	
	//apply force and damping before acceleration
	glm::vec3 accumulatedForce = this->AccumulatedForce.ScalarMultiplication(1.0f / mass);
	
	this->Acceleration.Add(MyVector(accumulatedForce.x, accumulatedForce.y, accumulatedForce.z));
	glm::vec3 acceleration = this->Acceleration.ScalarMultiplication(time);
	this->Velocity.Add(MyVector(acceleration.x, acceleration.y, acceleration.z));
	glm::vec3 finalVelocity = this->Velocity.ScalarMultiplication(powf(this->damping, time));

	this->Velocity.x = finalVelocity.x;
	this->Velocity.y = finalVelocity.y;
	this->Velocity.z = finalVelocity.z;

}

void RenderParticle::AddForce(MyVector force) {
	this->AccumulatedForce.Add(force);
}

void RenderParticle::ResetForce() {
	this->AccumulatedForce = MyVector(0, 0, 0);
	this->Acceleration = MyVector(0, 0, 0);
}

void RenderParticle::Update(float time) {
	this->UpdatePosition(time);
	this->UpdateVelocity(time);
	this->lifespan -= 1.0f * time;

	if (this->lifespan <= 0.0f) {
		this->Destroy();
	}

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