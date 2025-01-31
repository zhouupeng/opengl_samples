#pragma once

#include "display/RenderData.hpp"

class RenderRectangleUseTexture : public RenderData
{
public:
    RenderRectangleUseTexture() {}
    RenderRectangleUseTexture(std::vector<float> Vertices, std::vector<int> Indices, std::string Name) : RenderData(Vertices, Indices, Name) {}
    RenderRectangleUseTexture(std::string Name);

    void ConfigData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) override;
    void Draw() override;

private:
    unsigned int texture;
    
};