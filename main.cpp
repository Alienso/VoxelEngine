
#include <iostream>
#include <cstdlib>

#include "source/AppName.h"

int main(int argc, char** argv) {
    AppName app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}