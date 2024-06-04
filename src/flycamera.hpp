#ifndef FLYCAMERA_HPP
#define FLYCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

// Definition of a FlyCamera class
class FlyCamera
{
public:
	// Constructors
	FlyCamera() {} // Default constructor
	FlyCamera(float width, float height) : width(width), height(height)
	{
		this->AspectRatio = width / height;
	}

public:
	// Public member variables
	float width;			  // Width of the viewport
	float height;			  // Height of the viewport
	float Speed = 1;		  // Movement speed of the camera
	float Sensitivity = 0.2f; // Mouse sensitivity for camera rotation

	// Camera vectors
	glm::vec3 Location{0.0f, 0.0f, 5.0f};	// Camera position
	glm::vec3 Direction{0.0f, 0.0f, -1.0f}; // Camera forward direction
	glm::vec3 Up{0.0f, 1.0f, 0.0f};			// Camera up direction

	// Camera parameters
	float FieldOfView = glm::radians(45.0f); // Field of view in radians
	float AspectRatio;						 // Aspect ratio of the viewport
	float Near = 0.01f;						 // Near clipping plane
	float Far = 1000.0f;					 // Far clipping plane

public:
	// Camera movement methods
	void moveForward(float amount)
	{
		this->Location += glm::normalize(Direction) * amount * Speed;
	}

	void moveBack(float amount)
	{
		this->Location += glm::normalize(Direction) * amount * Speed;
	}

	void moveRight(float amount)
	{
		glm::vec3 Right = glm::normalize(glm::cross(Direction, Up));
		this->Location += Right * amount * Speed;
	}

	void moveLeft(float amount)
	{
		glm::vec3 Left = glm::normalize(glm::cross(Direction, Up));
		this->Location += Left * amount * Speed;
	}

	void moveUp(float amount)
	{
		this->Location -= Up * amount * Speed;
	}

	void moveDown(float amount)
	{
		this->Location += Up * amount * Speed;
	}

	// Camera rotation method
	void lookAt(float yawAmount, float pitchAmount)
	{
		// Adjust sensitivity
		yawAmount *= Sensitivity;
		pitchAmount *= Sensitivity;

		// Create an identity matrix
		const glm::mat4 IdentityMatrix = glm::identity<glm::mat4>();

		// Calculate the right vector, perpendicular to both the camera direction and up vector
		glm::vec3 Right = glm::normalize(glm::cross(Direction, Up));

		// Apply yaw rotation around the up vector
		glm::mat4 YawRotationMatrix = glm::rotate(IdentityMatrix, glm::radians(yawAmount), Up);

		// Apply pitch rotation around the right vector
		glm::mat4 PitchRotationMatrix = glm::rotate(IdentityMatrix, glm::radians(pitchAmount), Right);

		// Update the up vector by applying pitch rotation
		this->Up = PitchRotationMatrix * glm::vec4{this->Up, 0.0f};

		// Update the camera direction by applying both yaw and pitch rotations
		this->Direction = YawRotationMatrix * PitchRotationMatrix * glm::vec4{this->Direction, 0.0f};
	}

	// Calculates and returns the view-projection matrix for the camera.
	glm::mat4 GetViewProjection() const
	{
		// View matrix represents the camera's orientation and position in the world
		// It is created using the camera's location, the point it's looking at (Direction),
		// and the up direction (Up).
		glm::mat4 View = glm::lookAt(Location, Location + Direction, Up);

		// Projection matrix simulates the perspective of the camera.
		// It is created using the camera's field of view, aspect ratio, and clipping planes (Near and Far).
		glm::mat4 Projection = glm::perspective(FieldOfView, AspectRatio, Near, Far);

		// The final view-projection matrix is obtained by multiplying the projection matrix by the view matrix.
		return Projection * View;
	}
};

#endif