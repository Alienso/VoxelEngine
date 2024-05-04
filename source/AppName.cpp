//
// Created by Alienson on 16.4.2024..
//

#include "AppName.h"

#include "glad.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Global.h"
#include "Configuration.h"
#include "util/Profiler.h"
#include "world/Blocks.h"

#include <iostream>

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    Configuration::fov -= (float)yoffset;
    if (Configuration::fov < 1.0f)
        Configuration::fov = 1.0f;
    if (Configuration::fov > Configuration::fovMax)
        Configuration::fov = Configuration::fovMax;
}

void GLAPIENTRY glErrorCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ){
    if (type != GL_DEBUG_TYPE_ERROR)
        return;
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", "** GL ERROR **", type, severity, message );
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    Configuration::wWidth = width;
    Configuration::wHeight = height;
}

void AppName::initGlfw(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Global::window = glfwCreateWindow(Configuration::wWidth,Configuration::wHeight, "Test 3D", nullptr, nullptr);
    if (Global::window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(Global::window);
    glfwSetFramebufferSizeCallback(Global::window, framebuffer_size_callback);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glfwSetScrollCallback(Global::window, scrollCallback);
    glfwSetInputMode(Global::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void AppName::initImGui(){
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Global::window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    ImGui::StyleColorsDark();
}

void AppName::renderImGui(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    world->onImGuiRender();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void AppName::run() {
    init();
    mainLoop();
    cleanup();
}

void AppName::init() {
    initGlfw();
    initImGui();

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( glErrorCallback, nullptr );
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    srand((unsigned int)glfwGetTime());

    initAssets();
    Blocks::init();
    Global::init();
    world = new World();
    Global::world = world;
}

void AppName::mainLoop() {

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(Global::window)) {

        PROFILE_SCOPE("mainLoop");
        glfwPollEvents();

        world->onUpdate(glfwGetTime() - lastTime);
        lastTime = glfwGetTime();

        world->onRender();

        renderImGui();

        glfwSwapBuffers(Global::window);
    }
}

void AppName::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}