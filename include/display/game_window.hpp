#pragma once

#include "display/base_window.hpp"
#include "display/RenderData.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


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

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float DeltaTime = 0.0f;
    float LastFrame = 0.0f;

    void ProcessInput(GLFWwindow* window);
    glm::mat4 GetViewMatrix();

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
