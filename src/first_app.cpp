#include "first_app.hpp"
#include "GLFW/glfw3.h"
#include "gef_device.hpp"
#include "gef_pipeline.hpp"

namespace gef {

FirstApp::FirstApp() : 
	gefWindow{WIDTH, HEIGHT, "FirstAppName"}, 
	gefDevice{gefWindow},
	gefPipeLine{gefDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", 
		GefPipeLine::defaultPipelineConfigInfo(WIDTH, HEIGHT)} {/*empty*/}

void FirstApp::run() {
    while(!gefWindow.shouldClose()) {
        glfwPollEvents();
    }
}

}  // namespace gef
