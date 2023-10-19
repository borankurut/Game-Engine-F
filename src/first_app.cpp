#include "first_app.hpp"
#include <stdint.h>
#include <array>
#include <memory>
#include <stdexcept>
#include <string>
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
		drawFrame();
    }
	vkDeviceWaitIdle(gefDevice.device());
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

void FirstApp::createCommandBuffers(){
	commandBuffers.resize(gefSwapChain.imageCount());
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = gefDevice.getCommandPool();
	allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
	
	if(vkAllocateCommandBuffers(gefDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS){
		throw std::runtime_error("failed to create command buffers!");
	}

	for(int i = 0; i < commandBuffers.size(); ++i){
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		
		if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS){
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = gefSwapChain.getRenderPass();
		renderPassInfo.framebuffer = gefSwapChain.getFrameBuffer(i);
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = gefSwapChain.getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
		clearValues[1].depthStencil = {1.0f, 0};

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		gefPipeline->bind(commandBuffers[i]);
		vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffers[i]);
		if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS){
			throw std::runtime_error("failed to record command buffer!");
		}
	}
}

void FirstApp::drawFrame(){
	uint32_t imageIx;
	auto result = gefSwapChain.acquireNextImage(&imageIx);
	if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	result = gefSwapChain.submitCommandBuffers(&commandBuffers[imageIx], &imageIx);
	if(result != VK_SUCCESS){
		throw std::runtime_error("failed to present swap chain image!");
	}
}

}  // namespace gef
