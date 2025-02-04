#ifndef INC_3D_ENGINE_HELLOTRIANGLEAPPLICATION_H
#define INC_3D_ENGINE_HELLOTRIANGLEAPPLICATION_H

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>
#include <SDL2/SDL.h>

#include <vector>
#include <optional>

const uint32_t X_POS = 0;
const uint32_t Y_POS = 0;
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                                                    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME};
const std::vector<const char *> instanceExtensions = {VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                                                      VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME};

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
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapchainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    VkInstance instance = VK_NULL_HANDLE;
    SDL_Window *window = nullptr;
    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;

    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;

    VkSurfaceKHR surface = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    std::vector<VkImage> swapchainImages;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;

    std::vector<VkImageView> swapchainImageViews;

    void initWindow();

    void initVulkan();

    void mainLoop();

    void createInstance();

    void createSurface();

    void createLogicalDevice();

    void createSwapchain();

    void createImageViews();

    bool checkValidationLayerSupport();

    bool checkDeviceExtensionSupport(VkPhysicalDevice dvc);

    void setupDebugMessenger();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    static VKAPI_ATTR VkBool32 VKAPI_CALL
    debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                  VkDebugUtilsMessageTypeFlagsEXT messageType,
                  const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                  void *pUserData);

    void pickPhysicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice dvc);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dvc);

    SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice dvc);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    std::vector<const char *> getRequiredInstanceExtensions();

    void cleanup();
};

#endif //INC_3D_ENGINE_HELLOTRIANGLEAPPLICATION_H
