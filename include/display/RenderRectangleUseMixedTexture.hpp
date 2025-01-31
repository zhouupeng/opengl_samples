#pragma once

#include "display/RenderData.hpp"

class RenderRectangleUseMixedTexture : public RenderData
{
public:
    RenderRectangleUseMixedTexture() {}
    RenderRectangleUseMixedTexture(std::vector<float> Vertices, std::vector<int> Indices, std::string Name) : RenderData(Vertices, Indices, Name) {}
    RenderRectangleUseMixedTexture(std::string Name);

    void ConfigData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) override;
    void Draw() override;

private:
    unsigned int texture;
    unsigned int texture2;
    
};