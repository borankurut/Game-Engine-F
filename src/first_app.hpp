#pragma once

#include <memory>
#include <vector>
#include "gef_device.hpp"
#include "gef_swap_chain.hpp"
#include "gef_window.hpp"
#include "gef_pipeline.hpp"
#include "vulkan/vulkan_core.h"

namespace gef {

class FirstApp {
   public:
    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;
    FirstApp();
	~FirstApp();

	FirstApp(const FirstApp&) = delete;
    FirstApp& operator=(const FirstApp&) = delete;

    void run();

   private:

	void createPipelineLayout();
	void createPipeline();
	void createCommandBuffers();
	void drawFrame();

    GefWindow gefWindow;
	GefDevice gefDevice;
	GefSwapChain gefSwapChain{gefDevice, gefWindow.getExtent()};
	std::unique_ptr<GefPipeline>gefPipeline;
	VkPipelineLayout pipelineLayout;
	std::vector<VkCommandBuffer> commandBuffers;

};

}  // namespace gef
