#pragma once

#include "glad.h"
#include "glfw3.h"
#include <string>
#include <iostream>
#include <glm.hpp>


class Shader {
    public:
    unsigned int programID;
    std::string vertexFile;
    std::string fragmentFile;

    long fragmentModTimeOnLoad;

    Shader();
    void Unload();
    void ReloadFromFile();
    static Shader LoadShader(std::string fileVertexShader, std::string fileFragmentShader);

    private:
    static bool CompileShader(unsigned int shaderId, char(&infoLog)[512]);
    static bool LinkProgram(unsigned int programID, char(&infoLog)[512]);
public:
    void use() const
    {
        glUseProgram(programID);
    }

    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
    }

     void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};