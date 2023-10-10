#include "gef_pipeline.hpp"
#include <stdint.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include "vulkan/vulkan_core.h"

namespace gef {

GefPipeLine::GefPipeLine(GefDevice& device, const std::string& vertFilepath, const std::string& fragFilepath,
                         const PipelineConfigInfo& configInfo): gefDevice{device} {

    createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
}

GefPipeLine::~GefPipeLine(){/*todo*/}

std::vector<char> GefPipeLine::readFile(const std::string& filepath) {
    std::ifstream file{filepath, std::ios::ate | std::ios::binary};

    if(!file.is_open()) {
        throw std::runtime_error("Can't open file: " + filepath);
    }

    size_t size = static_cast<size_t>(file.tellg());

    std::vector<char> buffer(size);

    file.seekg(0);
    file.read(buffer.data(), size);

    file.close();
    return buffer;
}

void GefPipeLine::createGraphicsPipeline(const std::string& vertFilepath, 
										 const std::string& fragFilepath, const PipelineConfigInfo &configInfo) {
    auto vertCode = readFile(vertFilepath);
    auto fragCode = readFile(fragFilepath);

    std::cout << "Vertex shader code size: " << vertCode.size() << "\n";
    std::cout << "Fragment shader code size: " << fragCode.size() << "\n";
}


void GefPipeLine::createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule){
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
	if(vkCreateShaderModule(gefDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS){
		throw std::runtime_error("unable to create shader module");
	}
}

PipelineConfigInfo GefPipeLine::defaultPipelineConfigInfo(uint32_t width, uint32_t height){
	PipelineConfigInfo configInfo {};

	return configInfo;
}

}  // namespace gef

