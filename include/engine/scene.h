#pragma once

#include "engine/window.h"
#include "entity/mesh.h"
#include "entity/mesh_group.h"

#include "opengl/shader.h"
#include "opengl/shadow_map.h"
#include "opengl/framebuffer.h"

#include "camera.h"
#include "post_process_pass.h"
#include "post_processing_chain.h"
#include "light_source.h"

#include "glm/glm.hpp"

#include <vector>

namespace Cork {

struct Scene {
    Cork::Window* window;
    Cork::Camera* camera;
    int timeElapsed = 0;

    glm::mat4 projection;

    Cork::Shader shader;
    Cork::Shader debugShader;
    Cork::Shader shadowMapShader;

    std::vector<Cork::Mesh*> meshes;

    Cork::PostProcessingChain postProcessingChain;

    Cork::ShadowMap shadowMap;

    Cork::LightSource* light;

    Scene(Cork::Window* window, Cork::Camera* camera, Cork::LightSource* light);

    void add(Cork::Mesh* newMesh, Cork::Shader* customShader = nullptr);

    template <typename T>
    void add(Cork::MeshGroup<T>* newMeshGroup, Cork::Shader* customShader = nullptr);

    void remove(Cork::Mesh* mesh);

    void startFrame();

    void endFrame();

    void addPostProcessPass(std::string shaderFilePath);
};

template <typename T>
void Scene::add(Cork::MeshGroup<T>* meshGroup, Cork::Shader* customShader) {
    for (auto& mesh : meshGroup->meshes) {
        if (std::find(meshes.begin(), meshes.end(), &mesh) != meshes.end()) {
            continue;
        }
        meshes.push_back(&mesh);
    }
}

}