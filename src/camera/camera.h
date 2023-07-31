#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Front_for_move;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat fov;

	GLfloat camera_speed;
	GLfloat sensetivity;

	Camera(Camera&) = delete;
	Camera(Camera&&) = delete;

	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);//vectors constructor
	Camera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat up_x, GLfloat up_y, GLfloat up_z, GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);//scalar constructor
	void keyboard_move(GLfloat delta_time, bool massiv[]);
	void mouse_move(GLfloat xoffset, GLfloat yoffset);
	void mouse_scroll( double yoffset);
	glm::mat4 viewMatrix() { return glm::lookAt(Position, Position + Front, Up); }

	~Camera() {}
private:
	void update_vectors();
};