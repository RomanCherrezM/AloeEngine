#pragma once

#include <Editor/EditorPanelBase.h>

#include <Core/AssetSerializer.h>
#include <Render/Texture.h>

#include <filesystem>
#include <map>

namespace Aloe {

    enum class EditorFileType
    {
        NotSoported = -1,

        Folder,

        SourceTexture,
        SourceStaticMesh,

        AloeTexture,
        AloeScene,
        AloeMesh,
    };

    struct EditorFile
    {
        EditorFileType m_type = EditorFileType::NotSoported;

        std::filesystem::path m_path = "";
    };

    class EditorContentBrowserPanel : public EditorPanelBase
    {
    public:
        EditorContentBrowserPanel(EditorEventMessenger* eventRef);

        // EditorPanelBase
        virtual void Init() override;
        virtual EPanelType GetPanelType() override;
        virtual bool OnPanelUpdate(Entity entity) override;

        // IEditorEventListener
        virtual void OnEvent(Aloe::EditorEvent& event) override;

        void DrawFileHierarchy(std::filesystem::path path);
        void DrawFilePath();
        void DrawFileBrowser();

    private:

        EditorFileType GetFileType(std::filesystem::directory_entry entry);

        void OpenFile(const EditorFile& file);

        void OpenFileOptionsPopup(const EditorFile& file);

        void HandleFilePopup(const EditorFile& file);
        void HandleDragDropFile(const EditorFile& file);

        std::filesystem::path m_currentPath;

        // Resources
        std::map<EditorFileType, std::shared_ptr<Texture>> m_fileIcons;
            
        EditorEventMessenger* m_eventMessenger;
    };
}