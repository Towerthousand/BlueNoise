#include "MyProfiler.hpp"

MyProfiler::MyProfiler() {
}

void MyProfiler::renderCustomInterface() const {
	ImGui::Begin("Controls", nullptr, ImVec2(0.47f*Window::getInstance()->getSize().x, 0.11f*Window::getInstance()->getSize().y), 0.9f, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowPos(ImVec2(0.5f*Window::getInstance()->getSize().x, 0.05f*Window::getInstance()->getSize().y), ImGuiSetCondition_FirstUseEver);
	ImGui::SliderFloat("Min Power", &minPower, 0.0f, 1.0f);
	ImGui::SliderFloat("Max Power", &maxPower, 0.0f, 1.0f);
	ImGui::SliderFloat("Grid Noise Scale", &gridNoiseScale, 0.1f, 100.0f);
	ImGui::SliderFloat("Drop Scale", &dropScale, 0.01f, 200.0f);
	ImGui::SliderFloat("Drop Chance", &dropChance, 0.0f, 1.0f);
	ImGui::SliderInt("Min Grid Size", &minGridSize, 1, 10);
	ImGui::SliderInt("Max Grid Size", &maxGridSize, 1, 10);
	ImGui::SliderInt("Grid Size Cutoff", &gridSizeCutoff, 1, 10);
	ImGui::SliderInt("Grid Noise Octaves", &gridNoiseOctaves, 1, 10);
	ImGui::Separator();
	ImGui::Text("Blue Noise Generator");
	ImGui::End();
	maxPower = glm::max(minPower,maxPower);
	minPower = glm::min(minPower,maxPower);
}
