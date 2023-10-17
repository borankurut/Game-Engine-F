#include "gef_window.hpp"
#include <stdexcept>
#include "GLFW/glfw3.h"
#include "vulkan/vulkan_core.h"

namespace gef {

GefWindow::GefWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
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

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

void GefWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
	if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
		throw std::runtime_error("failed to create window surface.");
	}
}

}  // namespace gef
