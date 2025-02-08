#include "display/base_window.hpp"
#include "display/RenderData.hpp"

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

    RenderData* TriangleData;
    RenderData* RectangleData;
    RenderData* TextureData;
    RenderData* MixedTextureData;
    RenderData* CubeData;

    RenderData* CurrentRenderData;

private:
    float TriangleVertices[9] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };

    unsigned int VAO2;
    unsigned int VBO2;
    unsigned int EBO2;

    void LoadContent2();
    void Render2();

    void ShowTriangle();
    void ShowRectangle();
    void ShowTexture();
    void ShowMixedTexture();
    void ShowCube();
};