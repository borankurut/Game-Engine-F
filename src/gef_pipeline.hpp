#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include "gef_device.hpp"
#include "vulkan/vulkan_core.h"

namespace gef {

struct PipelineConfigInfo {
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
};

class GefPipeline {

   public:
    GefPipeline(GefDevice& device, const std::string& vertFilepath, const std::string& fragFilepath,
                const PipelineConfigInfo& config);

    ~GefPipeline();

    GefPipeline(const GefPipeline&) = delete;
    void operator=(const GefPipeline&) = delete;

    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

	void bind(VkCommandBuffer commandBuffer);

   private:
    static std::vector<char> readFile(const std::string& filepath);

    void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath,
                                const PipelineConfigInfo& configInfo);

    void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

    GefDevice& gefDevice;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
};

}  // namespace gef
