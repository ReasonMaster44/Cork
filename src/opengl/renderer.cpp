#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "opengl/renderer.h"

#include "opengl/shader.h"
#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"
#include "opengl/glerrorhandler.h"

#include "engine/scene.h"
#include "engine/overlay.h"
#include "engine/window.h"

#include "entity/mesh.h"
#include "entity/quad.h"

Cork::Renderer::Renderer(Window* window) {
    shadowMapDebugQuad = Cork::Quad(glm::vec2(0.0f), glm::vec2((float)window->WIN_W, (float)window->WIN_H));
    shadowMapDebugShader = Cork::Shader("../Cork/shaders/shadowmap_vert_debug.glsl", "../Cork/shaders/shadowmap_frag_debug.glsl");

    framebufferQuad = Cork::Quad(glm::vec2(0.0f, 0.0f), glm::vec2((float)window->frameBufferWidth, (float)window->frameBufferHeight));
}

void Cork::Renderer::clear() {
    GLCall(glClearColor(0.105f, 0.12f, 0.13f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Cork::Renderer::render(IBO* ibo, VAO* vao, Shader* shader) {
    vao->bind();
    ibo->bind();

    GLCall(glDrawElements(GL_TRIANGLES, ibo->count, GL_UNSIGNED_INT, 0));
}

void Cork::Renderer::renderShadowMap(Scene* scene) {
    scene->shadowMap.bindForRendering();


    scene->shadowMapShader.bind();
    scene->shadowMapShader.setUniformMat4("u_lightProjection", scene->light->projection);
    scene->shadowMapShader.setUniformMat4("u_lightView", scene->light->view);


    for (Mesh* mesh : scene->meshes) {
        scene->shadowMapShader.setUniformMat4("u_model", mesh->model);
        render(&mesh->ibo, &mesh->vao, &scene->shadowMapShader);
    }

    scene->shadowMap.unbind(scene->window->frameBufferWidth, scene->window->frameBufferHeight);

}

void Cork::Renderer::renderShadowMapDebug(Scene* scene) {
    renderShadowMap(scene);
    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->shadowMap.texture);

    shadowMapDebugShader.bind();
    shadowMapDebugShader.setUniform1i("u_shadowMap", 0);

    clear();

    render(&shadowMapDebugQuad.ibo, &shadowMapDebugQuad.vao, &shadowMapDebugShader);
}

void Cork::Renderer::renderScene(Scene* scene) {
    clear();
    renderShadowMap(scene);

    
    int numberOfPostProcessPasses = scene->postProcessingChain.passes.size();
    unsigned int textureSlot = 10;

    if (numberOfPostProcessPasses > 0) {
        scene->postProcessingChain.passes[0].framebuffer.bind();
        scene->postProcessingChain.passes[0].texture.bind(textureSlot);
        clear();
    }
    

    renderMeshes(scene);
    
    GLCall(glDisable(GL_DEPTH_TEST));

    if (numberOfPostProcessPasses > 0) {
        for (int i = 1; i < numberOfPostProcessPasses; i++) {
            scene->postProcessingChain.passes[i].texture.bind(textureSlot + 1);
            scene->postProcessingChain.passes[i].framebuffer.bind();

            renderPostProcessPass(scene, i - 1, textureSlot);
            textureSlot++;
        }

        Cork::FrameBuffer::bindDefault();

        renderPostProcessPass(scene, numberOfPostProcessPasses - 1, textureSlot);
    }
}

void Cork::Renderer::renderMeshes(Cork::Scene* scene) {
    GLCall(glEnable(GL_DEPTH_TEST));
    scene->shader.bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->shadowMap.texture);

    scene->shader.setUniform1i("u_shadowMap", 0);

    for (Cork::Mesh* mesh : scene->meshes) {
        scene->shader.setUniformMat4("u_model", mesh->model);
        render(&mesh->ibo, &mesh->vao, &scene->shader);
    }
}

void Cork::Renderer::renderPostProcessPass(Cork::Scene* scene, int frameBufferIndex, int textureSlot) {
    std::string baseUniformName = "u_screenTexture";
    std::string currentUniformName = baseUniformName + std::to_string(frameBufferIndex);

    scene->postProcessingChain.passes[frameBufferIndex].shader.bind();
    scene->postProcessingChain.passes[frameBufferIndex].shader.setUniform1i(currentUniformName, textureSlot);

    for (int i = 0; i < frameBufferIndex; i++) {
        currentUniformName = baseUniformName + std::to_string(frameBufferIndex - i - 1);

        scene->postProcessingChain.passes[frameBufferIndex - i - 1].texture.bind(textureSlot - i - 1);
        scene->postProcessingChain.passes[frameBufferIndex].shader.setUniform1i(currentUniformName, textureSlot - i - 1);
    }
    
    scene->postProcessingChain.passes[frameBufferIndex].shader.setUniformMat4("u_model", framebufferQuad.model);
    render(&framebufferQuad.ibo, &framebufferQuad.vao, &scene->postProcessingChain.passes[frameBufferIndex].shader);
}

void Cork::Renderer::renderOverlay(Overlay* overlay) {
    GLCall(glDisable(GL_DEPTH_TEST));
    
    for (Quad* quad : overlay->quads) {
        overlay->currentShader->bind();
        overlay->currentShader->setUniformMat4("u_model", quad->model);

        if (quad->texture == nullptr) {
            overlay->currentShader->setUniformVec3("u_baseColour", quad->colour);
        } else {
            quad->texture->bind(5);
            overlay->currentShader->setUniform1i("u_texture", 5);  
            //quad->texture->unbind();
        }

        //quad->texture->bind(0);
        //overlay->currentShader->setUniform1i("u_texture", 0);  
        
        render(&quad->ibo, &quad->vao, overlay->currentShader);
        overlay->currentShader->unbind();
    }
}