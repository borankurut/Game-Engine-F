include(./.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)
message(STATUS "Local .env.cmake: ${LOCAL_ENV}")

# Minimum version of CMake required
cmake_minimum_required(VERSION 3.27)


# Project name
project(Game-Engine-F)


set(Vulkan_INCLUDE_DIRS "${VULKAN_SDK_PATH}/Include") # 1.1 Make sure this include path is correct
set(Vulkan_LIBRARIES "${VULKAN_SDK_PATH}/Lib") # 1.2 Make sure lib path is correct


set(GLFW_INCLUDE_DIRS "${GLFW_PATH}/include")
set(GLFW_LIB "${GLFW_PATH}/lib-vc2022") # 2.1 Update lib-vc2019 to use same version as your visual studio

include_directories(external)

set(TINYOBJ_PATH external/tinyobjloader)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Add your source files
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build")


target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${Vulkan_INCLUDE_DIRS}
  ${TINYOBJ_PATH}
  ${GLFW_INCLUDE_DIRS}
  ${GLM_PATH}
)

target_link_directories(${PROJECT_NAME} PUBLIC
  ${Vulkan_LIBRARIES}
  ${GLFW_LIB}
)

target_link_libraries(${PROJECT_NAME} glfw3 vulkan-1)

