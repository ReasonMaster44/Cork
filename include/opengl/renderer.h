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
    Quad shadowMapDebugQuad;
    Cork::Shader shadowMapDebugShader;

    Renderer(Window* window);

    void clear();

    void render(IBO* ibo, VAO* vao, Shader* shader);

    void renderShadowMap(Scene* scene);

    void renderShadowMapDebug(Scene* scene);

    void renderScene(Scene* scene);

    void renderOverlay(Overlay* overlay);
};

}