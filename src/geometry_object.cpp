#include "geometry_object.hpp"

// generates vertices for a cube and returns an array of My_vertex containing 36 vertices
std::array<My_vertex, 36> generateCube()
{
    // Define colors for each triangle
    glm::vec3 blue{0.0f, 0.0f, 1.0f};
    glm::vec3 magenta{1.0f, 0.0f, 1.0f};
    glm::vec3 red{1.0f, 0.0f, 0.0f};
    glm::vec3 yellow{1.0f, 1.0f, 0.0f};
    glm::vec3 green{0.0f, 1.0f, 0.0f};
    glm::vec3 turquoise{0.0f, 1.0f, 1.0f};
    glm::vec3 black{0.0f, 0.0f, 0.0f};

    return std::array<My_vertex, 36>{
        // Front face of the cube
        // Triangle 1
        My_vertex{glm::vec3{-1.0f, 1.0f, 1.0f}, blue, glm::vec2{0.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, -1.0f, 1.0f}, magenta, glm::vec2{0.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, -1.0f, 1.0f}, red, glm::vec2{1.0f, 1.0f}},
        // Triangle 2
        My_vertex{glm::vec3{1.0f, -1.0f, 1.0f}, yellow, glm::vec2{1.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, 1.0f, 1.0f}, green, glm::vec2{1.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, 1.0f, 1.0f}, turquoise, glm::vec2{0.0f, 0.0f}},
        // Back face of the cube
        // Triangle 1
        My_vertex{glm::vec3{-1.0f, 1.0f, -1.0f}, black, glm::vec2{0.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, -1.0f, -1.0f}, blue, glm::vec2{0.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, -1.0f, -1.0f}, magenta, glm::vec2{1.0f, 1.0f}},
        // Triangle 2
        My_vertex{glm::vec3{1.0f, -1.0f, -1.0f}, red, glm::vec2{1.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, 1.0f, -1.0f}, yellow, glm::vec2{1.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, 1.0f, -1.0f}, green, glm::vec2{0.0f, 0.0f}},
        // Bottom face of the cube
        // Triangle 1
        My_vertex{glm::vec3{-1.0f, -1.0f, -1.0f}, turquoise, glm::vec2{0.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, -1.0f, 1.0f}, black, glm::vec2{0.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, -1.0f, -1.0f}, blue, glm::vec2{1.0f, 1.0f}},
        // Triangle 2
        My_vertex{glm::vec3{1.0f, -1.0f, 1.0f}, magenta, glm::vec2{1.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, -1.0f, -1.0f}, red, glm::vec2{1.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, -1.0f, 1.0f}, yellow, glm::vec2{0.0f, 0.0f}},
        // Top face of the cube
        // Triangle 1
        My_vertex{glm::vec3{-1.0f, 1.0f, -1.0f}, green, glm::vec2{0.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, 1.0f, 1.0f}, turquoise, glm::vec2{0.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, 1.0f, -1.0f}, black, glm::vec2{1.0f, 1.0f}},
        // Triangle 2
        My_vertex{glm::vec3{1.0f, 1.0f, 1.0f}, blue, glm::vec2{1.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, 1.0f, -1.0f}, magenta, glm::vec2{1.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, 1.0f, 1.0f}, red, glm::vec2{0.0f, 0.0f}},
        // Right face of the cube
        // Triangle 1
        My_vertex{glm::vec3{1.0f, 1.0f, -1.0f}, yellow, glm::vec2{0.0f, 0.0f}},
        My_vertex{glm::vec3{1.0f, 1.0f, 1.0f}, green, glm::vec2{0.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, -1.0f, 1.0f}, turquoise, glm::vec2{1.0f, 1.0f}},
        // Triangle 2
        My_vertex{glm::vec3{1.0f, -1.0f, 1.0f}, black, glm::vec2{1.0f, 1.0f}},
        My_vertex{glm::vec3{1.0f, -1.0f, -1.0f}, blue, glm::vec2{1.0f, 0.0f}},
        My_vertex{glm::vec3{1.0f, 1.0f, -1.0f}, magenta, glm::vec2{0.0f, 0.0f}},
        // Left face of the cube
        // Triangle 1
        My_vertex{glm::vec3{-1.0f, 1.0f, -1.0f}, red, glm::vec2{0.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, 1.0f, 1.0f}, yellow, glm::vec2{0.0f, 1.0f}},
        My_vertex{glm::vec3{-1.0f, -1.0f, 1.0f}, green, glm::vec2{1.0f, 1.0f}},
        // Triangle 2
        My_vertex{glm::vec3{-1.0f, -1.0f, 1.0f}, turquoise, glm::vec2{1.0f, 1.0f}},
        My_vertex{glm::vec3{-1.0f, -1.0f, -1.0f}, black, glm::vec2{1.0f, 0.0f}},
        My_vertex{glm::vec3{-1.0f, 1.0f, -1.0f}, blue, glm::vec2{0.0f, 0.0f}},
    };
}