#include"imgui_user_rendering_interface.h"

//�� �� object ���� Ŭ���� �ۼ� �� ��� �ʿ�
void imguiURI::printObj(grid* obj) {
	printTransform(obj->myTrns);
	if (obj->tag == "grid") {
		ImGui::Separator();
		ImGui::InputFloat("gridSize", &obj->gridSize);
		ImGui::Separator();
		ImGui::InputInt("gridNum", &obj->gridNum);
	}
}

void imguiURI::printTransform(Transform trns) {
	ImGui::Text("Transform");
	ImGui::Separator();
	ImGui::InputFloat3("Position", trns.Position);
	ImGui::Separator();
	ImGui::InputFloat3("Rotation", trns.Rotation);
	ImGui::Separator();
	ImGui::InputFloat3("Scale", trns.Scale);
}