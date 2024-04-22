//
// Created by Alienson on 21.4.2024..
//

#include "InputHandler.h"
#include "Global.h"

void InputHandler::processMouseInput() {

    if (glfwGetInputMode(Global::window,GLFW_CURSOR) == GLFW_CURSOR_NORMAL){
        return;
    }

    double xposIn,yposIn;
    glfwGetCursorPos(Global::window,&xposIn,&yposIn);

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (Global::camera.firstMouse){
        Global::camera.lastPos[0] = xpos;
        Global::camera.lastPos[1] = ypos;
        Global::camera.firstMouse = false;
    }

    float xoffset = xpos - Global::camera.lastPos[0];
    float yoffset = Global::camera.lastPos[1] - ypos;
    Global::camera.lastPos[0] = xpos;
    Global::camera.lastPos[1] = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Global::camera.yaw += xoffset;
    Global::camera.pitch += yoffset;

    if (Global::camera.pitch > 89.0f)
        Global::camera.pitch = 89.0f;
    if (Global::camera.pitch < -89.0f)
        Global::camera.pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(Global::camera.yaw)) * cos(glm::radians(Global::camera.pitch));
    front.y = sin(glm::radians(Global::camera.pitch));
    front.z = sin(glm::radians(Global::camera.yaw)) * cos(glm::radians(Global::camera.pitch));
    Global::camera.front = glm::normalize(front);
}

void InputHandler::processKeyboardInput(float deltaTime){
    if (glfwGetKey(Global::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        int mode = glfwGetInputMode(Global::window,GLFW_CURSOR);
        glfwSetInputMode(Global::window, GLFW_CURSOR, mode == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        Global::camera.firstMouse = true;
    }
    else if (glfwGetKey(Global::window, GLFW_KEY_Q) == GLFW_PRESS){
        glfwSetWindowShouldClose(Global::window, true);
    }

    float cameraSpeed = 20.0f * deltaTime;
    if (glfwGetKey(Global::window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraSpeed /=3;

    if (glfwGetKey(Global::window, GLFW_KEY_G) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(Global::window, GLFW_KEY_F) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(Global::window, GLFW_KEY_W) == GLFW_PRESS)
        Global::camera.pos += cameraSpeed * Global::camera.front;
    if (glfwGetKey(Global::window, GLFW_KEY_S) == GLFW_PRESS)
        Global::camera.pos -= cameraSpeed * Global::camera.front;
    if (glfwGetKey(Global::window, GLFW_KEY_A) == GLFW_PRESS)
        Global::camera.pos -= glm::normalize(glm::cross(Global::camera.front, Global::camera.up)) * cameraSpeed;
    if (glfwGetKey(Global::window, GLFW_KEY_D) == GLFW_PRESS)
        Global::camera.pos += glm::normalize(glm::cross(Global::camera.front, Global::camera.up)) * cameraSpeed;
    if (glfwGetKey(Global::window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Global::camera.pos += cameraSpeed * glm::vec3(0.0f,1.0f,0.0f);
    if (glfwGetKey(Global::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        Global::camera.pos += cameraSpeed * glm::vec3(0.0f,-1.0f,0.0f);
}