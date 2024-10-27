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

#include"Shader.h"

#include "io/Keyboard.h"
#include "io/Mouse.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600; 
float x, y, z;


int main() {

	int success;
	char infoLog[512];

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COPMPAT, GL_TRUEF);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Title", NULL, NULL);
	if (window == NULL) { // window not created
		std::cout << "Could not create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, Keyboard::keyCallBack);

	glfwSetCursorPosCallback(window, Mouse::cursorPosCallBack);
	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallBack);

	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

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
	

	x = 0.0f;
	y = 0.0f;
	z = 3.0f;

	while (!glfwWindowShouldClose(window)) {
		// process input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// create transformation for screen
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projecton = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f));
		view = glm::translate(view, glm::vec3(-x, -y, -z));
		projecton = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.activate();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projecton);

		// draw shapes
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// send new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VAO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void processInput(GLFWwindow* window) {
	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

	//if (Keyboard::key(GLFW_KEY_W)) {
	//	trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(1.0f, 0.0f, 0.0f));
	//}
	//if (Keyboard::key(GLFW_KEY_S)) {
	//	trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(-1.0f, 0.0f, 0.0f));
	//}
	//if (Keyboard::key(GLFW_KEY_A)) {
	//	trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(0.0f, 1.0f, 0.0f));
	//}
	//if (Keyboard::key(GLFW_KEY_D)) {
	//	trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(0.0f, -1.0f, 0.0f));
	//}
}