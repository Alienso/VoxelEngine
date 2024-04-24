//
// Created by Alienso on 23.9.2022..
//

#ifndef GRASSTERRAIN_CONFIGURATION_H
#define GRASSTERRAIN_CONFIGURATION_H

class Configuration{

public:
    static int wWidth;
    static int wHeight;
    static float fov;
    static float fovMax;

    static int shadowWidth;
    static int shadowHeight;

    Configuration()= default;
};

#endif //GRASSTERRAIN_CONFIGURATION_H
