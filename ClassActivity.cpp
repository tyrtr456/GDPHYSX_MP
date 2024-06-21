#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "P6/MyVector.h"
#include "RenderParticle.h"
#include "PhysicsWorld.h"
#include "Model3D.h"
#include <string>
#include <iostream>

#include <chrono>

using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(1000ms);  


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float window_width = 700.0f;
    float window_height = 700.0f;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "PC01 - Uriel Pascual", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    /*glViewport(0, //min x
        0, //min y
        640, //x
        480); //y */

        //load vert shader
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();

    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    //load frag shader
    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();

    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    //add vertex shader
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);

    GLint isCompiled = 0;

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vertShader, maxLength, &maxLength, &errorLog[0]);
        std::cout << &errorLog[0];
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        //glDeleteShader(fragShader); // Don't leak the shader.
    }

    //add frag shader
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragShader, maxLength, &maxLength, &errorLog[0]);
        std::cout << &errorLog[0];
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(fragShader); // Don't leak the shader.
    }

    //create shader program and attach compiled shaders
    GLuint shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertShader);
    glAttachShader(shaderProg, fragShader);

    //finalize the compilation process
    glLinkProgram(shaderProg);

    std::string path = "3D/sphere.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;  
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );

    //get EBO indices array
    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

    GLfloat vertices[]{
        //x   y     z
        0.f, 0.5f, 0.f, //0
        -0.5f, -0.5f, 0.f, //1
        0.5f, -0.5f, 0.f //2
    };

    GLuint indices[]{
        0, 1, 2
    };

    GLuint VAO, VBO, EBO;
    //Initialize VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //tell opengl to use shader for VAOs below
    glUseProgram(shaderProg);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //VBO
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * attributes.vertices.size(), //bytes
        &attributes.vertices[0],         // == attributes.vertices.data()
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, //0 pos, 1 tex, 2 norms
        3, //xyz
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GL_FLOAT),
        (void*)0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * mesh_indices.size(),
        &mesh_indices[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    float x, y, z;
    x = y = z = 0.0f;
    z = -5.0f;
    glm::mat3 identity_matrix3 = glm::mat3(1.0f);
    glm::mat4 identity_matrix4 = glm::mat4(1.0f);

    float scale_x, scale_y, scale_z = 1.f;
    scale_x = scale_y = scale_z = 1.f;

    float axis_x, axis_y, axis_z, theta = 0.f;
    axis_x = axis_y = axis_z = theta = 0.f;
    axis_y = 1.f;

    glm::mat4 projectionMatrix = glm::ortho(
        -1.f, //left
        1.f, //right
        -1.f, //bottom
        1.f, //top
        -1.f, //znear
        400.f //zfar
    );

    /*glm::mat4 projectionMatrix = glm::ortho(
        -400.f, //left
        400.f, //right
        -400.f, //bottom
        400.f, //top
        -400.f, //znear
        400.f //zfar
    );*/


    /*glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(60.f), //fov
        window_height / window_width, //aspect ratio
        0.1f, //znear > 0
        100.0f //zfar
    );*/

    P6::PhysicsWorld pWorld = P6::PhysicsWorld();

    P6::Model3D particleModel1 = P6::Model3D(glm::vec3(-0.800f, 0.700f, 0.201f), glm::vec3(0.0f), glm::vec3(0.02f), 0.0f, glm::vec3(1, 0, 0));
    P6::Model3D particleModel2 = P6::Model3D(glm::vec3(0.800f, 0.700f, 0.173f), glm::vec3(0.0f), glm::vec3(0.02f), 0.0f, glm::vec3(0, 255, 0));
    P6::Model3D particleModel3 = P6::Model3D(glm::vec3(-0.800, -0.700, -0.300f), glm::vec3(0.0f), glm::vec3(0.02f), 0.0f, glm::vec3(0, 0, 1));
    P6::Model3D particleModel4 = P6::Model3D(glm::vec3(0.800, -0.700, -0.150f), glm::vec3(0.0f), glm::vec3(0.02f), 0.0f, glm::vec3(255, 255, 0));

    P6::RenderParticle p1 = P6::RenderParticle(&particleModel1);
    p1.Position = P6::MyVector(particleModel1.position.x, particleModel1.position.y, particleModel1.position.z);
    p1.Velocity = P6::MyVector(0.8f, 0.8f, 0.f);
    p1.Acceleration = P6::MyVector(0.145f, 0.145f, 0.f);
    pWorld.AddParticle(&p1);

    P6::RenderParticle p2 = P6::RenderParticle(&particleModel2);
    p2.Position = P6::MyVector(particleModel2.position.x, particleModel2.position.y, particleModel2.position.z);
    p2.Velocity = P6::MyVector(0.9f, 0.0f, 0.f);
    p2.Acceleration = P6::MyVector(0.08f, 0.08f, 0.f);
    pWorld.AddParticle(&p2);

    P6::RenderParticle p3 = P6::RenderParticle(&particleModel3);
    p2.Position = P6::MyVector(particleModel3.position.x, particleModel3.position.y, particleModel3.position.z);
    p2.Velocity = P6::MyVector(0.13f, 0.13f, 0.f);
    p2.Acceleration = P6::MyVector(0.01f, 0.01f, 0.f);
    pWorld.AddParticle(&p3);

    P6::RenderParticle p4 = P6::RenderParticle(&particleModel4);
    p2.Position = P6::MyVector(particleModel4.position.x, particleModel4.position.y, particleModel4.position.z);
    p2.Velocity = P6::MyVector(0.11f, 0.11f, 0.f);
    p2.Acceleration = P6::MyVector(0.03f, 0.03f, 0.f);
    pWorld.AddParticle(&p4);

    //initialize clock
    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //get current time
        curr_time = clock::now();
        //check duration
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(curr_time - prev_time);
        //set prev to current
        prev_time = curr_time;
        //add duration
        curr_ns += dur;

        if (curr_ns >= timestep) {
            //convert ns to ms
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            curr_ns -= timestep;
            //std::cout << "MS: " << (float)ms.count() << "\n";
            //reset
            curr_ns -= curr_ns;
            //call updates
           //std::cout << "P6 Update" << "\n";
           pWorld.Update((float)ms.count() / 1000);

        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");

        glUniformMatrix4fv(projectionLoc, //address of transform variable
            1, //how many matrices to assign
            GL_FALSE, //transpose
            glm::value_ptr(projectionMatrix) //pointer to matrix
        );

        for (std::list<P6::RenderParticle*>::iterator p = pWorld.Particles.begin();

            //Continue looping
            p != pWorld.Particles.end();
            //Move to the next particle.
            p++
            )
        {
            //Call the particle's update
            (*p)->RenderObject->Draw(shaderProg, VAO, mesh_indices);

        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}