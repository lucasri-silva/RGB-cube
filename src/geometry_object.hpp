#ifndef GEOMETRY_OBJECT_HPP
#define GEOMETRY_OBJECT_HPP

#include <array>
#include <glm/glm.hpp>

// Definition of a structure representing a vertex with position, color, and texture coordinates
struct My_vertex
{
    glm::vec3 Posicao;  // Position of the vertex in 3D space
    glm::vec3 Cor;      // Color of the vertex
    glm::vec2 UV;       // Texture coordinates of the vertex
};

// Function prototype to generate vertices for a cube and return them as an array
std::array<My_vertex, 36> generateCube();

#endif