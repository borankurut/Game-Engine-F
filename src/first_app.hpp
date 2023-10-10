#pragma once

#include "gef_device.hpp"
#include "gef_window.hpp"
#include "gef_pipeline.hpp"

namespace gef {

class FirstApp {
   public:
    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;
    FirstApp();

    void run();

   private:
    GefWindow gefWindow;
	GefPipeLine gefPipeLine;
	GefDevice gefDevice;

};

}  // namespace gef
