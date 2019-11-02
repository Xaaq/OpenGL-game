#ifndef MY_GAME_GAME_CONTROLLER_H
#define MY_GAME_GAME_CONTROLLER_H


#include "window_manager.h"
#include "camera.h"

class GameController {
public:
    explicit GameController(const WindowManager &windowManager, const Camera &camera);

    void run() const;

private:
    const WindowManager &windowManager;
    const Camera &camera;

    void processKeyboardInput() const;

    void clearScreen() const;
};


#endif // MY_GAME_GAME_CONTROLLER_H
