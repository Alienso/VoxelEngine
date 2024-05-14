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
#include "InputHandler.h"

#include <iostream>

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    GraphicsConfiguration::fov -= (float)yoffset;
    if (GraphicsConfiguration::fov < 1.0f)
        GraphicsConfiguration::fov = 1.0f;
    if (GraphicsConfiguration::fov > GraphicsConfiguration::fovMax)
        GraphicsConfiguration::fov = GraphicsConfiguration::fovMax;
}

void GLAPIENTRY glErrorCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ){
    if (type != GL_DEBUG_TYPE_ERROR)
        return;
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", "** GL ERROR **", type, severity, message );
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    Configuration::windowWidth = width;
    Configuration::windowHeight = height;
}

void AppName::initGlfw(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Global::window = glfwCreateWindow(Configuration::windowWidth, Configuration::windowHeight, "Voxel", glfwGetPrimaryMonitor(), nullptr);
    Global::window = glfwCreateWindow(Configuration::windowWidth, Configuration::windowHeight, "Voxel", nullptr, nullptr);
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

    /*
     * OpenGl context is on main thread, maybe it can be moved to another?
     * Glfw polling must be done on main thread https://discourse.glfw.org/t/multithreading-glfw/573/2
     * When updating terrain, and when mesh is being generated calls are being made to openGl when creating BufferData,
     * so it currently breaks
     */

    terrainUpdateThread = std::thread([this] {
        while(shouldContinue) {
            this->world->updateTerrain();
        }
    });

    this_thread::sleep_for(std::chrono::milliseconds(300));

    lastLogicTime = lastMainTime = glfwGetTime();

    logicThread = std::thread([this] {
        while(shouldContinue) {
            world->onUpdate(glfwGetTime() - lastLogicTime);
            lastLogicTime = glfwGetTime();
        }
    });

}

void AppName::mainLoop() {

    while (shouldContinue) {

        shouldContinue = !glfwWindowShouldClose(Global::window);

        //PROFILE_SCOPE("mainLoop");
        glfwPollEvents();

        InputHandler::processKeyboardInput(glfwGetTime() - lastMainTime);
        InputHandler::processMouseInput();

        lastMainTime = glfwGetTime();

        world->updateBufferData();

        world->onRender();
        renderImGui();
        glfwSwapBuffers(Global::window);
    }
}

void AppName::cleanup() {

    /*terrainUpdateThread.join(); //TODO deadlock?
    logicThread.join();*/

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}