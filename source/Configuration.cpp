//
// Created by Alienso on 23.9.2022..
//
#include "Configuration.h"

int Configuration:: windowWidth = 1600;
int Configuration:: windowHeight = 900;

GraphicsConfiguration Configuration::graphicsConfiguration;

float GraphicsConfiguration::fov = 60.0f;
float GraphicsConfiguration::fovMax = 100.0f;

int GraphicsConfiguration::shadowWidth = 1600;
int GraphicsConfiguration::shadowHeight = 900;

int GraphicsConfiguration::renderDistance = 6;

float GraphicsConfiguration::fogStrength = 1.0f;
int GraphicsConfiguration::fogDistance = 16;
float GraphicsConfiguration::bloomThreshold = 1.1f;
int GraphicsConfiguration::bloomDecay = 8;

float GraphicsConfiguration::contrast = 1.0f;
float GraphicsConfiguration::brightness = 0.0f;
float GraphicsConfiguration::saturation = 1.0f;
float GraphicsConfiguration::gamma = 1.0f;