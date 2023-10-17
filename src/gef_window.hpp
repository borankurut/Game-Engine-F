#pragma once

#include <stdint.h>
#include "vulkan/vulkan_core.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace gef {

class GefWindow {
   public:
    GefWindow(int w, int h, std::string name);
    ~GefWindow();
    bool shouldClose(){return glfwWindowShouldClose(window);}
	VkExtent2D getExtent(){return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};}

	void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    GefWindow(const GefWindow&) = delete;
    GefWindow& operator=(const GefWindow&) = delete;


   private:
    void initWindow();
    const int height;
    const int width;
    std::string windowName;
    GLFWwindow* window;
};

}  // namespace gef
