#include "Screen.h"

#include "Keyboard.h"
#include "Mouse.h"

unsigned int Screen::SCR_WIDTH = 800;
unsigned int Screen::SCR_HEIGHT = 600;

void Screen::framebufferSizeCallBack(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

Screen::Screen()
	: window(nullptr) {}

bool Screen::init() {
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Homogenous cordinates demonstration", NULL, NULL);
	if (!window) {
		// window not created
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}

void Screen::setParameters() {
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, Screen::framebufferSizeCallBack);

	glfwSetKeyCallback(window, Keyboard::keyCallBack);

	glfwSetCursorPosCallback(window, Mouse::cursorPosCallBack);
	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallBack);
}

void Screen::update() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::newFrame() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Screen::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Screen::setShouldClose(bool shouldClose) {
	glfwSetWindowShouldClose(window, shouldClose);
}