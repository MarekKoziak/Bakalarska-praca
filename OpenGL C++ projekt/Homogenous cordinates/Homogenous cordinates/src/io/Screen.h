#ifndef SCREEN_H
#define SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Screen {
public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void framebufferSizeCallBack(GLFWwindow* window, int width, int height);

	Screen();

	bool init();

	void setParameters();

	GLFWwindow* getWindow();

	// main loop
	void update();
	void newFrame();

	// window closing accessors and modifieres
	bool shouldClose();
	void setShouldClose(bool shouldClose);

private:
	GLFWwindow* window;
};

#endif
