#include "entity/mesh_group.h"

template <typename T>
MeshGroup<T>::MeshGroup() {
}

template <typename T>
template <typename... Args>
void MeshGroup<T>::add(Args&&... args) {
    meshes.emplace_back(std::forward<Args>(args)...);
}