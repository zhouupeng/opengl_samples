#include "display/RenderData.hpp"
#include <iostream>

RenderData::RenderData() {}

RenderData::RenderData(std::vector<float> Vertices, std::vector<int> Indices, std::string Name)
{
    this->Vertices = Vertices;
    this->Indices = Indices;
    this->Name = Name;
}

RenderData::~RenderData()
{
    std::cout << "RenderData::~RenderData()" << std::endl;
}

void RenderData::LoadShader(std::string VertexShader, std::string FragmentShader)
{
    this->Shader = Shader::LoadShader(VertexShader, FragmentShader);
}