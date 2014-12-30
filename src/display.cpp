#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "display.h"

extern GLuint shaderProgram;
static GLuint VAO;

void displayMode() {
	glfwSetErrorCallback(errorCallback);
    ensureShaders(TEST_VS, TEST_FRAG);
    ensureModel(SUIT);
    GLfloat vertices[] = {
        0.5, 0.0, 
        -0.5, 0.5,
        0.0, 0.5
    };
}
void errorCallback(int error, const char* description) {
    fputs(description, stderr);
}
void displayFunc(GLFWwindow* window) {
    glClearColor(0.05, 0.05, 0.05, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

    glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
    glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
    glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0, -1.75, 0.0));
    model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    drawModel(SUIT);
}
