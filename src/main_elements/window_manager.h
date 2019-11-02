#ifndef MY_GAME_WINDOW_MANAGER_H
#define MY_GAME_WINDOW_MANAGER_H


#include <GLFW/glfw3.h>

#include "utils/library_loader.h"

class WindowManager {
public:
    explicit WindowManager(std::tuple<int, int> window_dimensions, const LibraryLoader &libraryLoader);

    virtual ~WindowManager();

    [[nodiscard]] int getKeyState(int key) const;

    [[nodiscard]] bool shouldWindowClose() const;

    void swapBuffers() const;

private:
    GLFWwindow *window;

    static GLFWwindow *createWindow(int width, int height);

    static void resizeCallback(GLFWwindow *window, int width, int height);
};


#endif // MY_GAME_WINDOW_MANAGER_H
