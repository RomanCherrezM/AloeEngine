#include "EditorContentBrowserPanel.h"

#include <imgui.h>

#include <Core/AloeEngine.h>
#include <Scene/SceneManager.h>

namespace Aloe
{
    std::filesystem::path s_editorAssetPath = "../../AloeEditor/Assets/Content Browser/Files";
    std::filesystem::path s_assetPath = "../../AloeProject/Assets";

    std::unordered_map<std::string, EditorFileType> s_extensionFileMap;
    std::unordered_map<AssetType, EditorFileType> s_assetFileMap;

    EditorContentBrowserPanel::EditorContentBrowserPanel(EditorEventMessenger* eventRef)
    {
        m_eventMessenger = eventRef;
        m_currentPath = s_assetPath;

        // TODO: Find a way to cache the Editor/Assets directory same as in the game
        auto notSupportedText = Texture::Create((s_editorAssetPath / "not_supported.png").string());
        auto textureSourceText = Texture::Create((s_editorAssetPath / "raw.png").string());
        auto textureAssetText = Texture::Create((s_editorAssetPath / "texture_asset.png").string());
        auto folderText = Texture::Create((s_editorAssetPath / "folder.png").string());
        auto sceneAssetText = Texture::Create((s_editorAssetPath / "scene.png").string());

        folderText->Load();
        textureSourceText->Load();
        textureAssetText->Load();
        sceneAssetText->Load();
        notSupportedText->Load();

        m_fileIcons[EditorFileType::NotSoported] = notSupportedText;
        m_fileIcons[EditorFileType::Folder] = folderText;
        m_fileIcons[EditorFileType::SourceTexture] = textureSourceText;
        m_fileIcons[EditorFileType::AloeTexture] = textureAssetText;
        m_fileIcons[EditorFileType::AloeScene] = sceneAssetText;

        // Setup extension -> file
        {
            s_extensionFileMap[""] = EditorFileType::NotSoported;
            s_extensionFileMap[".png"] = EditorFileType::SourceTexture;
            s_extensionFileMap[".scene"] = EditorFileType::AloeScene;
        }

        // Setup asset -> file
        {
            s_assetFileMap[AssetType::Invalid] = EditorFileType::NotSoported;
            s_assetFileMap[AssetType::Mesh] = EditorFileType::AloeMesh;
            s_assetFileMap[AssetType::Texture] = EditorFileType::AloeTexture;
            s_assetFileMap[AssetType::Scene] = EditorFileType::AloeScene;
        }
    }

    void EditorContentBrowserPanel::Init()
    {
    }

    EPanelType EditorContentBrowserPanel::GetPanelType()
    {
        return EPanelType::ContentBrowser;
    }

    bool EditorContentBrowserPanel::OnPanelUpdate(Entity entity)
    {
        bool open = true;
        if (ImGui::Begin("Content Browser", &open))
        {
            // Left Side - File Hierarchy
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
                ImGui::BeginChild("ChildMiddle", ImVec2(0, 0),
                    ImGuiChildFlags_Border | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeY, window_flags);
                
                // Top Bar
                if (ImGui::ArrowButton("##leftArrow", ImGuiDir_Left))
                {

                }
                ImGui::SameLine();
                if (ImGui::ArrowButton("##rightArrow", ImGuiDir_Right))
                {

                }
                ImGui::SameLine();
                DrawFilePath();

                ImGui::EndChild();
            }

            // Left Side - File Hierarchy
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar;
                ImGui::BeginChild("ChildLeft", ImVec2(200.0f, ImGui::GetContentRegionAvail().y),
                    ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Border, window_flags);
                
                DrawFileHierarchy(s_assetPath);

                ImGui::EndChild();
            }

            ImGui::SameLine();

            // Right Side - File Browser
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar;
                ImGui::BeginChild("ChildRight", ImVec2(-1.0f, ImGui::GetContentRegionAvail().y),
                    ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Border, window_flags);
                
                DrawFileBrowser();

