#ifndef MYGUI_H
#define MYGUI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class MyGui {
public:
	static float x, y, w, size;

	static void init(GLFWwindow* window);
	static void render();
	static void cleanup();

	static void show();
	static void layout();
	static void newFrame();

	static void customFontsLoading();

private:
	static ImGuiIO* io;
	static ImGuiStyle* style;
	static ImFont* myFontH1;
	static ImFont* myFontH2;
};

#endif
