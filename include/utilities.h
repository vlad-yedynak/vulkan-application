#ifndef INC_3D_ENGINE_UTILITIES_H
#define INC_3D_ENGINE_UTILITIES_H

#include <vulkan/vulkan.h>

#include <vector>
#include <string>

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator);

std::vector<char> readFile(const std::string& filename);

#endif //INC_3D_ENGINE_UTILITIES_H
