#pragma once

#include "camera.h"
#include "engine/window.h"
#include "engine/scene.h"
#include "entity/mesh.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_inverse.hpp>

namespace Cork {

    inline std::optional<glm::vec3> screenPointToWorld(glm::ivec2 coord, Cork::Window* window, Cork::Scene* scene, Cork::Camera* camera, Cork::Mesh* mesh) {
        // Normalized device coordinates
        float x = (2.0f * coord.x) / window->WIN_W - 1.0f;
        float y = 1.0f - (2.0f * coord.y) / window->WIN_H; // flip Y

        // Clip space
        glm::vec4 clip = glm::vec4(x, y, -1.0f, 1.0f);

        // Eye space
        glm::vec4 eye = glm::inverse(scene->projection) * clip;
        eye = glm::vec4(eye.x, eye.y, -1.0f, 0.0f);

        // World space
        glm::vec3 world = glm::vec3(glm::inverse(camera->view) * eye);

        return mesh->rayIntersect(camera->pos, glm::normalize(world));
    }

};