#include "AssetSerializer.h"

#define YAML_CPP_STATIC_DEFINE

#include <yaml-cpp/yaml.h>

#include <fstream>

#include <Core/UUID.h>

namespace Aloe
{

    AssetSerializer::AssetSerializer(std::filesystem::path path) :
        m_assetPath(path)
    {
    }

    bool AssetSerializer::Serialize()
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Asset" << YAML::BeginMap;

        out << YAML::Key << "UUID" << YAML::Value << UUID();
        out << YAML::Key << "Source" << YAML::Value << m_assetPath.string();
        out << YAML::Key << "Type" << YAML::Value << 0;

        out << YAML::EndMap;
        out << YAML::EndMap;

        std::filesystem::path newAssetPath = m_assetPath;
        newAssetPath.replace_extension("asset");

        // TODO: Check if asset exist to create it with another name

        std::ofstream fout(newAssetPath);
        fout << out.c_str();

        return true;
    }

    AssetSpec AssetSerializer::Deserialize()
    {
        AssetSpec spec;

        std::ifstream stream(m_assetPath);
        std::stringstream strStream;

        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());

        auto asset = data["Asset"];
        if (!asset) return spec;

        // TODO: Log if uuid is 0

        spec.m_uuid = asset["UUID"].as<uint64_t>();
        spec.m_path = asset["Source"].as<std::string>();
        spec.m_type = (AssetType)asset["Type"].as<int32_t>();
        spec.m_state = AssetState::Unloaded;

        return spec;
    }

}