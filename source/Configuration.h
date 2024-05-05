//
// Created by Alienso on 23.9.2022..
//

#ifndef GRASSTERRAIN_CONFIGURATION_H
#define GRASSTERRAIN_CONFIGURATION_H

struct GraphicsConfiguration{

    static float fov;
    static float fovMax;

    static int renderDistance;

    static float fogStrength;
    static int fogDistance;
    static float bloomThreshold;
    static int bloomDecay;

    static float contrast;
    static float brightness;
    static float saturation;
    static float gamma;

    static int shadowWidth;
    static int shadowHeight;
};

class Configuration{

public:
    static int windowWidth;
    static int windowHeight;

    static GraphicsConfiguration graphicsConfiguration;

    Configuration()= default;
};

#endif //GRASSTERRAIN_CONFIGURATION_H
