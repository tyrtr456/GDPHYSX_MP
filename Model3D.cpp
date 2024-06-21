#include "Model3D.h"

using namespace P6;

Model3D::Model3D(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca, float th, glm::vec3 color)
    : position(pos), rotation(rot), scale(sca), transformationMatrix(glm::mat4(1.0f)), theta(th), color(color) {

    this->theta = th;

}

void Model3D::UpdateTransformationMatrix() {
    this->transformationMatrix = glm::mat4(1.0f);
    this->transformationMatrix = glm::translate(transformationMatrix, position);
    this->transformationMatrix = glm::scale(transformationMatrix, scale);

}

void Model3D::Draw(GLuint shaderProgram, GLuint VAO, std::vector<GLuint>& mesh_indices) {
    UpdateTransformationMatrix();
    //transformation shader
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));

    //color
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(this->color));

    //draw object using VAOs
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);
}