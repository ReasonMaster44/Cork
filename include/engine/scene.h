#pragma once

#include "engine/window.h"
#include "entity/entity.h"
#include "opengl/shader.h"
#include "camera.h"

#include "glm/glm.hpp"

#include <vector>

namespace Cork {

struct Scene {
    Window* window;
    Camera* camera;

    Shader shader;

    glm::mat4 projection;
    
    std::vector<Entity*> entities;

    glm::vec3 lightPos;
    glm::vec3 lightFacing;
    glm::mat4 lightView;
    glm::mat4 lightProjection;

    Scene(Window* window, Camera* camera, glm::vec3 lightPos, glm::vec3 lightFacing);

    void add(Entity* newEntity);

    void startFrame();

    void endFrame();
};

}