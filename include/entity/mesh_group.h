#include "cork.h"

template <typename T>
struct MeshGroup {
    std::vector<T> meshes;

    MeshGroup();

    template <typename... Args>
    void add(Args&&... args);
};