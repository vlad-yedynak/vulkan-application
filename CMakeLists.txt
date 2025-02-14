cmake_minimum_required(VERSION 3.27)
project(3d_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(3d_engine tests/main.cpp
        src/VulkanApplication.cpp
        include/VulkanApplication.h
        include/utilities.h
        src/utilities.cpp)

find_package(Vulkan REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${Vulkan_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
target_link_libraries(3d_engine ${Vulkan_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_INCLUDE_DIRS})

if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "VULKAN_SDK is not set. Please ensure Vulkan SDK is installed and the environment variable is configured.")
endif()

set(VULKAN_GLSLC "$ENV{VULKAN_SDK}/bin/glslc")

set(SHADER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(SHADER_BINARY_DIR ${CMAKE_SOURCE_DIR}/shaders-spv)

file(MAKE_DIRECTORY ${SHADER_BINARY_DIR})
file(GLOB_RECURSE SHADERS "${SHADER_SOURCE_DIR}/*.*")

set(SPIRV_SHADERS "")
foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(SPIRV_SHADER ${SHADER_BINARY_DIR}/${SHADER_NAME}.spv)

    add_custom_command(
            OUTPUT ${SPIRV_SHADER}
            COMMAND ${VULKAN_GLSLC} ${SHADER} -o ${SPIRV_SHADER}
            DEPENDS ${SHADER}
            COMMENT "Compiling shader: ${SHADER_NAME}"
            VERBATIM
    )

    list(APPEND SPIRV_SHADERS ${SPIRV_SHADER})
endforeach()

add_custom_target(Shaders DEPENDS ${SPIRV_SHADERS})
add_dependencies(3d_engine Shaders)
