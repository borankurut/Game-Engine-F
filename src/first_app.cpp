#include "first_app.hpp"
#include <memory>
#include <stdexcept>
#include "GLFW/glfw3.h"
#include "gef_device.hpp"
#include "gef_pipeline.hpp"
#include "vulkan/vulkan_core.h"

namespace gef {

FirstApp::FirstApp() : gefWindow{WIDTH, HEIGHT, "FirstAppName"}, gefDevice{gefWindow} {
	createPipelineLayout();
	createPipeline();
	createCommandBuffers();
}

FirstApp::~FirstApp(){
	vkDestroyPipelineLayout(gefDevice.device(), pipelineLayout, nullptr);
}

void FirstApp::run() {
    while(!gefWindow.shouldClose()) {
        glfwPollEvents();
    }
}

void FirstApp::createPipelineLayout(){
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pSetLayouts = nullptr;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;
	if(vkCreatePipelineLayout(gefDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout)){
		throw std::runtime_error("failed to create pipeline layout!");
	}

}

void FirstApp::createPipeline(){
	auto pipelineConfig = GefPipeline::defaultPipelineConfigInfo(gefSwapChain.width(), gefSwapChain.height());
	pipelineConfig.renderPass = gefSwapChain.getRenderPass();
	pipelineConfig.pipelineLayout = pipelineLayout;

	gefPipeline = std::make_unique<GefPipeline>(
		gefDevice,
		"shaders/simple_shader.vert.spv",
		"shaders/simple_shader.frag.spv",
		pipelineConfig
	);
}

void FirstApp::createCommandBuffers(){}

void FirstApp::drawFrame(){}

}  // namespace gef
