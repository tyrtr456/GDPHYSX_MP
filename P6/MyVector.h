#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace P6 {
	class MyVector
	{
		public:
			float x, y, z;

	public:
		MyVector(float x, float y, float z);



	public:
		void Add(MyVector b);
		void Subtract(MyVector b);
		void Multiply(MyVector b);
		void Divide(MyVector b);

		float getMagnitude();
		glm::vec3 getDirection();
		glm::vec3 ScalarMultiplication(float scalar);
		float ScalarProduct(MyVector b);
		glm::vec3 VectorProduct(MyVector b);
			
	};

}

