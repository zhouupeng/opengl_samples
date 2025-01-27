#pragma once

#include "display/RenderData.hpp"

class RenderTriangle : public RenderData
{
public:
    RenderTriangle() {}
    RenderTriangle(std::vector<float> Vertices, std::vector<int> Indices, std::string Name) : RenderData(Vertices, Indices, Name) {}
    RenderTriangle(std::string Name);

    void ConfigData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) override;
    void Draw() override;
};