#pragma once

#include "display/RenderData.hpp"

class RenderRectangle : public RenderData
{
public:
    RenderRectangle() {}
    RenderRectangle(std::vector<float> Vertices, std::vector<int> Indices, std::string Name) : RenderData(Vertices, Indices, Name) {}
    RenderRectangle(std::string Name);

    void ConfigData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) override;
    void Draw() override;
};