#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>

namespace P6 {

    class Model3D {
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::vec3 color;
        float theta;

    public:

        Model3D(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca, float th, glm::vec3 color);

        void UpdateTransformationMatrix();

        void Draw(GLuint shaderProgram, GLuint VAO, std::vector<GLuint>& mesh_indices);

    private:
        glm::mat4 transformationMatrix;
    };
}