                ImGui::EndChild();
            }         
        }
        ImGui::End();

        return !open;
    }

    void EditorContentBrowserPanel::DrawFileHierarchy(std::filesystem::path path)
    {
        // We gather all the directories first because we want to know if its empty before drawing the Tree
        std::vector<std::filesystem::path> innerPaths;

        for (auto& path : std::filesystem::directory_iterator(path))
        {
            if (path.is_directory()) {
                innerPaths.push_back(path);
            }
        }

        ImGuiTreeNodeFlags flags = innerPaths.empty() ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow;

        bool open = ImGui::TreeNodeEx(path.stem().string().c_str(), flags);

        if (ImGui::IsItemClicked())
        {
            m_currentPath = path;
        }

        if (open)
        {
            for (auto& path : innerPaths)
            {
                DrawFileHierarchy(path);
            }

            ImGui::TreePop();
        }
    }

    void EditorContentBrowserPanel::DrawFilePath()
    {
        std::list<std::filesystem::path> paths;

        auto itPath = m_currentPath;
        while (itPath != s_assetPath)
        {
            paths.push_front(itPath);
            itPath = itPath.parent_path();
        }

        if (ImGui::Button("Assets"))
        {
            m_currentPath = s_assetPath;
        }
        
        ImGui::SameLine();ImGui::Text("/");

        for each (auto path in paths)
        {
            ImGui::SameLine();
            if (ImGui::Button(path.stem().string().c_str()))
            {
                m_currentPath = path;
            }

            ImGui::SameLine();ImGui::Text("/");
        }
    }

    void EditorContentBrowserPanel::DrawFileBrowser()
    {
        static EditorFile s_filePopup;

        float totalSize = ImGui::GetContentRegionAvail().x;
        float thumbnailSize = 100 + ImGui::GetStyle().ItemSpacing.x * 2.0f + ImGui::GetStyle().FramePadding.x * 2.0f;

        int columnCount = (int)(totalSize / (thumbnailSize + 10.0f)); // 20.0f is a bias to avoid file images cropping weirdly
        if (columnCount < 1)columnCount = 1;

        int currentColumn = 0;
        if (ImGui::BeginTable("FileBrowserTable", columnCount, ImGuiTableFlags_SizingStretchSame)) {

            for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentPath))
            {
                if (currentColumn == 0)ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(currentColumn);

                const auto& path = directoryEntry.path();

                std::string fileStem = path.stem().string();

                EditorFile editorFile;

                editorFile.m_type = GetFileType(directoryEntry);
                editorFile.m_path = path.string();

                uint32_t icon = m_fileIcons[editorFile.m_type]->GetRendererID();
                
                ImGui::ImageButton((ImTextureID)icon, ImVec2(thumbnailSize, thumbnailSize), ImVec2(0, 1), ImVec2(1, 0));
                
                HandleDragDropFile(editorFile);

                if (ImGui::IsItemHovered())
                {
                    if (ImGui::IsMouseDoubleClicked(0))
                    {
                        OpenFile(editorFile);
                    }
                    if (ImGui::IsMouseClicked(1))
                    {
                        OpenFileOptionsPopup(editorFile);
                        s_filePopup = editorFile;
                    }
                }

                ImGui::SetNextItemWidth(thumbnailSize);
                ImGui::Text(fileStem.c_str());

                currentColumn++;
                if (currentColumn >= columnCount) currentColumn = 0;
            }

            HandleFilePopup(s_filePopup);

            ImGui::EndTable();
        }
    }

    void EditorContentBrowserPanel::OpenFileOptionsPopup(const EditorFile& file)
    {
        // TODO: Change file options per file type (open different popups accordingly)
        ImGui::OpenPopup("FileOptions");
    }

    void EditorContentBrowserPanel::HandleFilePopup(const EditorFile& file)
    {
        if (ImGui::BeginPopup("FileOptions"))
        {
            if (ImGui::Button("Create Asset"))
            {
                AssetSerializer assetSerializer(file.m_path.string());
                assetSerializer.Serialize();
            }

            ImGui::EndPopup();
        }
    }

    void EditorContentBrowserPanel::HandleDragDropFile(const EditorFile& file)
    {
        ImGuiDragDropFlags srcFlags = 0;
        srcFlags |= ImGuiDragDropFlags_SourceNoDisableHover;
        srcFlags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
        if (ImGui::IsItemHovered() && ImGui::BeginDragDropSource(srcFlags))
        {
            // TODO: Begin different type of DragAsset depending on asset type
            ImGui::SetDragDropPayload("DragAsset", file.m_path.string().data(), file.m_path.string().size());
            ImGui::EndDragDropSource();
        }
    }

    EditorFileType EditorContentBrowserPanel::GetFileType(std::filesystem::directory_entry entry)
    {
        std::filesystem::path path = entry.path();

        if (entry.is_directory()) return EditorFileType::Folder;
        if (!path.has_extension()) return EditorFileType::NotSoported;

        if (path.extension() == ".asset")
        {
            AssetSpec spec;

            AssetSerializer serializer(path);
            spec = serializer.Deserialize();

            return s_assetFileMap[spec.m_type];
        }
        else
        {
            return s_extensionFileMap[path.extension().string()];
        }
    }

    void EditorContentBrowserPanel::OpenFile(const EditorFile& file)
    {
        switch (file.m_type)
        {
        case EditorFileType::Folder:
        {
            m_currentPath /= file.m_path.filename();
            break;
        }
        case EditorFileType::AloeScene:
        {
            SceneManager::Get().TryLoadScene(file.m_path.string());
            break;
        }
        default:
            printf("\n [WARNING] Trying to open non supported file type");
        }
    }

    void EditorContentBrowserPanel::OnEvent(Aloe::EditorEvent& event)
    {
    }

}