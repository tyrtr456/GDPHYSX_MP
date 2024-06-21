#pragma once

#include "P6/MyVector.h"
#include "Model3D.h"

namespace P6 {

	class RenderParticle {

	protected:
		bool isDestroyed = false;
		bool isComplete = false;

	public:
		float damping = 0.9f;
		float mass = 1.0f;
		int totalTime = 0;
		float lifespan = 0.0f;
		Model3D* RenderObject;
		MyVector AccumulatedForce;
		MyVector Position;
		MyVector Velocity;
		MyVector Acceleration;

	
	public:
		RenderParticle(Model3D* object, float lifespan);

	protected:
		void UpdatePosition(float time);
		void UpdateVelocity(float time);
		void AddForce(MyVector Force);
		void ResetForce();


	public:
		void Update(float time);
		void Complete();
		void Destroy();
		bool IsDestroyed();
		bool IsCompleted();




	};







}