#pragma once

#include <Core/Asset.h>
#include <filesystem>

namespace Aloe
{
    class AssetSerializer
    {
    public:

        // path - source file to do serialization on
        AssetSerializer(std::filesystem::path path);

        // Takes path and creates an asset from it
        bool Serialize();

        // Takes path and returns deserialization
        AssetSpec Deserialize();

    private:

        std::filesystem::path m_assetPath;

    };
}