#pragma once

#include <string>
#include <Core/UUID.h>

namespace Aloe
{
    enum class AssetState
    {
        Invalid = -1,

        Unloaded,
        Loading,

        Loaded
    };

    enum class AssetType
    {
        Invalid = -1,

        Texture,
        Mesh,
        Scene,
    };

    struct AssetSpec
    {
        UUID m_uuid = 0;
        AssetType m_type = AssetType::Invalid;
        AssetState m_state = AssetState::Invalid;
        std::string m_path = "";
    };

    class Asset
    {
    public:

        virtual void Load() = 0;
        virtual void Unload() = 0;

        UUID GetUUID() { return m_assetSpec.m_uuid; }
        AssetState GetAssetState() { return m_assetSpec.m_state; }
        std::string GetAssetPath() { return m_assetSpec.m_path; }

        AssetSpec m_assetSpec;
    };
}