#pragma once

#include <Core/UUID.h>

#include <unordered_map>
#include <memory>
#include <string>
#include <filesystem>

#include <Render/Texture.h>

namespace Aloe
{
    // Contains a map of all assets in the Assets directory,
    // all these assets are unloaded until a scene is loaded and the
    // assets are requested, moment when they are loaded.

    class AssetLibrary
    {
    public:
        // Get a pointer to the instance
        static AssetLibrary* Get();

        // Goes through the filepath and caches the UUID of the assets
        void InitCacheLibrary(const std::string filepath);

        template<typename T>
        std::shared_ptr<T> GetAsset(const UUID& uuid);

    private:

        // Default game assets
        void CacheDefaultAssets();

        // Cache just stores the path to the texture, it doesn't load it
        // when we load the scene we load all the assets used
        bool CacheAsset(std::shared_ptr<Asset>& asset);

        void CacheDirectory(std::filesystem::path path);

        std::unordered_map<UUID, std::shared_ptr<Asset>> m_assets;

    };

}