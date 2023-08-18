#include "EditorStyles.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include <string>
#include <glm/glm.hpp>

namespace Aloe {

    void DrawVec3Editor(const std::string& name, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
    {

		ImGui::BeginTable(name.c_str(), 4);
		
		float paramSize = (ImGui::GetContentRegionAvail().x - columnWidth) / 3.0f;

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		ImGui::TableSetupColumn("text", ImGuiTableColumnFlags_WidthFixed, columnWidth); // Default to 100.0f
		ImGui::TableSetupColumn("x", ImGuiTableColumnFlags_WidthStretch, paramSize);
		ImGui::TableSetupColumn("y", ImGuiTableColumnFlags_WidthStretch, paramSize);
		ImGui::TableSetupColumn("z", ImGuiTableColumnFlags_WidthStretch, paramSize);

		ImGui::TableNextRow(); // Start first row

		{	 // ----------- Title ----------- //
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(name.c_str());
		}

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		{	// ----------- X ----------- //
			ImGui::TableSetColumnIndex(1);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
				values.x = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		}

		{	// ----------- Y ----------- //
			ImGui::TableSetColumnIndex(2);	
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
				values.y = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		}

		{	// ----------- Z ----------- //
			ImGui::TableSetColumnIndex(3);	
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize))
				values.z = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		}

		ImGui::PopStyleVar(2);
		ImGui::EndTable();
    }

	void DrawColorEditor(const std::string& name, glm::vec3& values, float resetValue = 1.0f, float columnWidth = 100.0f)
	{
		ImGui::BeginTable(name.c_str(), 4);

		float paramSize = (ImGui::GetContentRegionAvail().x - columnWidth) / 3.0f;

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		ImGui::TableSetupColumn("text", ImGuiTableColumnFlags_WidthFixed, columnWidth); // Default to 100.0f
		ImGui::TableSetupColumn("r", ImGuiTableColumnFlags_WidthStretch, paramSize);
		ImGui::TableSetupColumn("g", ImGuiTableColumnFlags_WidthStretch, paramSize);
		ImGui::TableSetupColumn("b", ImGuiTableColumnFlags_WidthStretch, paramSize);

		ImGui::TableNextRow(); // Start first row

		{	 // ----------- Title ----------- //
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(name.c_str());
		}

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		{	// ----------- X ----------- //
			ImGui::TableSetColumnIndex(1);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("R", buttonSize))
				values.x = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::DragFloat("##R", &values.x, 0.01f, 0.0f, 1.0f, "%.3f");
		}

		{	// ----------- Y ----------- //
			ImGui::TableSetColumnIndex(2);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("G", buttonSize))
				values.y = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::DragFloat("##G", &values.y, 0.01f, 0.0f, 1.0f, "%.3f");
		}

		{	// ----------- Z ----------- //
			ImGui::TableSetColumnIndex(3);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("B", buttonSize))
				values.z = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::DragFloat("##B", &values.z, 0.01f, 0.0f, 1.0f, "%.3f");
		}

		ImGui::PopStyleVar(2);
		ImGui::EndTable();
	}

	void DrawFloatEditor(const std::string& name, float& value, float columnWidth = 100.0f)
	{
		ImGui::BeginTable(name.c_str(), 2);

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, columnWidth); // Default to 100.0f
		ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x);

		ImGui::TableNextRow();

		{   // Row 1
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(name.c_str());

			ImGui::TableSetColumnIndex(1);
			ImGui::SetNextItemWidth(-FLT_MIN); //Right Aligned
			ImGui::DragFloat("", &value, 0.1f, 0.0f, 0.0f, "%.2f");
		}

		ImGui::PopStyleVar(2);

		ImGui::EndTable();
	}

	void DrawSliderEditor(const std::string& name, float& value, float min = 0.0f, float max = 100.0f, float columnWidth = 100.0f)
	{
		ImGui::BeginTable(name.c_str(), 2);

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, columnWidth); // Default to 100.0f
		ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x);

		ImGui::TableNextRow();

		{   // Row 1
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(name.c_str());

			ImGui::TableSetColumnIndex(1);
			ImGui::SetNextItemWidth(-FLT_MIN); //Right Aligned
			ImGui::SliderFloat("", &value, min, max, "%.2f");
		}

		ImGui::PopStyleVar(2);

		ImGui::EndTable();
	}

	void DrawExtendedSliderEditor(const std::string& name, float& value, float min = 0.0f, float max = 100.0f, float columnWidth = 100.0f)
	{
		ImGui::BeginTable(name.c_str(), 2);

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, columnWidth); // Default to 100.0f
		ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x);

		ImGui::TableNextRow();

		{   // Row 1
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(name.c_str());

			ImGui::PopStyleVar(2);
			ImGui::TableSetColumnIndex(1);
			ImGui::SetNextItemWidth(columnWidth);
			ImGui::InputFloat("##1", &value, 0.0f);

			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN); //Right Aligned
			ImGui::SliderFloat("##2", &value, min, max, "");
		}

		ImGui::EndTable();
	}

}