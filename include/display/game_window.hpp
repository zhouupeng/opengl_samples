#include "display/base_window.hpp"

class GameWindow : public BaseWindow 
{

public:
    GameWindow(int width, int height, std::string title);
    void Initialize();
    void LoadContent();
    void Update();
    void Render();
    void Unload();
    void ShowRenderSettings();
private:
    float TriangleVertices[9] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };
    void LoadContent2();
    void Render2();
};