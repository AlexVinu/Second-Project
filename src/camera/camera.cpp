#include "camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch) :Front(glm::vec3(0.0f, 0.0f, -1.0f)), camera_speed(5.0f), sensetivity(0.1f), fov(45.0f)
{
	this->Position = pos;
	this->WorldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->update_vectors();
}

Camera::Camera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat up_x, GLfloat up_y, GLfloat up_z, GLfloat yaw, GLfloat pitch) :Front(glm::vec3(0.0f, 0.0f, -1.0f)), camera_speed(1.0f), sensetivity(1.0f), fov(45.0f)
{
	this->Position = glm::vec3(pos_x, pos_y, pos_z);
	this->WorldUp = glm::vec3(up_x, up_y, up_z);
	this->yaw = yaw;
	this->pitch = pitch;
	this->update_vectors();
}

void Camera::keyboard_move(GLfloat delta_time, bool massiv[])
{
	GLfloat cam_speed = camera_speed * delta_time;
	if (massiv[GLFW_KEY_W]) {
		Position += cam_speed * Front_for_move;
	}
	if (massiv[GLFW_KEY_S]) {
		Position -= cam_speed * Front_for_move;
	}
	if (massiv[GLFW_KEY_D]) {
		Position += Right * cam_speed;
	}
	if (massiv[GLFW_KEY_A]) {
		Position -= Right * cam_speed;
	}
}

void Camera::mouse_move(GLfloat xoffset, GLfloat yoffset)
{	
	xoffset *= sensetivity;
	yoffset *= sensetivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	update_vectors();
}

void Camera::mouse_scroll( double yoffset)
{
	if (this->fov >= 1.0f && this->fov <= 45.0f) {
		this->fov -= yoffset;
	}
	if (this->fov <= 1.0f) {
		this->fov = 1.0f;
	}
	if (this->fov >= 45.0f) {
		this->fov = 45.0f;
	}
}

void Camera::update_vectors()
{	
	glm::vec3 front_for_move;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	Front = glm::normalize(front);
	Right = glm::vec3(glm::normalize(glm::cross(Front, WorldUp)));
	Up = glm::vec3(glm::normalize(glm::cross(Right, Front)));

	front_for_move.x = cos(glm::radians(yaw));
	front_for_move.y = Position.y;
	front_for_move.z = sin(glm::radians(yaw));

	Front_for_move = glm::normalize(front_for_move);
}