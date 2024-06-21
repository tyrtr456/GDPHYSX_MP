#pragma once
#include <list>
#include "RenderParticle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>

namespace P6 {

	class PhysicsWorld {

	public:
		std::list<RenderParticle*> Particles;
		void AddParticle(RenderParticle* toAdd);
		void checkRanking();
		void Update(float time);

	private:
		void UpdateParticleList();

	};

}

