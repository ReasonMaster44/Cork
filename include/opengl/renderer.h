#include "opengl/shader.h"
#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

#include "engine/scene.h"
#include "engine/overlay.h"

namespace Cork {

struct Renderer {
    void clear();

    void render(IBO* ibo, VAO* vao, Shader* shader);

    void renderScene(Scene* scene);

    void renderOverlay(Overlay* overlay);
};

}