#pragma once

#include "opengl/shader.h"
#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

#include "engine/scene.h"
#include "engine/overlay.h"
#include "engine/window.h"

#include "entity/quad.h"

namespace Cork {

struct Renderer {
    Cork::Quad shadowMapDebugQuad;
    Cork::Quad framebufferQuad;

    Cork::Shader shadowMapDebugShader;

    Renderer(Cork::Window* window);

    void clear();

    void render(Cork::IBO* ibo, Cork::VAO* vao, Cork::Shader* shader);

    void renderShadowMap(Cork::Scene* scene);

    void renderShadowMapDebug(Scene* scene);

    void renderScene(Cork::Scene* scene);

    void renderMeshes(Cork::Scene* scene);

    void renderPostProcessPass(Cork::Scene* scene, int frameBufferIndex, int textureSlot);

    void renderOverlay(Cork::Overlay* overlay);

    
};

}