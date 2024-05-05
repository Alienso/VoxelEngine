//
// Created by Alienso on 14.4.2023..
//

#include "FrameBuffer.h"
#include "Configuration.h"

#include <iostream>

#include "glad.h"

FrameBuffer::FrameBuffer(FrameBufferType type) {
    glGenFramebuffers(1, &rendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, rendererID);

    switch (type) {
        case FRAME_BUFFER_REGULAR:
            createTexture();
            break;
        case FRAME_BUFFER_SHADOW:
            createShadowTexture();
            break;
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    glBindTexture(GL_TEXTURE_2D, 0);
    unbind();
}

FrameBuffer::~FrameBuffer() {
    glDeleteBuffers(1,&rendererID);
}

void FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
}

void FrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bindTexture(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
}

void FrameBuffer::createTexture(){
    glGenTextures(1, &renderedTexture);
    glGenTextures(1, &depthTexture);

    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Configuration::windowWidth, Configuration::windowHeight, 0, GL_RGB, GL_FLOAT, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D); //TODO this is required?

    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, depthTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Configuration::windowWidth, Configuration::windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, renderedTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
}

void FrameBuffer::createShadowTexture(){
    glGenTextures(1, &renderedTexture);

    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Configuration::windowWidth, Configuration::windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, renderedTexture, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

void FrameBuffer::generateMipMaps() const {
    glGenerateMipmap(GL_TEXTURE_2D);
}
