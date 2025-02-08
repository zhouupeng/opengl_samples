#include "display/game_window.hpp"
#include "shaders/shader.hpp"
#include <iostream>
#include "display/RenderTriangle.hpp"
#include "display/RenderRectangle.hpp"
#include "display/RenderRectangleUseTexture.hpp"
#include "display/RenderRectangleUseMixedTexture.hpp"
#include "display/RenderCube.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Template stuff
Shader s;
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

GameWindow::GameWindow(int width, int height, std::string title) : BaseWindow(width, height, title)
{
    this->TriangleData = new RenderTriangle("Triangle");
    this->RectangleData = new RenderRectangle("Rectangle");
    this->TextureData = new RenderRectangleUseTexture("Texture");
    this->MixedTextureData = new RenderRectangleUseMixedTexture("MixedTexture");
    this->CubeData = new RenderCube("Cube");

    this->CurrentRenderData = RectangleData;
}

// Called whenever the window or framebuffer's size is changed
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float DeltaTime = 0.0f;
float LastFrame = 0.0f;

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float CameraSpeed = static_cast<float>(2.5f * DeltaTime);
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += CameraSpeed * cameraFront;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= CameraSpeed * cameraFront;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed;
    }
}

// 1. The first thing that is run when starting the window
void GameWindow::Initialize() {
    // Set GLFW stuff before window is created
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

// 2. Run after the window has been created, as well as the OpenGL context
void GameWindow::LoadContent() {
    // Set callback
    glfwSetFramebufferSizeCallback(this->windowHandle, FramebufferSizeCallback);

    // Initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    std::cout << "INFO::IMGUI::SUCCESSFULLY_INITIALIZED" << std::endl;

    // Load the template shader
    s = Shader::LoadShader("../resources/shaders/testing.vs", "../resources/shaders/testing.fs");
    //s = Shader::LoadShader("testing.vs", "testing.fs");

    // Vertices needed for a square
    float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    // Indices for rendering the above square
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create Vertex Array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // And bind it

    // Create Vertex Buffer object
    glGenBuffers(1, &VBO);
    // And bind it (this also includes it into the VAO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Fill the VBO with vertex data, simply positions
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout = 0 should contain these positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Enable that shit

    // Create index buffer
    glGenBuffers(1, &EBO);
    // And bind it (also included in VAO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Fill with indices!
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void GameWindow::Update() {
    // Performs hot-reload of shader. Only reloads whenever it has been modified - so not every frame.
    s.ReloadFromFile();
}

void GameWindow::Render() {
    // Bind the VAO
    glBindVertexArray(VAO2);

    // Make sure we're using the correct shader program.
    // Must be done per-frame, since the shader program id might change when hot-reloading
    //glUseProgram(s.programID);
    glUseProgram(this->CurrentRenderData->Shader.programID);

    ProcessInput(this->windowHandle);
    // Create new imgui frames
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Clear the window
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the square
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    this->CurrentRenderData->Draw();

    // Draw imgui
    //ImGui::ShowDemoWindow();
    ShowRenderSettings();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap double buffers and poll OS-events
    glfwSwapBuffers(this->windowHandle);
    glfwPollEvents();
}

void GameWindow::Unload() {

    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteProgram(this->CurrentRenderData->Shader.programID);

    // Destroy imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GameWindow::ShowRenderSettings()
{

    if(!ImGui::Begin("Render Settings"))
    {
        ImGui::End();
        return;
    }
    
    if(ImGui::TreeNode("Render"))
    {
        static int clicked = 0;
        static int value = 0;        

        if(ImGui::Button("Triangle"))
        {
            ShowTriangle();
        }

        if(ImGui::Button("Rectangle"))
        {
            ShowRectangle();
        }

        if(ImGui::Button("Texture"))
        {
            ShowTexture();
        }

        if(ImGui::Button("Mixed Texture"))
        {
            ShowMixedTexture();
        }

        if(ImGui::Button("Cube"))
        {
            ShowCube();
        }
        ImGui::TreePop();
    }

    ImGui::End();
}

void GameWindow::LoadContent2()
{

    glfwSetFramebufferSizeCallback(this->windowHandle, FramebufferSizeCallback);

    // Initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    std::cout << "INFO::IMGUI::SUCCESSFULLY_INITIALIZED" << std::endl;

    // Load the template shader
    s = Shader::LoadShader("../resources/shaders/testing.vs", "../resources/shaders/testing.fs");
    //s = Shader::LoadShader("testing.vs", "testing.fs");
    CurrentRenderData->LoadShader("../resources/shaders/testing.vs", "../resources/shaders/testing.fs");
    

    float vertices[] = {
       -0.5f, -0.5f, 0.0f, // left  
        0.5f, -0.5f, 0.0f, // right 
        0.0f,  0.5f, 0.0f  // top   
    };
    CurrentRenderData->ConfigData(VAO2, VBO2, EBO2);

    //glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO); // And bind it

    // Create Vertex Buffer object
    //glGenBuffers(1, &VBO);
    // And bind it (this also includes it into the VAO)
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Fill the VBO with vertex data, simply positions
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout = 0 should contain these positions
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0); // Enable that shit

}

void GameWindow::Render2()
{

}

void GameWindow::ShowTriangle()
{
    this->CurrentRenderData = TriangleData;
    this->CurrentRenderData->LoadShader("../resources/shaders/testing.vs", "../resources/shaders/testing.fs");
    this->CurrentRenderData->ConfigData(VAO2, VBO2, EBO2);
}

void GameWindow::ShowRectangle()
{
    this->CurrentRenderData = RectangleData;
    this->CurrentRenderData->LoadShader("../resources/shaders/testing.vs", "../resources/shaders/testing.fs");
    this->CurrentRenderData->ConfigData(VAO2, VBO2, EBO2);
}

void GameWindow::ShowTexture()
{
    this->CurrentRenderData = TextureData;
    this->CurrentRenderData->LoadShader("../resources/shaders/use_texture.vs", "../resources/shaders/use_texture.fs");
    this->CurrentRenderData->ConfigData(VAO2, VBO2, EBO2);
}

void GameWindow::ShowMixedTexture()
{
    // or set it via the texture class
    this->CurrentRenderData = MixedTextureData;
    this->CurrentRenderData->LoadShader("../resources/shaders/use_texture_mixed.vs", "../resources/shaders/use_texture_mixed.fs");
    glUseProgram(this->CurrentRenderData->Shader.programID);
    glUniform1i(glGetUniformLocation(this->CurrentRenderData->Shader.programID, "ourTexture"), 0);
    glUniform1i(glGetUniformLocation(this->CurrentRenderData->Shader.programID, "ourTexture2"), 1);
    this->CurrentRenderData->ConfigData(VAO2, VBO2, EBO2);
}

void GameWindow::ShowCube()
{
    this->CurrentRenderData = CubeData;
    this->CurrentRenderData->LoadShader("../resources/shaders/render_cube.vs", "../resources/shaders/render_cube.fs");
    glUseProgram(this->CurrentRenderData->Shader.programID);
    glUniform1i(glGetUniformLocation(this->CurrentRenderData->Shader.programID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(this->CurrentRenderData->Shader.programID, "texture2"), 1);
    this->CurrentRenderData->ConfigData(VAO2, VBO2, EBO2);
    glEnable(GL_DEPTH_TEST);
}