#pragma once

#include "shaders/shader.hpp"
#include <vector>

class RenderData
{

public:

    RenderData();
    RenderData(std::vector<float> Vertices, std::vector<int> Indices, std::string Name);
    ~RenderData();
    
    void LoadShader(std::string VertexShader, std::string FragmentShader);
    virtual void ConfigData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) = 0;
    virtual void Draw() = 0;

    std::string Name;

    Shader Shader;
    std::vector<float> Vertices;
    std::vector<int> Indices;
};