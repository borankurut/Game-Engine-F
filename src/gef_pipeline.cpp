#include "gef_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace gef {

GefPipeLine::GefPipeLine(const std::string& vertFilepath, const std::string& fragFilepath) {
	createGraphicsPipeline(vertFilepath, fragFilepath);
}

std::vector<char> GefPipeLine::readFile(const std::string& filepath){
	std::ifstream file{filepath, std::ios::ate | std::ios::binary};

	if(!file.is_open()){
		throw std::runtime_error("Can't open file: " + filepath);
	}

	size_t size = static_cast<size_t>(file.tellg());

	std::vector<char> buffer(size);

	file.seekg(0);
	file.read(buffer.data(), size);

	file.close();
	return buffer;
}

void GefPipeLine::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath){
	auto vertCode = readFile(vertFilepath);
	auto fragCode = readFile(fragFilepath);

	std::cout << "Vertex shader code size: " << vertCode.size() << "\n";
	std::cout << "Fragment shader code size: " << fragCode.size() << "\n";

}

}  // namespace gef
