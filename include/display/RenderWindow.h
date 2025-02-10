#pragma once

#include "glad.h"
#include "glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <iostream>
#include <display/Camera.h>
#include <map>
#include <shaders/shader.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class RenderWindow 
{
public:
    int Width;
    int Height;
    std::string Title;
    GLFWwindow* WindowHandle;

    RenderWindow();
    RenderWindow(int width, int height, std::string title);
    int Run();

private:

    Camera* CurrentCamera;
    float CurrentFrame, DeltaTime, LastFrame;
    float LastX = Width / 2.0f;
    float LastY = Height / 2.0f;

    bool FirstMouse = true;


    static void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
    {
        glViewport(0, 0, Width, Height);
    }

    void ProcessInput(GLFWwindow* Window)
    {
        if(glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(Window, true);
        }

        if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
            CurrentCamera->ProcessKeyboard(ECameraMovement::FORWARD, DeltaTime);
        if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
            CurrentCamera->ProcessKeyboard(ECameraMovement::BACKWARD, DeltaTime);
        if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
            CurrentCamera->ProcessKeyboard(ECameraMovement::LEFT, DeltaTime);
        if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
            CurrentCamera->ProcessKeyboard(ECameraMovement::RIGHT, DeltaTime);
    }

    static void CursorPosCallback(GLFWwindow* Window, double xpos, double ypos)
    {
        RenderWindow* Instance = static_cast<RenderWindow*>(glfwGetWindowUserPointer(Window));
        if(Instance)
        {
            Instance->MouseCallback(xpos, ypos);
        }
    }

    void MouseCallback(double XPosIn, double YPosIn)
    {
        float Xpos = static_cast<float>(XPosIn);
        float Ypos = static_cast<float>(YPosIn);

        if(FirstMouse)
        {
            LastX = Xpos;
            LastY = Ypos;
            FirstMouse = false;
        }

        float Xoffset = Xpos - LastX;
        float Yoffset = LastY - Ypos;

        LastX = Xpos;
        LastY = Ypos;

        CurrentCamera->ProcessMouseMovement(Xoffset, Yoffset);
    }

    // all the shaders used by objects in one scene
    std::map<std::string, Shader> Shaders;
    // shaders relative vaos
    std::map<std::string, unsigned int> VAOs;

protected:
    virtual void LoadShaders();
    virtual void Setup();
    virtual void Render();
};