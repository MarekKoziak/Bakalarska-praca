#include "MyGui.h"

ImGuiIO* MyGui::io = nullptr;
ImGuiStyle* MyGui::style = nullptr;
ImFont* MyGui::myFontH1 = nullptr;
ImFont* MyGui::myFontH2 = nullptr;
float MyGui::x = 0.0f;
float MyGui::y = 0.0f;
float MyGui::w = 1.0f;
float MyGui::size = 1.0f;

void MyGui::show() {
	MyGui::newFrame();

	ImGui::Begin("Ovládacie prvky");
	MyGui::layout();
	ImGui::End();

	MyGui::render();
}

void MyGui::init(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	style = &ImGui::GetStyle();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	MyGui::customFontsLoading();
	style->FrameRounding = 3.0f;
}

void MyGui::customFontsLoading() {
	static const ImWchar slovak_glyph_ranges[] = {
	0x0020, 0x007E, 0x00A0, 0x00FF, 0x0100, 0x017F, 0
	};

	io->Fonts->AddFontDefault();
	myFontH1 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 22.0f, nullptr, slovak_glyph_ranges);
	IM_ASSERT(myFontH1 != NULL);
	myFontH2 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 19.0f, nullptr, slovak_glyph_ranges);
	IM_ASSERT(myFontH2 != NULL);
}

void MyGui::newFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(280, 200), ImGuiCond_Once);
	ImGui::SetNextWindowSizeConstraints(
		ImVec2(200, 0),
		ImVec2(350, FLT_MAX)
	);
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

void MyGui::layout() {
	ImGui::PushFont(myFontH1);
	ImGui::PushItemWidth(-FLT_MIN);
		ImGui::Text("Nastavenia súradníc");
	ImGui::PopFont();
	ImGui::PushFont(myFontH2);
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("Veľkosť ");
		ImGui::SameLine();
		ImGui::SliderFloat("##slider", &size, 1.0f, 3.0f, "%.1f");
		ImGui::Spacing();
	ImGui::PopFont();

	ImGui::PushFont(myFontH1);
		ImGui::Text("Nastavenia bodu");
	ImGui::PopFont();
	ImGui::PushFont(myFontH2);
		ImGui::Separator();
		ImGui::Text("Pozícia: x, y, w");
		if (ImGui::BeginTable("FullWidthTable", 3, ImGuiTableFlags_SizingStretchSame)) {
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::DragFloat("##point x", &x, 0.1f);
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::DragFloat("##point y", &y, 0.1f);
				ImGui::TableNextColumn();
				ImGui::PushItemWidth(-FLT_MIN);
				ImGui::DragFloat("##point w", &w, 0.1f, 0.0f, FLT_MAX, "%.3f", ImGuiSliderFlags_AlwaysClamp);
			ImGui::EndTable();
		}
	ImGui::PopFont();
}