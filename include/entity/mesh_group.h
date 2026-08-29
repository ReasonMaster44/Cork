#pragma once

#include <vector>

namespace Cork {

template <typename T>
struct MeshGroup {
    std::vector<T> meshes;

    MeshGroup();

    template <typename... Args>
    void add(Args&&... args);
};

template <typename T>
Cork::MeshGroup<T>::MeshGroup() {}

template <typename T>
template <typename... Args>
void MeshGroup<T>::add(Args&&... args) {
    meshes.emplace_back(std::forward<Args>(args)...);
}

}