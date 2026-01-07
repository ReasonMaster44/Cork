#include "opengl/renderer.h"

#include "opengl/shader.h"
#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"
#include "opengl/glerrorhandler.h"

#include "engine/scene.h"
#include "engine/overlay.h"
#include "engine/window.h"

#include "entity/entity.h"
#include "entity/quad.h"

Cork::Renderer::Renderer(Window* window) {
    shadowMapDebugQuad = Cork::Quad(glm::vec2(0.0f), glm::vec2((float)window->WIN_W, (float)window->WIN_H));
    shadowMapDebugShader = Cork::Shader("../Cork/shaders/shadowmap_vert_debug.glsl", "../Cork/shaders/shadowmap_frag_debug.glsl");
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
    scene->shadowMapShader.setUniformMat4("u_lightProjection", scene->lightProjection);

    for (Entity* entity : scene->entities) {
        scene->shadowMapShader.setUniformMat4("u_model", entity->model);
        render(&entity->ibo, &entity->vao, &scene->shadowMapShader);
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
    GLCall(glEnable(GL_DEPTH_TEST));

    renderShadowMap(scene);

    for (Entity* entity : scene->entities) {
        scene->shader.bind();
        scene->shader.setUniformMat4("u_model", entity->model);
        //scene->shader.setUniformVec3("u_baseColour", entity->colour);
        render(&entity->ibo, &entity->vao, &scene->shader);
    }
}

void Cork::Renderer::renderOverlay(Overlay* overlay) {
    GLCall(glDisable(GL_DEPTH_TEST));
    
    for (Quad* quad : overlay->quads) {
        if (quad->texture == nullptr) {
            overlay->currentShader->bind();
            overlay->currentShader->setUniformMat4("u_model", quad->model);
            overlay->currentShader->setUniformVec3("u_baseColour", quad->colour);
        } else {
            overlay->textureShader.bind();
            quad->texture->bind(0);
            overlay->textureShader.setUniformMat4("u_model", quad->model);
            overlay->textureShader.setUniform1i("u_texture", 0);  
        }
        
        render(&quad->ibo, &quad->vao, overlay->currentShader);
    }
}