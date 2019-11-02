#include <iostream>
#include <tuple>

#include "main_elements/game_controller.h"

int main() {
    LibraryLoader libraryLoader;
    libraryLoader.initLibraries();

    try {
        WindowManager windowManager{{1920, 1080}, libraryLoader};
        Camera camera{90, 16.0f / 9.0f};
        GameController gameController{windowManager, camera};

        gameController.run();
    } catch (const std::runtime_error &error) {
        std::cout << error.what() << std::endl;
    }

    libraryLoader.closeLibraries();
    return EXIT_SUCCESS;
}