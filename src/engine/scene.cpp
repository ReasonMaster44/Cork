#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "opengl/shader.h"

#include "entity/cube.h"
#include "entity/entity.h"

#include "engine/window.h"
#include "engine/scene.h"

#include "camera.h"


Cork::Scene::Scene(Window* window, Camera* camera, glm::vec3 lightPos, glm::vec3 lightFacing) 
    : window(window), camera(camera), lightPos(lightPos), lightFacing(lightFacing) {

    shader = Shader("Cork/shaders/basic_vert.glsl", "Cork/shaders/basic_frag.glsl");
    projection = glm::perspective(glm::radians(90.0f), (float)window->WIN_W / (float)window->WIN_H, 0.1f, 100.0f);

    glm::mat4 orthogonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);

    lightView = glm::lookAt(lightPos, lightFacing, glm::vec3(0.0f, 1.0f, 0.0f));
    lightProjection = orthogonalProjection * lightView;
}

void Cork::Scene::add(Entity* newEntity) {
    entities.push_back(newEntity);
}

void Cork::Scene::startFrame() {
    shader.bind();

    shader.setUniformMat4("u_view", camera->view);
    shader.setUniformMat4("u_projection", projection);
    shader.setUniformMat4("u_lightProjection", lightProjection);
    shader.setUniformVec3("u_lightPos", lightPos);
}

void Cork::Scene::endFrame() {
    glfwSwapBuffers(window->win);
    glfwPollEvents();
}
