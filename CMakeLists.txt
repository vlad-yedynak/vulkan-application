cmake_minimum_required(VERSION 3.27)
project(3d_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(3d_engine tests/main.cpp
        src/HelloTriangleApplication.cpp
        include/HelloTriangleApplication.h
        include/utilities.h
        src/utilities.cpp)

find_package(Vulkan REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${Vulkan_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
target_link_libraries(3d_engine ${Vulkan_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_INCLUDE_DIRS})
