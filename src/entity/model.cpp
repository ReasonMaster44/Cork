#include "entity/model.h"
#include "entity/mesh.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>

Cork::Vertex::Vertex(glm::vec3 pos, glm::vec3 norm) : pos(pos), norm(norm) {}


Cork::Model::Model(std::string objFilePath, glm::vec3 pos, glm::vec3 scale, glm::vec3 colour) 
    : Mesh(pos, scale, colour) {

    std::ifstream file(objFilePath);
    std::string line;

    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec3> vertexNormals;
    std::vector<unsigned int> positionIndices;
    std::vector<unsigned int> normalIndices;

    unsigned int firstSpaceIndex;
    unsigned int secondSpaceIndex;

    while (std::getline(file, line)) {
        // Vertex positions:
        if (line.substr(0, 2) == "v ") {
            firstSpaceIndex = line.find(" ", 2);
            secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);

            float x = std::stof(line.substr(2, firstSpaceIndex - 2));
            float y = std::stof(line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1));
            float z = std::stof(line.substr(secondSpaceIndex + 1));

            vertexPositions.push_back(glm::vec3(x, y, z));

        } else if (line.substr(0, 2) == "f ") { // Indices:
            firstSpaceIndex = line.find(" ", 2);
            secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);

            std::string v1 = line.substr(2, firstSpaceIndex - 2);
            std::string v2 = line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
            std::string v3 = line.substr(secondSpaceIndex + 1);

            unsigned int positionIndex1 = std::stoul(v1.substr(0, v1.find("/"))) - 1;
            unsigned int positionIndex2 = std::stoul(v2.substr(0, v2.find("/"))) - 1;
            unsigned int positionIndex3 = std::stoul(v3.substr(0, v3.find("/"))) - 1;

            positionIndices.push_back(positionIndex1);
            positionIndices.push_back(positionIndex2);
            positionIndices.push_back(positionIndex3);

            unsigned int normalIndex1 = std::stoul(v1.substr(v1.find("/", v1.find("/") + 1) + 1)) - 1;
            unsigned int normalIndex2 = std::stoul(v2.substr(v2.find("/", v2.find("/") + 1) + 1)) - 1;
            unsigned int normalIndex3 = std::stoul(v3.substr(v3.find("/", v3.find("/") + 1) + 1)) - 1;

            //std::cout << normalIndex1 << ", " << normalIndex2 << ", " << normalIndex3 << std::endl;
            
            normalIndices.push_back(normalIndex1);
            normalIndices.push_back(normalIndex2);
            normalIndices.push_back(normalIndex3);

        } else if (line.substr(0, 3) == "vn ") {
            firstSpaceIndex = line.find(" ", 3);
            secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);

            float x = std::stof(line.substr(2, firstSpaceIndex - 2));
            float y = std::stof(line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1));
            float z = std::stof(line.substr(secondSpaceIndex + 1));
            
            glm::vec3 norm(x, y, z);
            
            norm /= 2.0f;
            norm += 0.5f;
            //norm = abs(norm);
            //std::cout << norm.x << " " << norm.y << " " << norm.z << std::endl;

            vertexNormals.push_back(norm);
        }
    }

    std::vector<float> vertexDataCombined;
    
    for (int i = 0; i < normalIndices.size(); i++) {
        glm::vec3 pos = vertexPositions[positionIndices[i]];

        vertexDataCombined.push_back(pos.x);
        vertexDataCombined.push_back(pos.y);
        vertexDataCombined.push_back(pos.z);

        glm::vec3 norm = vertexNormals[normalIndices[i]];

        vertexDataCombined.push_back(norm.x);
        vertexDataCombined.push_back(norm.y);
        vertexDataCombined.push_back(norm.z);
    }

    unsigned int indices[positionIndices.size()];
    for (int i = 0; i < positionIndices.size(); i++) { indices[i] = i; }

    vbo = VBO(vertexDataCombined.data(), sizeof(float) * vertexDataCombined.size());
    ibo = IBO(indices, sizeof(indices));

    unsigned int layout[] = {3, 3};
    vbo.bind();
    vao = VAO(layout, 2);

    update();
}