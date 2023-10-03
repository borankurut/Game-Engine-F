#include "first_app.hpp"
#include "GLFW/glfw3.h"

namespace gef {

FirstApp::FirstApp() : gefWindow{WIDTH, HEIGHT, "FirstAppName"} {/*empty*/}


void FirstApp::run() {
    while(!gefWindow.shouldClose()) {
        glfwPollEvents();
    }
}

}  // namespace gef
