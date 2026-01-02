#include "opengl/renderer.h"

#include "opengl/shader.h"
#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"
#include "opengl/glerrorhandler.h"

#include "engine/scene.h"
#include "engine/overlay.h"

#include "entity/entity.h"

void Cork::Renderer::clear() {
    GLCall(glClearColor(0.105f, 0.12f, 0.13f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Cork::Renderer::render(IBO* ibo, VAO* vao, Shader* shader) {
    vao->bind();
    ibo->bind();

    GLCall(glDrawElements(GL_TRIANGLES, ibo->count, GL_UNSIGNED_INT, 0));
}

void Cork::Renderer::renderScene(Scene* scene) {
    GLCall(glEnable(GL_DEPTH_TEST));

    for (Entity* entity : scene->entities) {
        scene->shader.bind();
        scene->shader.setUniformMat4("u_model", entity->model);
        scene->shader.setUniformVec3("u_baseColour", entity->colour);
        render(&entity->ibo, &entity->vao, &scene->shader);
    }
}

void Cork::Renderer::renderOverlay(Overlay* overlay) {
    GLCall(glDisable(GL_DEPTH_TEST));
    
    for (Quad* quad : overlay->quads) {
        if (quad->texture == nullptr) {
            overlay->shader.bind();
            overlay->shader.setUniformMat4("u_model", quad->model);
            overlay->shader.setUniformVec3("u_baseColour", quad->colour);
        } else {
            overlay->textureShader.bind();
            quad->texture->bind(0);
            overlay->textureShader.setUniformMat4("u_model", quad->model);
            overlay->textureShader.setUniform1i("u_texture", 0);  
        }

        render(&quad->ibo, &quad->vao, &overlay->shader);
    }
}
