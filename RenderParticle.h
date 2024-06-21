#pragma once

#include "P6/MyVector.h"
#include "Model3D.h"

namespace P6 {

	class RenderParticle {

	protected:
		bool isDestroyed = false;
		bool isComplete = false;

	public:
		int ranking = 0;
		int totalTime = 0;
		Model3D* RenderObject;
		MyVector Position;
		MyVector Velocity;
		MyVector Acceleration;

	
	public:
		RenderParticle(Model3D* object);

	protected:
		void UpdatePosition(float time);
		void UpdateVelocity(float time);


	public:
		void Update(float time);
		void Complete();
		void Destroy();
		bool IsDestroyed();
		bool IsCompleted();




	};







}