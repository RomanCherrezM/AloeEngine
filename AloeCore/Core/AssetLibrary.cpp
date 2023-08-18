#include "AssetLibrary.h"

#include <Core/AssetSerializer.h>

#include <Render/Renderer.h>

namespace Aloe
{
    AssetLibrary* AssetLibrary::Get()
    {
        static AssetLibrary* library = new AssetLibrary();

        return library;
    }

    void AssetLibrary::CacheDefaultAssets() 
    {
        std::shared_ptr<Asset> defaultTexture = Renderer::Get()->GetDefaultSpriteTexture();
        CacheAsset(defaultTexture);
    }

    void AssetLibrary::InitCacheLibrary(const std::string filepath)
    {
        // TODO: assert multiple Init cache calls
        CacheDefaultAssets();

        CacheDirectory(filepath);
    }

    template std::shared_ptr<Texture> AssetLibrary::GetAsset(const UUID& uuid);

    template<typename T>
    std::shared_ptr<T> AssetLibrary::GetAsset(const UUID& uuid)
    {
        if (m_assets.find(uuid) == m_assets.end()) return nullptr;

        if (m_assets[uuid]->m_assetSpec.m_state == AssetState::Unloaded)
        {
            m_assets[uuid]->Load();
        }

        return std::static_pointer_cast<Texture>(m_assets[uuid]);
    }

    bool AssetLibrary::CacheAsset(std::shared_ptr<Asset>& asset)
    {
        if (m_assets.find(asset->GetUUID()) != m_assets.end()) return false;

        m_assets.emplace(std::pair(asset->GetUUID(), asset));

        return true;
    }

    void AssetLibrary::CacheDirectory(std::filesystem::path path)
    {
        for (auto& file : std::filesystem::directory_iterator(path))
        {
            if (file.is_directory()) CacheDirectory(file);

            if (file.path().extension() == ".asset")
            {
                AssetSerializer serializer(file.path());
                AssetSpec spec = serializer.Deserialize();

                std::shared_ptr<Asset> asset;

                switch (spec.m_type)
                {
                case AssetType::Texture: asset = Texture::Create(spec.m_path);
                    break;
                }

                asset->m_assetSpec = spec;

                CacheAsset(asset);
            }
        }
    }

}