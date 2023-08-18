#pragma once

#include <string>
#include <glm/glm.hpp>
#include <imgui_internal.h>

namespace Aloe {

    void DrawVec3Editor(const std::string& name, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
    void DrawFloatEditor(const std::string& name, float& value, float columnWidth = 100.0f);
    void DrawSliderEditor(const std::string& name, float& value, float min = 0.0f, float max = 100.0f, float columnWidth = 100.0f);
    void DrawExtendedSliderEditor(const std::string& name, float& value, float min = 0.0f, float max = 100.0f, float columnWidth = 100.0f);
    void DrawColorEditor(const std::string& name, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
}