#pragma once

#include "gef_window.hpp"
namespace gef {

class FirstApp {
   public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    FirstApp();

    void run();

   private:
    GefWindow gefWindow;
};

}  // namespace gef
