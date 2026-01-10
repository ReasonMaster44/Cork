#pragma once

#include "engine/window.h"
#include "entity/entity.h"
#include "opengl/shader.h"
#include "opengl/shadow_map.h"
#include "opengl/framebuffer.h"

#include "camera.h"
#include "post_process_pass.h"

#include "glm/glm.hpp"

#include <vector>

namespace Cork {

struct Scene {
    Cork::Window* window;
    Cork::Camera* camera;

    std::vector<Cork::PostProcessPass*> postProcessPasses;

    Cork::Shader shader;
    Cork::Shader shadowMapShader;

    glm::mat4 projection;
    glm::mat4 lightOrthogonalProjection;
    
    std::vector<Cork::Entity*> entities;

    glm::vec3 lightPos;
    glm::vec3 lightFacing;
    glm::mat4 lightView;
    glm::mat4 lightProjection;

    Cork::ShadowMap shadowMap;

    Scene(Cork::Window* window, Cork::Camera* camera, glm::vec3 lightPos, glm::vec3 lightFacing);

    void add(Cork::Entity* newEntity);

    void startFrame();

    void endFrame();

    void updateLightProjection();

    void addPostProcessPass(Cork::PostProcessPass* postProcessPass);
};

}