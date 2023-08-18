#include <Core/AloeEngine.h>
#include <Core/Window.h>

#include <Editor/EditorApplication.h>

int main() {

    Aloe::EditorApplication editorApplication = Aloe::EditorApplication();

    editorApplication.Start();
    editorApplication.Update();
    editorApplication.End();

    return 0;
}