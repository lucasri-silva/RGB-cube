#include "flycamera.hpp"
#include "utils.hpp"
#include "geometry_object.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Define the width and height of the window
const int Width = 1000;
const int Height = 800;

// Create an instance of FlyCamera with the specified width and height
FlyCamera Camera = FlyCamera(Width, Height);

// Store the previous cursor position for mouse movement
glm::vec2 PreviousCursorPosition;
bool EnableMouseMovement = false;

// GLFW callback function for mouse button events
void MouseButtonCallback(GLFWwindow *Window, int Button, int Action, int Modifiers)
{
    if (Button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (Action == GLFW_PRESS)
        {
            // Enable mouse cursor and capture it
            glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // Get initial cursor position
            double X, Y;
            glfwGetCursorPos(Window, &X, &Y);
            PreviousCursorPosition = glm::vec2{X, Y};

            EnableMouseMovement = true;
        }
        else if (Action == GLFW_RELEASE)
        {
            // Release mouse cursor
            glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            EnableMouseMovement = false;
        }
    }
}

// GLFW callback function for mouse motion events
void MouseMotionCallback(GLFWwindow *Window, double X, double Y)
{
    if (EnableMouseMovement)
    {
        // Calculate cursor movement delta
        glm::vec2 CurrentCursorPosition{X, Y};
        glm::vec2 Delta = PreviousCursorPosition - CurrentCursorPosition;

        // Update camera orientation based on mouse movement
        Camera.lookAt(-Delta.x, -Delta.y);

        PreviousCursorPosition = CurrentCursorPosition;
    }
}

// Function to render and display the 3D object using GLFW and OpenGL
template <std::size_t SIZE>
void view(std::array<My_vertex, SIZE> &object)
{
    // Initialize GLFW
    assert(glfwInit() == GLFW_TRUE);

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(Width, Height, "", nullptr, nullptr);
    assert(window);

    // Set GLFW callback functions
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MouseMotionCallback);

    // Make the OpenGL context of the window current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    int statusGlwInit = glewInit();
    std::cout << statusGlwInit << std::endl;
    assert(glewInit() == GLEW_OK);

    // Load shaders and create an OpenGL program
    GLuint ProgramId = Utils::LoadShaders("shaders/triangle_vert.glsl", "shaders/triangle_frag.glsl");

    // Create an OpenGL texture
    GLuint TextureId;

    // Show the 3D object using the provided utility function
    Utils::Show(object, window, ProgramId, TextureId, &Camera);

    // Terminate GLFW
    glfwTerminate();
}

// Main function
int main()
{
    // Generate a cube geometry
    std::array<My_vertex, 36> cube = generateCube();

    // Render and display the cube
    view(cube);

    return 0;
}
