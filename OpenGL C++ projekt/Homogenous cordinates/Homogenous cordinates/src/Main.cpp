#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
#include "graphics/models/Cube1.hpp"
#include "graphics/models/Cube2.hpp"
#include "graphics/models/Ray.hpp"


#include "io/Keyboard.h"
#include "io/Mouse.h"
#include "io/Camera.h"
#include "io/Screen.h"

void processInput(double dt);

Screen screen;

Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
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

	Cordinates cordinates(glm::vec3(2.0f));
	cordinates.init();
	Cube1 cube1(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.04f));
	cube1.init();
	Cube2 cube2(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.04f));
	cube2.init();
	Ray ray(glm::vec3(1.0f));
	ray.init();


	// ImGUI initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(screen.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	while (!screen.shouldClose()) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// process input
		processInput(deltaTime);
		ray.crossPoint();

		// update frame
		screen.update();

		// ImGUI window
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		shader.activate();

		// create transformation for screen
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)screen.SCR_WIDTH / (float)screen.SCR_HEIGHT, 0.1f, 100.0f);

		shader.activate();
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		// ImGui window layout global settings
		ImGui::Begin("ImGui");
		ImGui::PushItemWidth(50.0f);

		//ImGUI window layout
		ImGui::Text("Cordinates settings");
		ImGui::Separator();
		ImGui::Text("Size multiplayer ");
		ImGui::SameLine();
		ImGui::InputFloat("##cordinates multiplayer", &cordinates.sizeMultiplayer, 0.0, 0.0, "%.2f");
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("Object settings");
		ImGui::Separator();
		ImGui::Text("Size multiplayer ");
		ImGui::SameLine();
		ImGui::InputFloat("##object multiplayer", &cube1.sizeMultiplayer, 0.0, 0.0, "%.2f");
		ImGui::Text("Position: ");
		ImGui::Text("x");
		ImGui::SameLine();
		ImGui::InputFloat("##object x", &cube1.pos.x); cube2.pos.x = cube1.pos.x;
		ImGui::SameLine();
		ImGui::Text("y");
		ImGui::SameLine();
		ImGui::InputFloat("##object y", &cube1.pos.y); cube2.pos.y = cube1.pos.y;
		ImGui::SameLine();
		ImGui::Text("w");
		ImGui::SameLine();
		ImGui::InputFloat("##object w", &cube2.w);
		ray.pointPozition = cube1.pos;


		ImGui::End();
		// render UI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//render shapes
		cordinates.render(shader);
		cube1.render(shader);
		cube2.render(shader);
		ray.render(shader);

		// send new frame to window
		screen.newFrame();
	}

	cordinates.cleanup();
	cube1.cleanup();
	cube2.cleanup();
	ray.cleanup();
	
	// ImGui cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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