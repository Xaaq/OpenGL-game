#include <stdexcept>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window_manager.h"

WindowManager::WindowManager(std::tuple<int, int> window_dimensions, const LibraryLoader &libraryLoader) {
    const auto width = std::get<0>(window_dimensions);
    const auto height = std::get<1>(window_dimensions);

    this->window = WindowManager::createWindow(width, height);
    libraryLoader.initGlad();

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(this->window, resizeCallback);
}

WindowManager::~WindowManager() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

int WindowManager::getKeyState(int key) const {
    return glfwGetKey(this->window, key);
}

bool WindowManager::shouldWindowClose() const {
    return static_cast<bool>(glfwWindowShouldClose(this->window));
}

void WindowManager::swapBuffers() const {
    glfwSwapBuffers(this->window);
}

GLFWwindow *WindowManager::createWindow(int width, int height) {
    GLFWwindow *window = glfwCreateWindow(width, height, "My project", nullptr, nullptr);

    if (window == nullptr)
        throw std::runtime_error{"Failed to create window"};

    glfwMakeContextCurrent(window);
    return window;
}

void WindowManager::resizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
