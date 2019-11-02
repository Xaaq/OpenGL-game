#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "library_loader.h"

void LibraryLoader::initGlad() const {
    const auto loadResult = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    if (loadResult == 0)
        throw std::runtime_error{"Glad loading failed"};
}

void LibraryLoader::initLibraries() const {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    TODO: zrobic zeby glad byl w wersji 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void LibraryLoader::closeLibraries() const {
    glfwTerminate();
}
