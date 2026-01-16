#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "opengl/shader.h"
#include "opengl/shadow_map.h"

#include "entity/cube.h"
#include "entity/mesh.h"

#include "engine/window.h"
#include "engine/scene.h"

#include "camera.h"


Cork::Scene::Scene(Cork::Window* window, Cork::Camera* camera, Cork::LightSource* light) 
    : window(window), camera(camera), light(light) {

    shadowMap = ShadowMap(2048, 2048);
    shader = Shader("../Cork/shaders/basic_vert.glsl", "../Cork/shaders/basic_frag.glsl");
    shadowMapShader = Shader("../Cork/shaders/shadowmap_vert.glsl", "../Cork/shaders/shadowmap_frag.glsl");

    projection = glm::perspective(glm::radians(90.0f), (float)window->WIN_W / (float)window->WIN_H, 0.1f, 100.0f);
    
    postProcessingChain = PostProcessingChain(window);

    light->update();
}

void Cork::Scene::add(Mesh* newMesh) {
    meshes.push_back(newMesh);
}

void Cork::Scene::remove(Mesh* mesh) {
    meshes.erase(
        std::remove(meshes.begin(), meshes.end(), mesh),
        meshes.end()
    );
}


void Cork::Scene::startFrame() {
    light->update();

    postProcessingChain.update(timeElapsed);

    shader.bind();

    shader.setUniformMat4("u_view", camera->view);
    shader.setUniformMat4("u_projection", projection);

    shader.setUniformMat4("u_lightProjection", light->projection);
    shader.setUniformVec3("u_lightPos", light->pos);
    shader.setUniformMat4("u_lightView", light->view);

    //shader.setUniform1i("u_shadowMap", 0);

    timeElapsed += 1;
}

void Cork::Scene::endFrame() {
    glfwSwapBuffers(window->win);
    glfwPollEvents();
}

void Cork::Scene::addPostProcessPass(std::string shaderFilePath) {
    postProcessingChain.addPass(shaderFilePath);

    postProcessingChain.passes.back().shader.bind();
    postProcessingChain.passes.back().shader.setUniformMat4("u_projection", glm::ortho(0.0f, (float)window->frameBufferWidth, (float)window->frameBufferHeight, 0.0f, -1.0f, 1.0f));
}