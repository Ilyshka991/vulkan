#pragma once

#include "common/vk_common.h"
#include "core/instance.h"
#include "platform/application.h"

class HelloTriangle : public vkb::Application {

    struct SwapchainDimensions {
        uint32_t width = 0;
        uint32_t height = 0;

        VkFormat format = VK_FORMAT_UNDEFINED;
    };

    struct PerFrame {
        VkDevice device = VK_NULL_HANDLE;

        VkFence queue_submit_fence = VK_NULL_HANDLE;

        VkCommandPool primary_command_pool = VK_NULL_HANDLE;

        VkCommandBuffer primary_command_buffer = VK_NULL_HANDLE;

        VkSemaphore swapchain_acquire_semaphore = VK_NULL_HANDLE;

        VkSemaphore swapchain_release_semaphore = VK_NULL_HANDLE;

        int32_t queue_index;
    };

    struct Context {
        VkInstance instance = VK_NULL_HANDLE;
        VkPhysicalDevice gpu = VK_NULL_HANDLE;
        VkDevice device = VK_NULL_HANDLE;
        VkQueue queue = VK_NULL_HANDLE;
        VkSwapchainKHR swapchain = VK_NULL_HANDLE;
        SwapchainDimensions swapchain_dimensions;
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        int32_t graphics_queue_index = -1;
        std::vector<VkImageView> swapchain_image_views;
        std::vector<VkFramebuffer> swapchain_framebuffers;
        VkRenderPass render_pass = VK_NULL_HANDLE;
        VkPipeline pipeline = VK_NULL_HANDLE;
        VkPipelineLayout pipeline_layout = VK_NULL_HANDLE;
        VkDebugReportCallbackEXT debug_callback = VK_NULL_HANDLE;
        std::vector<VkSemaphore> recycled_semaphores;
        std::vector<PerFrame> per_frame;
    };

public:
    HelloTriangle();

    virtual ~HelloTriangle();

    virtual bool prepare(vkb::Platform &platform) override;

    virtual void update(float delta_time) override;

    virtual void resize(const uint32_t width, const uint32_t height) override;

    bool validate_extensions(const std::vector<const char *> &required,
                             const std::vector<VkExtensionProperties> &available);

    bool validate_layers(const std::vector<const char *> &required,
                         const std::vector<VkLayerProperties> &available);

    VkShaderStageFlagBits find_shader_stage(const std::string &ext);

    void init_instance(Context &context,
                       const std::vector<const char *> &required_instance_extensions,
                       const std::vector<const char *> &required_validation_layers);

    void init_device(Context &context,
                     const std::vector<const char *> &required_device_extensions);

    void init_per_frame(Context &context, PerFrame &per_frame);

    void teardown_per_frame(Context &context, PerFrame &per_frame);

    void init_swapchain(Context &context);

    void init_render_pass(Context &context);

    VkShaderModule load_shader_module(Context &context, const char *path);

    void init_pipeline(Context &context);

    VkResult acquire_next_image(Context &context, uint32_t *image);

    void render_triangle(Context &context, uint32_t swapchain_index);

    VkResult present_image(Context &context, uint32_t index);

    void init_framebuffers(Context &context);

    void teardown_framebuffers(Context &context);

    void teardown(Context &context);

private:
    Context context;

    std::unique_ptr<vkb::Instance> vk_instance;
};

std::unique_ptr<vkb::Application> create_hello_triangle();
