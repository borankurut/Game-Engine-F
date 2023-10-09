#pragma once

#include "gef_window.hpp"
#include "gef_pipeline.hpp"

namespace gef {

class FirstApp {
   public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    FirstApp();

    void run();

   private:
    GefWindow gefWindow;
	GefPipeLine gefPipeLine;

};

}  // namespace gef
