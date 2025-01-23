#include "display/game_window.hpp"
#include "shaders/shader.hpp"
#include <iostream>

// Template stuff
Shader s;
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

GameWindow::GameWindow(int width, int height, std::string title) : BaseWindow(width, height, title)
{
}

// Called whenever the window or framebuffer's size is changed
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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
    glBindVertexArray(VAO);

    // Make sure we're using the correct shader program.
    // Must be done per-frame, since the shader program id might change when hot-reloading
    glUseProgram(s.programID);

    // Create new imgui frames
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Clear the window
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the square
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Draw imgui
    //ImGui::ShowDemoWindow();
    //ShowRenderSettings();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap double buffers and poll OS-events
    glfwSwapBuffers(this->windowHandle);
    glfwPollEvents();
}

void GameWindow::Unload() {

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(s.programID);

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
    
    if(ImGui::TreeNode("Draw Triangle"))
    {

        static int clicked = 0;

        static int value = 0;        

        //printf("value %d\n", value);

     
        static float vec3[3];
        ImGui::InputFloat3("Vertex ", vec3);
        ImGui::SameLine(); 


        if(ImGui::Button("Button"))
        {
            []() mutable
            {
                value++;
                ImGui::Text("Button Click %d\n", value);
                vec3[0] += 0.01f;
            }();
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


    float vertices[] = {
       -0.5f, -0.5f, 0.0f, // left  
        0.5f, -0.5f, 0.0f, // right 
        0.0f,  0.5f, 0.0f  // top   
    };

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

}

void GameWindow::Render2()
{

}