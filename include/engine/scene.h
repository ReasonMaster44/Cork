#pragma once

#include "engine/window.h"
#include "entity/entity.h"
#include "opengl/shader.h"
#include "opengl/shadow_map.h"

#include "camera.h"


#include "glm/glm.hpp"

#include <vector>

namespace Cork {

struct Scene {
    Window* window;
    Camera* camera;

    Shader shader;
    Shader shadowMapShader;

    glm::mat4 projection;
    glm::mat4 lightOrthogonalProjection;
    
    std::vector<Entity*> entities;

    glm::vec3 lightPos;
    glm::vec3 lightFacing;
    glm::mat4 lightView;
    glm::mat4 lightProjection;

    ShadowMap shadowMap;

    Scene(Window* window, Camera* camera, glm::vec3 lightPos, glm::vec3 lightFacing);

    void add(Entity* newEntity);

    void startFrame();

    void endFrame();

    void updateLightProjection();
};

}