#include "gef_window.hpp"
#include "GLFW/glfw3.h"

namespace gef {

GefWindow::GefWindow(int w, int h, std::string name)
    : width{w}, height{h}, windowName{name} {
    initWindow();
}

GefWindow::~GefWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GefWindow::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window =
        glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

bool GefWindow::shouldClose() {
    return glfwWindowShouldClose(window);
}

}  // namespace gef
