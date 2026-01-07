#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "opengl/shader.h"
#include "opengl/shadow_map.h"

#include "entity/cube.h"
#include "entity/entity.h"

#include "engine/window.h"
#include "engine/scene.h"

#include "camera.h"


Cork::Scene::Scene(Window* window, Camera* camera, glm::vec3 lightPos, glm::vec3 lightFacing) 
    : window(window), camera(camera), lightPos(lightPos), lightFacing(lightFacing) {

    shadowMap = ShadowMap(2048, 2048);
    shader = Shader("../Cork/shaders/basic_vert.glsl", "../Cork/shaders/basic_frag.glsl");
    shadowMapShader = Shader("../Cork/shaders/shadowmap_vert.glsl", "../Cork/shaders/shadowmap_frag.glsl");

    projection = glm::perspective(glm::radians(90.0f), (float)window->WIN_W / (float)window->WIN_H, 0.1f, 100.0f);

    lightOrthogonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);

    updateLightProjection();
}

void Cork::Scene::add(Entity* newEntity) {
    entities.push_back(newEntity);
}

void Cork::Scene::startFrame() {
    updateLightProjection();

    shader.bind();

    shader.setUniformMat4("u_view", camera->view);
    shader.setUniformMat4("u_projection", projection);
    shader.setUniformMat4("u_lightProjection", lightProjection);
    shader.setUniformVec3("u_lightPos", lightPos);
    shader.setUniform1i("u_shadowMap", 0);
}

void Cork::Scene::endFrame() {
    glfwSwapBuffers(window->win);
    glfwPollEvents();
}

void Cork::Scene::updateLightProjection() {
    glm::vec3 forward = glm::normalize(lightFacing - lightPos);
    glm::vec3 worldUp = glm::vec3(0, 1, 0);

    if (glm::abs(glm::dot(forward, worldUp)) > 0.999f) { worldUp = glm::vec3(1, 0, 0); }

    lightView = glm::lookAt(lightPos, lightFacing, worldUp);

    lightProjection = lightOrthogonalProjection * lightView;
}