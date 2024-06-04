#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <cassert>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "flycamera.hpp"
#include "geometry_object.hpp"

// Utility class containing static methods for common operations such as file reading,
// shader compilation checking, shader program linking, and rendering using OpenGL.

class Utils
{
public:
	// Reads the contents of a file and returns it as a string.
	static std::string Read_file(const char *path)
	{
		std::string data_file;

		// Open the file stream for reading
		if (std::ifstream FileStream{path, std::ios::in})
		{
			// Read the entire file into the string
			data_file.assign(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
		}
		return data_file;
	}

	// Checks the compilation status of a shader and prints the log if compilation fails.
	static void CheckShader(GLuint ShaderId)
	{
		GLint result = GL_TRUE;

		// Get the compilation status of the shader
		glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &result);

		// If compilation fails, print the error log
		if (result == GL_FALSE)
		{
			GLint log_size = 0;
			glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &log_size);

			if (log_size > 0)
			{
				std::string textoLog(log_size, '\0');
				glGetShaderInfoLog(ShaderId, log_size, nullptr, &textoLog[0]);

				std::cout << "Shader Error:" << std::endl;
				std::cout << textoLog << std::endl;

				assert(false);
			}
		}
	}

	// Loads and compiles vertex and fragment shaders, links them into a program,
	// and returns the program ID.
	static GLuint LoadShaders(const char *VertexShaderFile, const char *FragmentShaderFile)
	{
		std::string VertexShaderSource = Read_file(VertexShaderFile);
		std::string FragmentShaderSource = Read_file(FragmentShaderFile);

		// Ensure shader source is not empty
		assert(!VertexShaderSource.empty());
		assert(!FragmentShaderSource.empty());

		// Create shader objects
		GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		// Load shader source, compile, and check for errors
		const char *VertexShaderSourcePtr = VertexShaderSource.c_str();
		glShaderSource(VertexShaderId, 1, &VertexShaderSourcePtr, nullptr);
		glCompileShader(VertexShaderId);
		CheckShader(VertexShaderId);

		// Load fragment shader source, compile, and check for errors
		const char *FragmentShaderPtr = FragmentShaderSource.c_str();
		glShaderSource(FragmentShaderId, 1, &FragmentShaderPtr, nullptr);
		glCompileShader(FragmentShaderId);
		CheckShader(FragmentShaderId);

		// Create shader program, attach shaders, link, and check for errors
		GLuint ProgramaId = glCreateProgram();
		glAttachShader(ProgramaId, VertexShaderId);
		glAttachShader(ProgramaId, FragmentShaderId);
		glLinkProgram(ProgramaId);

		GLint Result = GL_TRUE;
		glGetProgramiv(ProgramaId, GL_LINK_STATUS, &Result);

		if (Result == GL_FALSE)
		{
			GLint tamanhoLog = 0;
			glGetProgramiv(ProgramaId, GL_INFO_LOG_LENGTH, &tamanhoLog);

			if (tamanhoLog > 0)
			{
				std::string textoLog(tamanhoLog, '\0');
				glGetProgramInfoLog(ProgramaId, tamanhoLog, nullptr, &textoLog[0]);

				std::cout << "Program Error:" << std::endl;
				std::cout << textoLog << std::endl;

				assert(false);
			}
		}

		// Detach and delete shaders as they are no longer needed
		glDetachShader(ProgramaId, VertexShaderId);
		glDetachShader(ProgramaId, FragmentShaderId);
		glDeleteShader(VertexShaderId);
		glDeleteShader(FragmentShaderId);

		return ProgramaId;
	};

	// Renders a 3D object using OpenGL and GLFW, using the provided shader program,
	// texture ID, camera, and object vertices.
	template <std::size_t SIZE>
	static void Show(std::array<My_vertex, SIZE> &object, GLFWwindow *window, GLuint ProgramaId, GLuint TexturaId, FlyCamera *camera)
	{
		// Initialize model matrix and vertex buffer
		glm::mat4 MatrizModel = glm::identity<glm::mat4>();
		GLuint VertexBuffer;
		glGenBuffers(1, &VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(object), object.data(), GL_STATIC_DRAW);

		// Set clear color and initialize frame time variables
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		double TempoAtualizadoFrameAnterior = glfwGetTime();

	
		// Render loop
		while (!glfwWindowShouldClose(window))
		{
			// Calculate delta time for smooth animation
			double TempoAtualizadoFrameAtual = glfwGetTime();
			double DeltaTime = TempoAtualizadoFrameAtual - TempoAtualizadoFrameAnterior;
			if (DeltaTime > 0)
			{
				TempoAtualizadoFrameAnterior = TempoAtualizadoFrameAtual;
			}

			// Clear the screen and enable depth testing
			glClear(GL_COLOR_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Use the shader program
			glUseProgram(ProgramaId);

			// Calculate MVP matrix and set it as a uniform in the shader
			glm::mat4 MatrizViewProjection = camera->GetViewProjection();
			glm::mat4 ModelViewProjection = MatrizViewProjection * MatrizModel;
			GLint ModelViewProjectionLoc = glGetUniformLocation(ProgramaId, "ModelViewProjection");
			glUniformMatrix4fv(ModelViewProjectionLoc, 1, GL_FALSE, glm::value_ptr(ModelViewProjection));

			// Activate texture unit and bind the texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, TexturaId);

			// Set texture sampler uniform in the shader
			GLint TextureSamplerLoc = glGetUniformLocation(ProgramaId, "TextureSampler");
			glUniform1i(TextureSamplerLoc, 0);

			// Enable vertex attributes and bind vertex buffer
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

			// Specify vertex attribute pointers
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(My_vertex), nullptr);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(My_vertex),
								  reinterpret_cast<void *>(offsetof(My_vertex, Cor)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(My_vertex),
								  reinterpret_cast<void *>(offsetof(My_vertex, UV)));

			// Draw the object
			glDrawArrays(GL_TRIANGLES, 0, object.size());

			// Disable vertex attributes and reset state
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glUseProgram(0);

			// Poll for events, swap buffers, and handle camera movement
			glfwPollEvents();
			glfwSwapBuffers(window);

			// Handle camera movement based on keyboard input
			if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			{
				camera->moveForward(1.0f * DeltaTime);
			}
			if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
			{
				camera->moveBack(-1.0f * DeltaTime);
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				camera->moveLeft(1.0f * DeltaTime);
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				camera->moveRight(-1.0f * DeltaTime);
			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				camera->moveUp(1.0f * DeltaTime);
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				camera->moveDown(1.0f * DeltaTime);
			}
		}

		// Clean up: delete vertex buffer
		glDeleteBuffers(1, &VertexBuffer);
	}
};

#endif