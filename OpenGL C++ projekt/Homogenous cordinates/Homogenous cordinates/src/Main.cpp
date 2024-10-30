#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/Shader.h"

#include "io/Keyboard.h"
#include "io/Mouse.h"
#include "io/Camera.h"
#include "io/Screen.h"

void processInput(double dt);

Screen screen;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COPMPAT, GL_TRUEF);
#endif

	if (!screen.init()) { // window not created
		std::cout << "Could not create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	screen.setParameters();

	Shader shader("assets/object.vs", "assets/object.fs");

	// vertex array
	float vertices[] = {
		// positions			colors
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 1.0f
	};


	// VAO, VBO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind VAO
	glBindVertexArray(VAO);

	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set attribute pointer
	// positon
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	


	while (!screen.shouldClose()) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// process input
		processInput(deltaTime);

		// render
		screen.update();

		// create transformation for screen
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projecton = glm::mat4(1.0f);

		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f));
		view = camera.getViewMatrix();
		projecton = glm::perspective(glm::radians(camera.getZoom()), (float)screen.SCR_WIDTH / (float)screen.SCR_HEIGHT, 0.1f, 100.0f);

		shader.activate();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projecton);

		// draw shapes
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// send new frame to window
		screen.newFrame();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VAO);

	glfwTerminate();
	return 0;
}

void processInput(double dt) {
	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		screen.setShouldClose(true);
	}

	// move camera
	if (Keyboard::key(GLFW_KEY_W)) {
		camera.updateCameraPos(CameraDirection::FORWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		camera.updateCameraPos(CameraDirection::BACKWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_A)) {
		camera.updateCameraPos(CameraDirection::LEFT, dt);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		camera.updateCameraPos(CameraDirection::RIGHT, dt);
	}
	if (Keyboard::key(GLFW_KEY_SPACE)) {
		camera.updateCameraPos(CameraDirection::UP, dt);
	}
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
		camera.updateCameraPos(CameraDirection::DOWN, dt);
	}

	if (Mouse::button(GLFW_MOUSE_BUTTON_2)) {
		double dx = Mouse::getDX(), dy = Mouse::getDY();
		if (dx != 0 || dy != 0) {
			camera.updateCameraDirecion(dx, dy);
		}
	}

	double scrollDY = Mouse::getScrollDY();
	if (scrollDY != 0) {
		camera.updateCameraZoom(scrollDY);
	}
}