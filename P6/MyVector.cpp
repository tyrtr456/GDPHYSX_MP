
#include "MyVector.h"

using namespace P6;

    MyVector::MyVector(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Addition
    void MyVector::Add(MyVector b) {
        this->x += b.x;
        this->y += b.y;
        this->z += b.z;  
    }

    // Subtraction
    void MyVector::Subtract(MyVector b) {
        glm::vec3 result = glm::vec3(this->x + b.x, this->y + b.y, this->z + b.z);
        this->x -= b.x;
        this->y -= b.y;
        this->z -= b.z;
    }

    // Component-wise Multiplication
    void MyVector::Multiply(MyVector b) {

        this->x = this->x * b.x;
        this->y = this->y * b.y;
        this->z = this->z * b.z;
        
    }

    // Component-wise Division
    void MyVector::Divide(MyVector b) {
        this->x = this->x/b.x;
        this->y = this->y/b.y;
        this->z = this->z/b.z;
    }

    // Magnitude
    float MyVector::getMagnitude() {
        float result = glm::length(glm::vec3(this->x, this->y, this->z));
        return result;
    }

    // Direction (Normalization)
    glm::vec3 MyVector::getDirection() {
        glm::vec3 result = glm::normalize(glm::vec3(this->x, this->y, this->z));
        return result;
    }

    // Scalar Multiplication
    glm::vec3 MyVector::ScalarMultiplication(float scalar) {
        glm::vec3 result = glm::vec3(this->x * scalar, this->y * scalar, this->z * scalar);
        return result;
    }

    // Scalar (Dot) Product
    float MyVector::ScalarProduct(MyVector b) {
        return glm::dot(glm::vec3(this->x, this->y, this->z), glm::vec3(b.x, b.y, b.z));
    }

    // Vector (Cross) Product
    glm::vec3 MyVector::VectorProduct(MyVector b) {
        glm::vec3 result = glm::cross(glm::vec3(this->x, this->y, this->z), glm::vec3(b.x, b.y, b.z));
        return result;
    }

 

