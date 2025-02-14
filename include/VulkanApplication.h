#ifndef INC_3D_ENGINE_VULKANAPPLICATION_H
#define INC_3D_ENGINE_VULKANAPPLICATION_H

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>
#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <vector>
#include <set>
#include <array>

#include <optional>

const uint32_t X_POS = 0;
const uint32_t Y_POS = 0;
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;
const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                                                    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME};

const std::vector<const char *> instanceExtensions = {VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                                                      VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME};

struct QueueFamilies {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> transferFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && transferFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

const std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class VulkanApplication {
public:
    void run();

private:
    VkInstance instance;
    SDL_Window *window;
    VkDebugUtilsMessengerEXT debugMessenger;

    VkPhysicalDevice physicalDevice;
    VkDevice device;

    QueueFamilies queueFamilies;
    std::set<uint32_t> queueFamilyIndices;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkQueue transferQueue;

    VkSurfaceKHR surface;

    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;

    std::vector<VkImageView> swapchainImageViews;

    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;

    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapchainFramebuffers;

    VkRenderPass renderPass;
    uint32_t currentFrame;

    VkDescriptorPool descriptorPool;
    VkCommandPool graphicsCommandPool;
    VkCommandPool transferCommandPool;

    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkSemaphore> imageAvailableSemaphores;

    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    bool framebufferResized = false;

    std::vector<VkCommandBuffer> commandBuffers;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void *> uniformBuffersMapped;

    float angleZ = 0.0f;
    float angleX = 0.0f;

    void initWindow();

    void initVulkan();

    void mainLoop();

    void processWindowEvent(SDL_WindowEvent windowEvent);

    void processKeyEvent(SDL_KeyboardEvent keyboardEvent);

    void drawFrame();

    void updateUniformBuffer(uint32_t currentImage);

    void createInstance();

    void createSurface();

    void createLogicalDevice();

    void createSwapchain();

    void cleanupSwapchain();

    void recreateSwapchain();

    void createImageViews();

    void createRenderPass();

    void createDescriptorSetLayout();

    void createGraphicsPipeline();

    VkShaderModule createShaderModule(const std::vector<char>& code);

    void createFramebuffers();

    void createGraphicsCommandPool();

    void createTransferCommandPool();

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

    void createVertexBuffer();

    void createIndexBuffer();

    void createUniformBuffers();

    void createDescriptorPool();

    void createDescriptorSets();

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createCommandBuffers();

    void recordCommandBuffer(VkCommandBuffer cmdBuffer, uint32_t imageIndex);

    void createSyncObjects();

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

    QueueFamilies findQueueFamilies(VkPhysicalDevice dvc);

    SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice dvc);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    std::vector<const char *> getRequiredInstanceExtensions();

    void cleanup();
};

/*
 * TODO: Integrate VulkanMemoryAllocator for memory operations
 * Library: https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
 */

#endif //INC_3D_ENGINE_VULKANAPPLICATION_H
