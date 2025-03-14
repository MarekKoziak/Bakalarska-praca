#ifndef MYGUI_H
#define MYGUI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class MyGui {
public:
	static float x, y, w;
	static float size;
	static float mouseSnesitivity, cameraSpeed;

	static void init(GLFWwindow* window);
	static void cleanup();

	static void newFrame();
	static void mainLayout();
	static void overlayLayout();
	static void render();
	static void show();

	static void mainWindowSettings();
	static void overlayWindowSettings();

	static void customFontsLoading();

private:
	static ImGuiIO* io;
	static ImGuiStyle* style;
	static ImFont* myFontH1;
	static ImFont* myFontH2;
};

#endif
