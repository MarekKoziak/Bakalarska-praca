#include "gui/Mygui.h"

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

#include "graphics/models/Cordinates.hpp"
#include "graphics/models/ProjectivePlane.hpp"
#include "graphics/models/Arrow.hpp"
#include "graphics/models/Cube1.hpp"
#include "graphics/models/Cube2.hpp"
#include "graphics/models/Ray.hpp"


#include "io/Keyboard.h"
#include "io/Mouse.h"
#include "io/Camera.h"
#include "io/Screen.h"

Screen screen;
Camera camera(glm::vec3(0.0f, 0.2f, 4.0f));

void processInput(double dt);
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

	Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
	Shader shaderTransparency("assets/shaders/transparentObject.vs", "assets/shaders/transparentObject.fs");

	glm::vec3 planeSize(2.0f, 2.0f, 1.0f);

	Cordinates cordinates(glm::vec3(2.0f));
	ProjectivePlane plane(planeSize, 0.35f);
	Arrow arrow(glm::vec3(0.5f));
	Cube1 cube1(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.041f));
	Cube2 cube2(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.041f));
	Ray ray(glm::vec3(1.0f));


	MyGui::init(screen.getWindow());


	while (!screen.shouldClose()) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// process input
		processInput(deltaTime);
		
		// update frame
		screen.update();

		// create transformation for screen
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)screen.SCR_WIDTH / (float)screen.SCR_HEIGHT, 0.1f, 100.0f);

		shaderTransparency.activate();
		shaderTransparency.setMat4("view", view);
		shaderTransparency.setMat4("projection", projection);

		shader.activate();
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		//render shapes
		shader.activate();
		cordinates.render(shader);
		cube1.updateposition();
		cube2.updatePosition();
		cube2.render(shader);
		if (cube1.pos.x > plane.border.x || cube1.pos.x < -plane.border.x || cube1.pos.y > plane.border.y || cube1.pos.y < -plane.border.y) {
			arrow.render(shader, cube2.pos, plane.border);
		}else {
			cube1.render(shader);
			ray.render(shader, cube1.pos, cube2.pos);
		}

		shaderTransparency.activate();
		plane.render(shaderTransparency);

		MyGui::show();

		// send new frame to window
		screen.newFrame();
	}

	cordinates.cleanup();
	plane.cleanup();
	cube1.cleanup();
	cube2.cleanup();
	ray.cleanup();
	arrow.cleanup();
	MyGui::cleanup();

	glfwTerminate();
	return 0;
}



void processInput(double dt) {
	if (!MyGui::keyboardInput()) {
		// camera
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



		if (Keyboard::key(GLFW_KEY_R)) {
			camera.reset();
		}
	}

	if (!MyGui::mouseInput()) {		//checks if input is used by GUI, if yes input is ignored by application
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

	camera.sensitivity = MyGui::mouseSnesitivity;
	camera.speed = MyGui::cameraSpeed;
}