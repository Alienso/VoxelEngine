//
// Created by Alienson on 23.4.2024..
//

#include "Util.h"
#include "glad.h"
#include "Global.h"
#include "Configuration.h"
#include "world/World.h"
#include "world/Blocks.h"

unsigned int Util::quadVAO = 0;
unsigned int Util::quadVBO;

void Util::renderTexture(unsigned int textureId){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    //Global::textureManager.getAsset(Textures::MOUNTAINS)->bind();
    Shader* textureShader = Global::shaderManager.getAsset(Shaders::TEXTURE);
    //Shader* textureShader = Global::shaderManager.getAsset(Shaders::TEXTURE_MONO);
    textureShader->use();
    textureShader->setInt("texture1", 0);
    renderQuad();
}

void Util::renderQuad(){
    if (quadVAO == 0){
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

Timer::Timer(const char *name)  : name(name){
    startTimePoint = std::chrono::steady_clock::now();
}
Timer::~Timer(){
    if (!stopped)
        stop();
}

void Timer::stop(){
    auto endTimePoint = std::chrono::steady_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTimePoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

    std::cout << name << " took " <<end - start << "ms\n";

    stopped = true;
}
