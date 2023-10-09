#include "first_app.hpp"
#include "GLFW/glfw3.h"
#include "gef_pipeline.hpp"

namespace gef {

FirstApp::FirstApp() : 
	gefWindow{WIDTH, HEIGHT, "FirstAppName"}, 
	gefPipeLine{"shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv"} {/*empty*/}

void FirstApp::run() {
    while(!gefWindow.shouldClose()) {
        glfwPollEvents();
    }
}

}  // namespace gef
