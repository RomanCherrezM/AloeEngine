#define ALOE_EDITOR 1


class Applcation
{

    void Start()
    {
        
        


#ifdef ALOE_EDITOR
#endif

    }

};



class EditorModule
{

};

class Systems
{
public:
    void Init();
 
    // Scripting
    // Input
    // Transform
    // Render
    // Sound
    // Physics

};

class Scene
{
    
};

class SceneManager
{
    void Play()
    {
        systems.Init(); // Scripting system 
    }

    void 


    Systems systems;
    Scene scene;
};