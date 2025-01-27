#include "display/RenderRectangle.hpp"

RenderRectangle::RenderRectangle(std::string Name) : RenderData()
{
    this->Vertices = 
    {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    this->Indices = 
    {
        0, 1, 3,
        1, 2, 3
    };

    this->Name = Name;
}

void RenderRectangle::ConfigData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
     // Create Vertex Array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // And bind it

    // Create Vertex Buffer object
    glGenBuffers(1, &VBO);
    // And bind it (this also includes it into the VAO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Fill the VBO with vertex data, simply positions
    glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(float), this->Vertices.data(), GL_STATIC_DRAW);

    // layout = 0 should contain these positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Enable that shit

    // Create index buffer
    glGenBuffers(1, &EBO);
    // And bind it (also included in VAO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Fill with indices!
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(int), this->Indices.data(), GL_STATIC_DRAW);
}

void RenderRectangle::Draw()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}