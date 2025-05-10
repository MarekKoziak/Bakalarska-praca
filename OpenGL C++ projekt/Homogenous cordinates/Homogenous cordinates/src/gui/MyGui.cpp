#include "MyGui.h"
#include "../io/Screen.h"
#include <string>

ImGuiIO* MyGui::io = nullptr;
ImGuiStyle* MyGui::style = nullptr;
ImFont* MyGui::myFontH1 = nullptr;
ImFont* MyGui::myFontH2 = nullptr;
float MyGui::x = 0.0f;
float MyGui::y = 0.0f;
float MyGui::w = 1.0f;
float MyGui::mouseSnesitivity = 1.0f;
float MyGui::cameraSpeed = 1.0f;

void MyGui::show() {
	newFrame();

	// main GUI window
	mainWindowSettings();
	ImGui::Begin("Ovládacie prvky");
	mainLayout();
	ImGui::End();

	// overlay window
	overlayWindowSettings();
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
	overlayLayout();
	ImGui::End();

	render();
}

void MyGui::init(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	style = &ImGui::GetStyle();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	MyGui::loadCustomFonts();
}

void MyGui::loadCustomFonts() {
	static const ImWchar slovak_glyph_ranges[] = {
	0x0020, 0x007E, 0x00A0, 0x00FF, 0x0100, 0x017F, 0
	};

	io->Fonts->AddFontDefault();
	myFontH1 = io->Fonts->AddFontFromFileTTF("assets/fonts/arial.ttf", 22.0f, nullptr, slovak_glyph_ranges);
	IM_ASSERT(myFontH1 != NULL);
	myFontH2 = io->Fonts->AddFontFromFileTTF("assets/fonts/arial.ttf", 19.0f, nullptr, slovak_glyph_ranges);
	IM_ASSERT(myFontH2 != NULL);
}

void MyGui::newFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void MyGui::render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MyGui::cleanup() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MyGui::mainWindowSettings() {
	style->FrameRounding = 3;
	style->WindowRounding = 5;
	style->Colors[ImGuiCol_WindowBg].w = 1;

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(320, 280), ImGuiCond_Once);
	ImGui::SetNextWindowSizeConstraints(
		ImVec2(280, 0),
		ImVec2(450, FLT_MAX)
	);
}

void MyGui::overlayWindowSettings() {
	style->Colors[ImGuiCol_WindowBg].w = 0.5f;

	ImGui::SetNextWindowPos(ImVec2(Screen::SCR_WIDTH - 90, Screen::SCR_HEIGHT - 60));
	ImGui::SetNextWindowSize(ImVec2(90, 60));
}

void MyGui::mainLayout() {
	ImGui::PushFont(myFontH1);
		ImGui::Text("Ovládanie");
	ImGui::PopFont();
	ImGui::PushFont(myFontH2);
		ImGui::Separator();
		if (ImGui::BeginTable("Table1", 2)) {
				ImGui::TableSetupColumn("Static Column", ImGuiTableColumnFlags_WidthFixed, 130.0f);
				ImGui::TableNextColumn();
				ImGui::Text("Sensitivita myši");
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::SliderFloat("##mouse sens", &mouseSnesitivity, 0.0f, 5.0f, "%.2f");
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Rýchlosť kamery");
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::SliderFloat("##cam speed", &cameraSpeed, 0.0f, 10.0f, "%.2f");
			ImGui::EndTable();
		}
	ImGui::PopFont();

	ImGui::PushFont(myFontH1);
		ImGui::Text("Homogénny bod");
	ImGui::PopFont();
	ImGui::PushFont(myFontH2);
		ImGui::Separator();
		ImGui::Text("Pozícia: x, y, w");
		if (ImGui::BeginTable("Table2", 3, ImGuiTableFlags_SizingStretchSame)) {
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::DragFloat("##point x", &x, 0.01f);
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::DragFloat("##point y", &y, 0.01f);
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::DragFloat("##point w", &w, 0.01f, 0.0f, FLT_MAX, "%.3f", ImGuiSliderFlags_AlwaysClamp);
			ImGui::EndTable();
		}
	ImGui::PopFont();
}

void MyGui::overlayLayout() {
	ImGui::PushFont(myFontH2);

	ImGui::Text("u =");
	ImGui::SameLine();
	if (x == 0) {
		ImGui::Text("0.000");
	}
	else {
		std::string str = std::to_string(x / w);
		ImGui::Text(str.length() > 5 ? str.erase(5).c_str() : str.c_str());
	}
	ImGui::Text("v =");
	ImGui::SameLine();
	if (y == 0) {
		ImGui::Text("0.000");
	}
	else {
		std::string str = std::to_string(y / w);
		ImGui::Text(str.length() > 5 ? str.erase(5).c_str() : str.c_str());
	}

	ImGui::PopFont();
}