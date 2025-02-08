#pragma once

#include "display/RenderData.hpp"

class RenderCube : public RenderData
{
public:
    RenderCube() {}
    RenderCube(std::vector<float> Vertices, std::vector<int> Indices, std::string Name) : RenderData(Vertices, Indices, Name) {}
    RenderCube(std::string Name);

    void ConfigData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) override;
    void Draw() override;
private:
    unsigned int texture1;
    unsigned int texture2;
};