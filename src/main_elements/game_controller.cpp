#include <iostream>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "world_object.h"
#include "game_controller.h"
#include "shaders/shader_factory.h"
#include "meshes/mesh_factory.h"
#include "light/light_source.h"

GameController::GameController(const WindowManager &windowManager, const Camera &camera)
        : windowManager(windowManager), camera(camera) {
    glEnable(GL_DEPTH_TEST);
}

void GameController::run() const {
    ShaderFactory shaderFactory;
    auto basicShaderProgram = shaderFactory.createShaderProgram("basic");
    auto lightSourceShaderProgram = shaderFactory.createShaderProgram("light_source");

    MeshFactory meshLoader;
    std::shared_ptr<Renderable> mesh1 = meshLoader.loadMesh("model.obj");
    std::shared_ptr<Renderable> mesh2 = meshLoader.loadMesh("kostka.obj");

    WorldObject object1{mesh1};
    object1.setPosition(glm::vec3{8, 0, 0});

    auto object2 = std::make_unique<WorldObject>(mesh2);
    LightSource lightSource{std::move(object2), glm::vec3{0, 4, 1}, glm::vec3{1, 1, 1}};

    while (!this->windowManager.shouldWindowClose()) {
        this->clearScreen();
        this->processKeyboardInput();

        lightSource.shineLight(basicShaderProgram);

        camera.updateShader(basicShaderProgram);
        camera.updateShader(lightSourceShaderProgram);

        object1.render(basicShaderProgram);
        lightSource.render(lightSourceShaderProgram);

        this->windowManager.swapBuffers();
        glfwPollEvents();
    }
}

void GameController::processKeyboardInput() const {
    if (this->windowManager.getKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        std::cout << "nacisniety" << std::endl;
}

void GameController::clearScreen() const {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
