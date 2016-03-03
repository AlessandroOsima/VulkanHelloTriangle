#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

/*
Renders a triangle on the screen. 
As this example is meant to be as simple as possible no depth buffer or space-conversion matrices are used.
All vertices coordinates are in clip space.

The steps are :
1) Create an Instance
2) Interface with the window system by asking for a surface we can render and present on
3) Find all the available physical devices (the gpus on the machine)
4) Find a queue that supports presenting and rendering
4) Create a device by choosing from the list of physical devices 
5) Create a swapchain from the wsi surface
6) Obtain from the swapchain a set of images we can render on
7) Create a framebuffer from each swapchain image
8) Create a Render pass and subpass to specify rendertargets.
9) Create shader modules with the spir-v fragment and vertex shaders (compiled from glsl shaders with glslangValidator)
10) Create a vertex buffer to store the vertices to render
11) Create a Graphics Pipeline object to specify all the pipeline stages (no depth stencil, viewport and scissor are dynamic)
12) Ask the swapchain for the next image we can render on 
13) Create a command buffer, bind the renderpass, the pipeline, set the dynamic stages and issue a draw call
14) Place a pre-present barrier
15) Wait for the command to complete
14) Present the queue 
15) Weep with joy
*/


struct SwapchainImages
{
	VkImage image;
	VkImageView imageView;
};

struct  Vertices
{
	VkDeviceMemory memory;
	VkBuffer buffer;
};

class VulkanAPI
{
public:
	VulkanAPI();
	bool Init(bool validate = false);
	void DeInit();
	void Draw();

private:
	VkInstance CreateInstance();
	bool IsLayerListPresent(const std::vector<const char *> & layersToCheck, VkLayerProperties * presentLayers, uint32_t presentLayersCount);
	bool IsExtensionListPresent(const std::vector<const char *> & extensionsToCheck, VkExtensionProperties * presentExtensions, uint32_t presentExtensionsCount);
	bool CreateWSISurface();
	/*
	Use the first discrete gpu avaliable, the first avaliable if no discrete gpus are found
	@chosenDeviceId the id of the chosen physical device
	*/
	VkPhysicalDevice ChoosePhysicalDeviceToUse(VkPhysicalDevice * phdevs, unsigned int devicesCount, int & chosenDeviceId);
	bool CreateSwapChainForPhysicalDevice(VkPhysicalDevice deviceToUse, VkFormat & swapchainFormatUsed, VkColorSpaceKHR & colorSpaceUsed, VkExtent2D & swapchainExtent);
	VkDevice CreateDevice(const std::vector<VkPhysicalDevice> & devices, VkPhysicalDevice deviceToUse, uint32_t deviceToUseId);
	void EnumeratePhysicalDeviceProperties(VkPhysicalDevice physicalDevice);
	
	std::unique_ptr<SwapchainImages[]> GetImagesFromSwapchain(VkDevice device, VkSwapchainKHR swapchain, VkFormat imageFormat, VkColorSpaceKHR colorSpace, VkCommandBuffer commandBufferForLayoutSwitch, uint32_t & swapchainImagesCount);
	std::unique_ptr<VkFramebuffer[]> CreateFrameBufferFromSwapchainImages(VkDevice device, VkRenderPass renderPass, const std::unique_ptr<SwapchainImages[]> & swapchainImages, uint32_t swapchainImagesCount);
	VkRenderPass PrepareRenderPass(VkFormat format, VkExtent2D extent);
	
	std::unique_ptr<Vertices> CreateVertexBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties);
	bool GetMemoryTypeFromProperties(VkPhysicalDeviceMemoryProperties currentDeviceMemoryProperties, uint32_t typeBits, VkFlags requirementsMask, uint32_t & typeIndex);
	
	bool SetImageLayout(VkCommandBuffer imageLayoutChangeCommandBuffer, VkImage image, VkAccessFlagBits srcFlags, VkAccessFlagBits dstFlags, VkImageAspectFlags imageFlags, VkImageLayout oldLayout, VkImageLayout newLayout);
	
	VkPipeline CreatePipeline(VkDevice device, VkShaderModule vertex, VkShaderModule fragment, VkRenderPass renderPass);

	/*
	Read a spirv shader from a filename.
	@size the size of the shader file
	returns a pointer to the shader blob or NULL
	*/
	void * ReadShader(const char * filename, size_t & size) const;

	/*
	Create a shader module.
	@device -> the device to use to create the shader
	@filename -> the name of the spirv shader to load
	returns the shader module or VK_NULL_HANDLE if creation failed
	*/
	VkShaderModule CreateShaderModule(VkDevice device, const char * filename);

	VkInstance instance;

	VkDevice device;
	VkPhysicalDeviceMemoryProperties currentDeviceMemoryProperties;

	VkSurfaceKHR surface;
	VkSwapchainKHR swapchain;
	VkFormat swapchainFormat;
	VkColorSpaceKHR swapchainColorSpace;
	VkExtent2D swapchainExtent;
	uint32_t swapchainImagesCount;

	VkRenderPass renderPass;
	VkQueue renderingPresentQueue;
	VkPipeline pipeline;
	VkPipelineLayout layout;
	VkCommandBuffer renderingPresentCommandBuffer;

	uint32_t renderingPresentQueueFamilyIndex = 0;
	VkCommandPool commandPool;

	//The vertex buffer to render on screen
	std::unique_ptr<Vertices> vertices;

	//Pointers to extensions functions
	PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfVkGetPhysicalDeviceSurfaceSupportKHR;
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfVkGetPhysicalDeviceSurfaceCapabilities;
	PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfVKGetPhysicalDeviceSurfacePresentModesKHR;
	PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfVkGetPhysicalDeviceSurfaceFormatsKHR;

	std::unique_ptr<SwapchainImages[]> swapchainImagesBuffer;
	std::unique_ptr<VkFramebuffer[]> framebuffers;

	//List of the instance layers to enable
	std::vector<const char *> instanceLayers;
	//List of the device layers to enable
	std::vector<const char *> deviceLayers;
	//List of the instance extensions to enable
	std::vector<const char *> instanceExtensions;
	//List of the device extensions to enable
	std::vector<const char *> deviceExtensions;
};
