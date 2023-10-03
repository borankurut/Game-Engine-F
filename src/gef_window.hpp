#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace gef {

class GefWindow {
   public:
    GefWindow(int w, int h, std::string name);
    ~GefWindow();
    bool shouldClose();

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
