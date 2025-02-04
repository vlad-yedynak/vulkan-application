#ifndef INC_3D_ENGINE_HELLOTRIANGLEAPPLICATION_H
#define INC_3D_ENGINE_HELLOTRIANGLEAPPLICATION_H

#include <vulkan/vulkan.h>
#include <SDL.h>

#include <vector>
#include <optional>

const uint32_t X_POS = 0;
const uint32_t Y_POS = 0;
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class HelloTriangleApplication {
public:
    void run();

private:
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };

    VkInstance instance = VK_NULL_HANDLE;
    SDL_Window *window = nullptr;
    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;

    VkQueue graphicsQueue = VK_NULL_HANDLE;

    void initWindow();

    void initVulkan();

    void mainLoop();

    void cleanup();

    void createInstance();

    bool checkValidationLayerSupport();

    void setupDebugMessenger();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    static VKAPI_ATTR VkBool32 VKAPI_CALL
    debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                  VkDebugUtilsMessageTypeFlagsEXT messageType,
                  const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                  void *pUserData);

    void pickPhysicalDevice();

    void createLogicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice dvc);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dvc);

    std::vector<const char *> getRequiredInstanceExtensions();

    std::vector<const char *> getRequiredDeviceExtensions();
};

#endif //INC_3D_ENGINE_HELLOTRIANGLEAPPLICATION_H
