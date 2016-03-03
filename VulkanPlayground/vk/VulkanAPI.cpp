#include <stdafx.h>
#include <cstringt.h>
#include "VulkanAPI.h"
#include <sstream>
#include "iostream"
#include <fstream>
#include "../win/Platform.h"
#include <assert.h>

VulkanAPI::VulkanAPI() : instanceLayers({}), 
	deviceLayers(instanceLayers),
	instanceExtensions ({ VK_EXT_DEBUG_REPORT_EXTENSION_NAME, 
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME, 
		VK_KHR_SURFACE_EXTENSION_NAME }),
	deviceExtensions({ VK_KHR_SWAPCHAIN_EXTENSION_NAME })
{

}


void VulkanAPI::EnumeratePhysicalDeviceProperties(VkPhysicalDevice phdev)
{
	VkPhysicalDeviceProperties phDevProperties;
	vkGetPhysicalDeviceProperties(phdev, &phDevProperties);
	std::stringstream ss;
	ss << ">>[VK]Device name " << phDevProperties.deviceName << std::endl;
	ss << "->[VK]Device type " << std::hex << phDevProperties.deviceType << std::endl;
	ss << "->[VK]Device api version " << std::hex << phDevProperties.apiVersion << std::endl;
	ss << "->[VK]Device driver version " << std::hex << phDevProperties.driverVersion << std::endl;
	ss << "->[VK]Device vendor ID " << std::hex << phDevProperties.vendorID << std::endl;
	ss << "->[VK]Device ID " << std::hex << phDevProperties.deviceID << std::endl;

	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(phdev, &features);

	ss << "-->[VK]Device feature alphaToOne is " << features.alphaToOne << std::endl;
	ss << "-->[VK]Device feature depthBiasClamp is " << features.depthBiasClamp << std::endl;
	ss << "-->[VK]Device feature depthBounds is " << features.depthBounds << std::endl;
	ss << "-->[VK]Device feature depthClamp is " << features.depthClamp << std::endl;
	ss << "-->[VK]Device feature drawIndirectFirstInstance is " << features.drawIndirectFirstInstance << std::endl;
	ss << "-->[VK]Device feature dualSrcBlend is " << features.dualSrcBlend << std::endl;
	ss << "-->[VK]Device feature fillModeNonSolid is " << features.fillModeNonSolid << std::endl;
	ss << "-->[VK]Device feature fragmentStoresAndAtomics is " << features.fragmentStoresAndAtomics << std::endl;
	ss << "-->[VK]Device feature fullDrawIndexUint32 is " << features.fullDrawIndexUint32 << std::endl;
	ss << "-->[VK]Device feature geometryShader is " << features.geometryShader << std::endl;
	ss << "-->[VK]Device feature imageCubeArray is " << features.imageCubeArray << std::endl;
	ss << "-->[VK]Device feature independentBlend is " << features.independentBlend << std::endl;
	ss << "-->[VK]Device feature inheritedQueries is " << features.inheritedQueries << std::endl;
	ss << "-->[VK]Device feature largePoints is " << features.largePoints << std::endl;
	ss << "-->[VK]Device feature logicOp is " << features.logicOp << std::endl;
	ss << "-->[VK]Device feature multiDrawIndirect is " << features.multiDrawIndirect << std::endl;
	ss << "-->[VK]Device feature multiViewport is " << features.multiViewport << std::endl;
	ss << "-->[VK]Device feature occlusionQueryPrecise is " << features.occlusionQueryPrecise << std::endl;
	ss << "-->[VK]Device feature pipelineStatisticsQuery is " << features.pipelineStatisticsQuery << std::endl;
	ss << "-->[VK]Device feature robustBufferAccess is " << features.robustBufferAccess << std::endl;
	ss << "-->[VK]Device feature samplerAnisotropy is " << features.samplerAnisotropy << std::endl;
	ss << "-->[VK]Device feature sampleRateShading is " << features.sampleRateShading << std::endl;
	ss << "-->[VK]Device feature shaderClipDistance is " << features.shaderClipDistance << std::endl;
	ss << "-->[VK]Device feature shaderCullDistance is " << features.shaderCullDistance << std::endl;
	ss << "-->[VK]Device feature shaderFloat64 is " << features.shaderFloat64 << std::endl;
	ss << "-->[VK]Device feature shaderImageGatherExtended is " << features.shaderImageGatherExtended << std::endl;
	ss << "-->[VK]Device feature shaderInt16 is " << features.shaderInt16 << std::endl;
	ss << "-->[VK]Device feature shaderInt64 is " << features.shaderInt64 << std::endl;
	ss << "-->[VK]Device feature shaderResourceMinLod is " << features.shaderResourceMinLod << std::endl;
	ss << "-->[VK]Device feature shaderResourceResidency is " << features.shaderResourceResidency << std::endl;
	ss << "-->[VK]Device feature shaderSampledImageArrayDynamicIndexing is " << features.shaderSampledImageArrayDynamicIndexing << std::endl;
	ss << "-->[VK]Device feature shaderStorageBufferArrayDynamicIndexing is " << features.shaderStorageBufferArrayDynamicIndexing << std::endl;
	ss << "-->[VK]Device feature shaderStorageImageArrayDynamicIndexing is " << features.shaderStorageImageArrayDynamicIndexing << std::endl;
	ss << "-->[VK]Device feature shaderStorageImageExtendedFormats is " << features.shaderStorageImageExtendedFormats << std::endl;
	ss << "-->[VK]Device feature shaderStorageImageMultisample is " << features.shaderStorageImageMultisample << std::endl;
	ss << "-->[VK]Device feature shaderStorageImageReadWithoutFormat is " << features.shaderStorageImageReadWithoutFormat << std::endl;
	ss << "-->[VK]Device feature shaderStorageImageWriteWithoutFormat is " << features.shaderStorageImageWriteWithoutFormat << std::endl;
	ss << "-->[VK]Device feature shaderTessellationAndGeometryPointSize is " << features.shaderTessellationAndGeometryPointSize << std::endl;
	ss << "-->[VK]Device feature shaderUniformBufferArrayDynamicIndexing is " << features.shaderUniformBufferArrayDynamicIndexing << std::endl;
	ss << "-->[VK]Device feature sparseBinding is " << features.sparseBinding << std::endl;
	ss << "-->[VK]Device feature sparseResidency16Samples is " << features.sparseResidency16Samples << std::endl;
	ss << "-->[VK]Device feature sparseResidency2Samples is " << features.sparseResidency2Samples << std::endl;
	ss << "-->[VK]Device feature sparseResidency4Samples is " << features.sparseResidency4Samples << std::endl;
	ss << "-->[VK]Device feature sparseResidency8Samples is " << features.sparseResidency8Samples << std::endl;
	ss << "-->[VK]Device feature sparseResidencyAliased is " << features.sparseResidencyAliased << std::endl;
	ss << "-->[VK]Device feature sparseResidencyBuffer is " << features.sparseResidencyBuffer << std::endl;
	ss << "-->[VK]Device feature sparseResidencyImage2D is " << features.sparseResidencyImage2D << std::endl;
	ss << "-->[VK]Device feature sparseResidencyImage3D is " << features.sparseResidencyImage3D << std::endl;
	ss << "-->[VK]Device feature tessellationShader is " << features.tessellationShader << std::endl;
	ss << "-->[VK]Device feature textureCompressionASTC_LDR is " << features.textureCompressionASTC_LDR << std::endl;
	ss << "-->[VK]Device feature textureCompressionBC is " << features.textureCompressionBC << std::endl;
	ss << "-->[VK]Device feature textureCompressionETC2 is " << features.textureCompressionETC2 << std::endl;
	ss << "-->[VK]Device feature variableMultisampleRate is " << features.variableMultisampleRate << std::endl;
	ss << "-->[VK]Device feature vertexPipelineStoresAndAtomics is " << features.vertexPipelineStoresAndAtomics << std::endl;
	ss << "-->[VK]Device feature wideLines is " << features.wideLines << std::endl;

	uint32_t queues = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(phdev, &queues, NULL);

	VkQueueFamilyProperties * queueProperties = new VkQueueFamilyProperties[queues];
	vkGetPhysicalDeviceQueueFamilyProperties(phdev, &queues, queueProperties);

	for (uint32_t i = 0; i < queues; i++)
	{
		ss << "->[VK]Has " << std::dec << queueProperties[i].queueCount << " queues with flags " << std::hex << (uint32_t)queueProperties[i].queueFlags << std::endl;

	}

	delete queueProperties;

	platform->LogString(ss.str());
}

std::unique_ptr<SwapchainImages[]> VulkanAPI::GetImagesFromSwapchain(VkDevice device, VkSwapchainKHR swapchain, VkFormat imageFormat, VkColorSpaceKHR colorSpace, VkCommandBuffer commandBufferForLayoutSwitch, uint32_t & swapchainImagesCount)
{
	uint32_t swapchainImagesSize = 0;
	if (vkGetSwapchainImagesKHR(device, swapchain, &swapchainImagesSize, NULL) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK] Unable to enumerate swapchain images"), false);
		return nullptr;
	}
	swapchainImagesCount = swapchainImagesSize;

	std::unique_ptr<SwapchainImages[]> swapchainImages = std::unique_ptr<SwapchainImages[]>(new SwapchainImages[swapchainImagesSize]);

	std::vector<VkImage> images(swapchainImagesSize);
	
	if (vkGetSwapchainImagesKHR(device, swapchain, &swapchainImagesSize, images.data()))
	{
		platform->ReportError(_T("[VK] Unable to get swapchain images"), false);
		return nullptr;
	}


	for (uint32_t i = 0; i < swapchainImagesSize; i++)
	{
		swapchainImages[i].image = images[i];
		VkImageViewCreateInfo imageViewCreateInfo
		{
			VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			NULL,
			0,
			images[i],
			VK_IMAGE_VIEW_TYPE_2D,
			imageFormat,
			VkComponentMapping{
				VK_COMPONENT_SWIZZLE_R,
				VK_COMPONENT_SWIZZLE_G,
			    VK_COMPONENT_SWIZZLE_B,
			    VK_COMPONENT_SWIZZLE_A,
			 },
			VkImageSubresourceRange{
			    VK_IMAGE_ASPECT_COLOR_BIT,
			    0,
			    1,
			    0,
			    1}
		};

		VkImageMemoryBarrier imageMemoryBarrier
		{
			VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			NULL,
			0,
			VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			renderingPresentQueueFamilyIndex,
			renderingPresentQueueFamilyIndex,
			images[i],
			VkImageSubresourceRange{
			VK_IMAGE_ASPECT_COLOR_BIT,
			0,
			1,
			0,
			1 }
		};

		vkCmdPipelineBarrier(commandBufferForLayoutSwitch, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 0, 0, NULL, 0, NULL, 1, &imageMemoryBarrier);

		vkCreateImageView(device, &imageViewCreateInfo, NULL, &swapchainImages[i].imageView);
	}

	return swapchainImages;
}

std::unique_ptr<VkFramebuffer[]> VulkanAPI::CreateFrameBufferFromSwapchainImages(VkDevice device, VkRenderPass renderPass, const std::unique_ptr<SwapchainImages[]> & swapchainImages, uint32_t swapchainImagesCount)
{
	std::unique_ptr<VkFramebuffer[]> framebuffers = std::unique_ptr<VkFramebuffer[]>(new VkFramebuffer[swapchainImagesCount]);

	VkImageView attachment;
	VkFramebufferCreateInfo framebufferCreateInfo
	{
		VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		NULL,
		0,
		renderPass,
		1,
		&attachment,
		swapchainExtent.width,
		swapchainExtent.height,
		1,
	};

	for (int i = 0; i < swapchainImagesCount; i++)
	{
		attachment = swapchainImages[i].imageView;
		if (vkCreateFramebuffer(device, &framebufferCreateInfo, NULL, &framebuffers[i]) != VK_SUCCESS)
		{
			platform->ReportError(_T("Create framebuffers failed"));
			return nullptr;
		}
	}

	return framebuffers;
}

VkRenderPass VulkanAPI::PrepareRenderPass(VkFormat format, VkExtent2D extent)
{
	VkAttachmentDescription attachments [1]
	{
	    { //Color buffer
			0,
			format,
		    VK_SAMPLE_COUNT_1_BIT,
		    VK_ATTACHMENT_LOAD_OP_CLEAR,
			VK_ATTACHMENT_STORE_OP_STORE,
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		    VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	    },
	};

	VkAttachmentReference colorAttachmentReference 
	{
		0, 
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	};

	VkAttachmentReference depthAttachmentReference
	{
		VK_ATTACHMENT_UNUSED,
		VK_IMAGE_LAYOUT_UNDEFINED
	};


	VkSubpassDescription renderingSubpass 
	{
		0,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		0,
		NULL,
		1,
		&colorAttachmentReference,
		NULL,
		&depthAttachmentReference,
		0,
		NULL,
	};

	VkRenderPassCreateInfo renderingRenderPassCreateInfo
	{
		VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		NULL,
		0,
		1,
		attachments,
		1,
		&renderingSubpass,
		0,
		NULL
	};

	VkRenderPass renderPass;
	if (vkCreateRenderPass(device, &renderingRenderPassCreateInfo, NULL, &renderPass) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK] Unablke to create renderpass"));
		renderPass = VK_NULL_HANDLE;
	}

	return renderPass;
}

std::unique_ptr<Vertices> VulkanAPI::CreateVertexBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties)
{
	const float vertices[3][7]
	{
		//Position              //Color
		{ -1.0f, -1.0f,  1.f,   1.f, 0.f, 0.f, 1.f },
		{ 1.0f, -1.0f,  1.f,    0.f, 1.f, 0.f, 1.f },
		{ 0.0f,  1.0f,  1.0f,   0.f, 0.f, 1.f, 1.f },
	};

	VkBufferCreateInfo bufferCreateInfo
	{
		VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		NULL,
		0,
		sizeof(vertices),
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_SHARING_MODE_EXCLUSIVE,
		0,
		NULL
	};

	std::unique_ptr<Vertices> verticesGroup = std::make_unique<Vertices>();
	if (vkCreateBuffer(device, &bufferCreateInfo, NULL, &verticesGroup->buffer) != VK_SUCCESS)
	{
		platform->ReportError(_T("Unable to create vertex buffer"));
		return nullptr;
	}


	VkMemoryRequirements memoryRequirements;

	vkGetBufferMemoryRequirements(device, verticesGroup->buffer, &memoryRequirements);

	VkMemoryAllocateInfo memAllocateInfo;
	memAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAllocateInfo.pNext = NULL;
	memAllocateInfo.allocationSize = memoryRequirements.size;

	if (!GetMemoryTypeFromProperties(currentDeviceMemoryProperties, memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, memAllocateInfo.memoryTypeIndex))
	{
		platform->ReportError(_T("Unable to get memory type index for vertex buffer"));
		return nullptr;
	}

	if (vkAllocateMemory(device, &memAllocateInfo, NULL, &verticesGroup->memory) != VK_SUCCESS)
	{
		platform->ReportError(_T("Unable to allocate vertex buffer device memory"));
		return nullptr;
	}

	void * data;

	if (vkMapMemory(device, verticesGroup->memory, 0, memAllocateInfo.allocationSize, 0, &data) != VK_SUCCESS)
	{
		platform->ReportError(_T("Unable to map memory to device buffer"));
		return nullptr;
	}

	memcpy(data, vertices, sizeof(vertices));

	vkUnmapMemory(device, verticesGroup->memory);

	if (vkBindBufferMemory(device, verticesGroup->buffer, verticesGroup->memory, 0))
	{
		platform->ReportError(_T("Unable to bind memory to device buffer"));
		return nullptr;
	}

	return verticesGroup;
}

//shamelessly copied from the samples
bool VulkanAPI::GetMemoryTypeFromProperties(VkPhysicalDeviceMemoryProperties currentDeviceMemoryProperties, uint32_t typeBits, VkFlags requirementsMask, uint32_t & typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < 32; i++) {
		if ((typeBits & 1) == 1) {
			// Type is available, does it match user properties?
			if ((currentDeviceMemoryProperties.memoryTypes[i].propertyFlags &
				requirementsMask) == requirementsMask) {
				typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return false;
}

bool VulkanAPI::SetImageLayout(VkCommandBuffer imageLayoutChangeCommandBuffer, VkImage image, VkAccessFlagBits srcFlags, VkAccessFlagBits dstFlags, VkImageAspectFlags imageFlags, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	bool createBuffer = imageLayoutChangeCommandBuffer == VK_NULL_HANDLE ? true : false;
	if (createBuffer)
	{
		VkCommandBufferAllocateInfo allocateInfo
		{
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			NULL,
			commandPool,
			VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			1
		};

		if (vkAllocateCommandBuffers(device, &allocateInfo, &imageLayoutChangeCommandBuffer) != VK_SUCCESS)
		{
			DeInit();
			platform->ReportError(_T("[VK]Unable to allocate init command buffer"), true);
			return false;
		}

		VkCommandBufferBeginInfo commandBufferBeginInfo
		{
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			NULL,
			0,
			NULL
		};

		if (vkBeginCommandBuffer(imageLayoutChangeCommandBuffer, &commandBufferBeginInfo) != VK_SUCCESS)
		{
			platform->ReportError(_T("[VK]Unable to begin command buffer"));
			return false;
		}
	}

	VkImageMemoryBarrier imageMemoryBarrier
	{
		VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		NULL,
		srcFlags,
		dstFlags,
		oldLayout,
		newLayout,
		renderingPresentQueueFamilyIndex,
		renderingPresentQueueFamilyIndex,
		image,
		VkImageSubresourceRange{
		imageFlags,
		0,
		1,
		0,
		1 }
	};

	vkCmdPipelineBarrier(imageLayoutChangeCommandBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 0, 0, NULL, 0, NULL, 1, &imageMemoryBarrier);

	if (createBuffer)
	{
		if (vkEndCommandBuffer(imageLayoutChangeCommandBuffer) != VK_SUCCESS)
		{
			platform->ReportError(_T("[VK]Unable to end command buffer"));
			return false;
		}

		VkSubmitInfo submitInfo
		{
			VK_STRUCTURE_TYPE_SUBMIT_INFO,
			NULL,
			0,
			NULL,
			NULL,
			1,
			&imageLayoutChangeCommandBuffer,
			0,
			NULL
		};

		VkResult res = vkQueueSubmit(renderingPresentQueue, 1, &submitInfo, NULL);
		if (res != VK_SUCCESS)
		{
			vkFreeCommandBuffers(device, commandPool, 1, &imageLayoutChangeCommandBuffer);
			DeInit();
			platform->ReportError(_T("[VK]Unable to submit queue"), true);
			return false;
		}

		if (vkQueueWaitIdle(renderingPresentQueue) != VK_SUCCESS && res != VK_ERROR_DEVICE_LOST)
		{
			vkFreeCommandBuffers(device, commandPool, 1, &imageLayoutChangeCommandBuffer);
			DeInit();
			platform->ReportError(_T("[VK]Unable to wait on queue idle"), true);
			return false;
		}

		vkFreeCommandBuffers(device, commandPool, 1, &imageLayoutChangeCommandBuffer);

	}
}

void * VulkanAPI::ReadShader(const char * filename, size_t & size) const
{
	FILE * file;
	file = fopen(filename, "rb");

	if (!file)
	{
		platform->ReportError(_T("Unable to open shader file"));
		return nullptr;
	}

	fseek(file, 0, SEEK_END);

	long int fileSize = ftell(file);

	fseek(file, 0, SEEK_SET);

	void * fileContent = malloc(fileSize);

	int ret = fread(fileContent, fileSize, 1, file);

	if (!ret)
	{
		free(fileContent);
		platform->ReportError(_T("Unable to read shader file"));
		return nullptr;
	}

	fclose(file);

	size = fileSize;

	return fileContent;
}

VkShaderModule VulkanAPI::CreateShaderModule(VkDevice device, const char * filename)
{
	void * shaderBlob = NULL;
	size_t shaderBlobSize = 0;
	shaderBlob = ReadShader(filename, shaderBlobSize);

	if (!shaderBlob || !shaderBlobSize)
	{
		free(shaderBlob);
		platform->ReportError(_T("Unable to read shader file"));
		return VK_NULL_HANDLE;
	}

	VkShaderModule shaderModule;
	VkShaderModuleCreateInfo shaderModuleCreateInfo
	{
		VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		NULL,
		0,
		shaderBlobSize,
		(const uint32_t *)shaderBlob
	};

	if (vkCreateShaderModule(device, &shaderModuleCreateInfo, NULL, &shaderModule) != VK_SUCCESS)
	{
		free(shaderBlob);
		platform->ReportError(_T("Unable to create shader module"));
		return VK_NULL_HANDLE;
	}

	free(shaderBlob);

	return shaderModule;
}

void VulkanAPI::DeInit()
{
	if (renderingPresentCommandBuffer)
	{
		vkFreeCommandBuffers(device, commandPool, 1, &renderingPresentCommandBuffer);
	}

	if (vertices)
	{
		vkFreeMemory(device, vertices->memory, NULL);
		vkDestroyBuffer(device, vertices->buffer, NULL);
	}

	if (layout)
	{
		vkDestroyPipelineLayout(device, layout, NULL);
	}

	if (pipeline)
	{
		vkDestroyPipeline(device, pipeline, NULL);
	}

	if (renderPass)
	{
		vkDestroyRenderPass(device, renderPass, NULL);
	}

	if (framebuffers)
	{
		for (uint32_t i = 0; i < swapchainImagesCount; i++)
		{ 
			vkDestroyFramebuffer(device, framebuffers[i], NULL);
		}
	}

	if (swapchainImagesBuffer)
	{
		for (uint32_t i = 0; i < swapchainImagesCount; i++)
		{
			vkDestroyImageView(device, swapchainImagesBuffer[i].imageView, NULL);
		}
	}

	if (commandPool != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(device, commandPool, NULL);
	}

	if (device != VK_NULL_HANDLE)
	{
		vkDeviceWaitIdle(device);

		if (swapchain != VK_NULL_HANDLE)
		{
			vkDestroySwapchainKHR(device, swapchain, NULL);
		}

		if (surface != VK_NULL_HANDLE)
		{
			vkDestroySurfaceKHR(instance, surface, NULL);
		}


		vkDestroyDevice(device, NULL);
	}


	if (instance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(instance, NULL);
	}

}

void VulkanAPI::Draw()
{
	VkSemaphore swapchainAcquireSemaphore;
	VkSemaphoreCreateInfo semaphoreCreateInfo
	{
		VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, 
		NULL, 
		0
	};
	uint32_t currentSwapchainImageId;
	if (vkCreateSemaphore(device, &semaphoreCreateInfo, NULL, &swapchainAcquireSemaphore) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("[VK]Unable to create semaphore to acquire next swapchain image id"), true);
	}

	if (vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, swapchainAcquireSemaphore, 0, &currentSwapchainImageId) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("[VK]Unable to acquire next swapchain image id"), true);
	}


	SetImageLayout(NULL, swapchainImagesBuffer[currentSwapchainImageId].image, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

	//SetImageLayout(NULL, swapchainImagesBuffer[currentSwapchainImageId].image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_GENERAL);


	//Draw COMMAND BUFFER
	VkCommandBufferBeginInfo commandBufferBeginInfo
	{
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		NULL,
		0,
		NULL
	};

	VkClearColorValue clearColor;

	clearColor.float32[0] = 0;
	clearColor.float32[1] = 0;
	clearColor.float32[2] = 0;
	clearColor.float32[3] = 1;

	VkClearValue clearValueFramebuffer;
	memset(&clearValueFramebuffer, 0, sizeof(clearValueFramebuffer));
	clearValueFramebuffer.color = clearColor;
	

	VkImageSubresourceRange range
	{
		VK_IMAGE_ASPECT_COLOR_BIT,
		0,
		1,
		0,
		1
	};

	if (vkBeginCommandBuffer(renderingPresentCommandBuffer, &commandBufferBeginInfo) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to begin command buffer"), true);
	}

	VkRenderPassBeginInfo renderPassBeginInfo
	{
		VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		NULL,
		renderPass,
		framebuffers[currentSwapchainImageId],
		{
			0,
			0,
			swapchainExtent.width,
			swapchainExtent.height,
		},
		1,
		&clearValueFramebuffer,
	};

	vkCmdBeginRenderPass(renderingPresentCommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(renderingPresentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

	VkViewport viewport
	{
		0,
		0,
		swapchainExtent.width,
		swapchainExtent.height,
		0.f,
		1.f,
	};

	vkCmdSetViewport(renderingPresentCommandBuffer, 0, 1, &viewport);

	VkRect2D scissor
	{
		{ 0,0 },
		{ swapchainExtent.width, swapchainExtent.height }
	};

	vkCmdSetScissor(renderingPresentCommandBuffer, 0, 1, &scissor);
	
	VkDeviceSize offsets[1] = { 0 };
	vkCmdBindVertexBuffers(renderingPresentCommandBuffer, 0, 1, &vertices->buffer, offsets);
	vkCmdDraw(renderingPresentCommandBuffer, 3, 1, 0, 0);
	
	vkCmdEndRenderPass(renderingPresentCommandBuffer);

	VkImageMemoryBarrier prePresentBarrier = {
		VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		NULL,
		VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		VK_ACCESS_MEMORY_READ_BIT,
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		VK_QUEUE_FAMILY_IGNORED,
		VK_QUEUE_FAMILY_IGNORED,
		swapchainImagesBuffer[currentSwapchainImageId].image,
		{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 }
	};

	vkCmdPipelineBarrier(renderingPresentCommandBuffer, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, NULL, 0, NULL, 1, &prePresentBarrier);


	if (vkEndCommandBuffer(renderingPresentCommandBuffer) != VK_SUCCESS)
	{
		platform->ReportError(_T("Unable to end command buffer"), true);
	}


	//////////////////////////////////////////////////////////////////////////

	const VkPipelineStageFlags pipelineStageFlag = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

	VkSubmitInfo drawCommandSubmitInfo
	{
		VK_STRUCTURE_TYPE_SUBMIT_INFO,
		NULL,
		1,
		&swapchainAcquireSemaphore,
		&pipelineStageFlag,
		1,
		&renderingPresentCommandBuffer,
		0,
		NULL
	};

	vkQueueSubmit(renderingPresentQueue, 1, &drawCommandSubmitInfo, NULL);

	VkResult queuePresentResult;
	VkPresentInfoKHR presentInfo
	{
		VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		NULL,
		0,
		NULL,
		1,
		&swapchain,
		&currentSwapchainImageId,
		&queuePresentResult
	};

	vkQueuePresentKHR(renderingPresentQueue, &presentInfo);

	vkQueueWaitIdle(renderingPresentQueue);

	vkDestroySemaphore(device, swapchainAcquireSemaphore, NULL);
}

VkPipeline VulkanAPI::CreatePipeline(VkDevice device, VkShaderModule vertex, VkShaderModule fragment, VkRenderPass renderPass)
{
	VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo;
	memset(&graphicsPipelineCreateInfo, 0, sizeof(graphicsPipelineCreateInfo));

	//Pipeline Creation
	graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	graphicsPipelineCreateInfo.pNext = NULL;
	graphicsPipelineCreateInfo.flags = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT | VK_PIPELINE_CREATE_DERIVATIVE_BIT;

	//Shader Stage 
	VkPipelineShaderStageCreateInfo shaderStagesCreateInfos[2];
	memset(&shaderStagesCreateInfos, 0, 2 * sizeof(VkPipelineShaderStageCreateInfo));

	//Vertex shader
	shaderStagesCreateInfos[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStagesCreateInfos[0].pNext = NULL;
	shaderStagesCreateInfos[0].flags = 0;
	shaderStagesCreateInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStagesCreateInfos[0].module = vertex;
	shaderStagesCreateInfos[0].pName = "main";

	//Fragment shader
	shaderStagesCreateInfos[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStagesCreateInfos[1].pNext = NULL;
	shaderStagesCreateInfos[1].flags = 0;
	shaderStagesCreateInfos[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStagesCreateInfos[1].module = fragment;
	shaderStagesCreateInfos[1].pName = "main";

	graphicsPipelineCreateInfo.stageCount = 2;
	graphicsPipelineCreateInfo.pStages = shaderStagesCreateInfos;

	//Vertext Input State
	VkPipelineVertexInputStateCreateInfo inputVertexBindingCreateInfo;
	inputVertexBindingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	inputVertexBindingCreateInfo.pNext = NULL;
	inputVertexBindingCreateInfo.flags = 0;

	VkVertexInputBindingDescription vertexBinding;
	vertexBinding.binding = 0;
	vertexBinding.stride = sizeof(float) * 7;
	vertexBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	VkVertexInputAttributeDescription vertexInputAttributePosition;
	vertexInputAttributePosition.binding = 0;
	vertexInputAttributePosition.location = 0;
	vertexInputAttributePosition.format = VK_FORMAT_R32G32B32_SFLOAT;
	vertexInputAttributePosition.offset = 0;

	VkVertexInputAttributeDescription vertexInputAttributeColor;
	vertexInputAttributeColor.binding = 0;
	vertexInputAttributeColor.location = 1;
	vertexInputAttributeColor.format = VK_FORMAT_R32G32B32A32_SFLOAT;
	vertexInputAttributeColor.offset = sizeof(float) * 3;

	VkVertexInputAttributeDescription vertexAttributes[2] = { vertexInputAttributePosition, vertexInputAttributeColor };

	inputVertexBindingCreateInfo.vertexBindingDescriptionCount = 1;
	inputVertexBindingCreateInfo.pVertexBindingDescriptions = &vertexBinding;
	inputVertexBindingCreateInfo.vertexAttributeDescriptionCount = 2;
	inputVertexBindingCreateInfo.pVertexAttributeDescriptions = vertexAttributes;

	graphicsPipelineCreateInfo.pVertexInputState = &inputVertexBindingCreateInfo;

	//Input Assembly State
	VkPipelineInputAssemblyStateCreateInfo iaStateCreateInfo
	{
	   VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
	   NULL,
	   0,
	   VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
	   VK_FALSE
	};

	graphicsPipelineCreateInfo.pInputAssemblyState = &iaStateCreateInfo;

	//Tesselation State
	graphicsPipelineCreateInfo.pTessellationState = NULL; //No tesselation for now

    //Viewport State is dynamic
    VkViewport viewport
    {
    	0,
    	0,
		swapchainExtent.width,
		swapchainExtent.height,
    	0.f,
    	1.f,
    };
    
    VkRect2D scissor
    {
    	{0,0},
    	{ swapchainExtent.width, swapchainExtent.height}
    };
    
    VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo
    {
    	VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    	NULL,
    	0,
    	1,
    	&viewport,
    	1,
    	&scissor
    };
    
    graphicsPipelineCreateInfo.pViewportState = &pipelineViewportStateCreateInfo;
    
    //Rasterization State
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo
    {
    	VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    	NULL,
    	0,
    	VK_FALSE,
    	VK_FALSE,
    	VK_POLYGON_MODE_FILL,
    	VK_CULL_MODE_BACK_BIT,
    	VK_FRONT_FACE_CLOCKWISE,
    	VK_FALSE,
    	0,
    	0,
    	1,
    };
    
    graphicsPipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
    
    //Multisample State
    
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo
    {
    	VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    	NULL,
    	0,
    	VK_SAMPLE_COUNT_1_BIT, //Center of the pixel
    	VK_FALSE,
    	0,
    	0,
    	VK_FALSE,
    	VK_FALSE,
    
    };
    
    graphicsPipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
    
    //Depth Stencil State -> Not enabled for now
    
	VkStencilOpState fakeState;
	memset(&fakeState, 0, sizeof(fakeState));
	VkPipelineDepthStencilStateCreateInfo depthStencilState
	{
		VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		NULL,
		0,
		VK_FALSE,
		VK_FALSE,
		VK_COMPARE_OP_NEVER,
		VK_FALSE,
		VK_FALSE,
		fakeState,
		fakeState,
		0.f,
		1.f
	};

    graphicsPipelineCreateInfo.pDepthStencilState = NULL;
    
    //Color blend -> No blend with the framebuffer
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    memset(&colorBlendAttachment, 0, sizeof(colorBlendAttachment));
    colorBlendAttachment.colorWriteMask = 0xf;
    colorBlendAttachment.blendEnable = VK_FALSE;
    
    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo;
    memset(&colorBlendStateCreateInfo, 0, sizeof(colorBlendStateCreateInfo));
    colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCreateInfo.attachmentCount = 1;
    colorBlendStateCreateInfo.pAttachments = &colorBlendAttachment;

	graphicsPipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
    
    //Set dinamyc states
	VkDynamicState states[2];
	states[0] = VK_DYNAMIC_STATE_VIEWPORT;
    states[1] = VK_DYNAMIC_STATE_SCISSOR;


    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo;
    memset(&dynamicStateCreateInfo, 0, sizeof(dynamicStateCreateInfo));
    dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateCreateInfo.pNext = NULL;
    dynamicStateCreateInfo.flags = 0;
    dynamicStateCreateInfo.dynamicStateCount = 2;
    dynamicStateCreateInfo.pDynamicStates = states;

	graphicsPipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;

	//Pipeline Layout
	VkPipelineLayoutCreateInfo layoutCreateInfo
	{
		VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		NULL,
		0,
		0,
		NULL,
		0,
		NULL
	};

	//
	graphicsPipelineCreateInfo.renderPass = renderPass;

	graphicsPipelineCreateInfo.subpass = 0;

	graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;

	graphicsPipelineCreateInfo.basePipelineIndex = -1;


	if (vkCreatePipelineLayout(device, &layoutCreateInfo, NULL, &layout) != VK_SUCCESS)
	{
		platform->ReportError(_T("Unable to create pipeline layout"));
		return VK_NULL_HANDLE;
	}

	graphicsPipelineCreateInfo.layout = layout;
    
    VkPipeline pipeline;
    if (vkCreateGraphicsPipelines(device, NULL, 1, &graphicsPipelineCreateInfo, NULL, &pipeline) != VK_SUCCESS)
    {
		platform->ReportError(_T("Unable to create graphics pipeline"));
		return VK_NULL_HANDLE;
    }

	return pipeline;
}

VkPhysicalDevice VulkanAPI::ChoosePhysicalDeviceToUse(VkPhysicalDevice * phdevs, unsigned int devicesCount, int & chosenDeviceId)
{
	if (!devicesCount)
	{
		return VK_NULL_HANDLE;
	}
	VkPhysicalDevice chosenPDev = phdevs[0];

	//Find the first discrete gpu and use it if possible
	for (uint32_t i = 0; i < devicesCount; i++)
	{
		VkPhysicalDeviceProperties phDevProperties;
		vkGetPhysicalDeviceProperties(phdevs[i], &phDevProperties);

		if (phDevProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			chosenPDev = phdevs[i];
			chosenDeviceId = i;
			break;
		}
	}

	return chosenPDev;
}

VkInstance VulkanAPI::CreateInstance()
{
	uint32_t layerPropertiesCount = 0;
	vkEnumerateInstanceLayerProperties(&layerPropertiesCount, NULL);
	VkLayerProperties * properties = new VkLayerProperties[layerPropertiesCount];

	if (vkEnumerateInstanceLayerProperties(&layerPropertiesCount, properties) != VK_SUCCESS)
	{
		delete properties;
		platform->ReportError(_T("Unable to get instance layer properties"), true);
		return NULL;
	}

	std::stringstream ss;
	for (int i = 0; i < layerPropertiesCount; i++)
	{
		ss << "[VK]Instance Layer " << i << " has name " << properties[i].layerName << std::endl;
	}
	platform->LogString(ss.str());

	if (!IsLayerListPresent(instanceLayers, properties, layerPropertiesCount))
	{
		delete properties;
		platform->ReportError(_T("Unable to find instance layer"), true);
	}

	delete properties;

	uint32_t presentExtensionsCount;
	if (vkEnumerateInstanceExtensionProperties(NULL, &presentExtensionsCount, NULL) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to enumerate device extensions count"), true);
		return VK_NULL_HANDLE;
	}

	VkExtensionProperties * extensionsProperties = new VkExtensionProperties[presentExtensionsCount];
	if (vkEnumerateInstanceExtensionProperties(NULL, &presentExtensionsCount, extensionsProperties) != VK_SUCCESS)
	{
		delete extensionsProperties;
		platform->ReportError(_T("[VK]Unable to enumerate instance extensions"), true);
		return VK_NULL_HANDLE;
	}

	ss.str("");
	for (uint32_t i = 0; i < presentExtensionsCount; i++)
	{
		ss << "[VK]Instance Extension " << i << " has name " << extensionsProperties[i].extensionName << std::endl;
	}
	platform->LogString(ss.str());

	if (!IsExtensionListPresent(instanceExtensions, extensionsProperties, presentExtensionsCount))
	{
		delete extensionsProperties;
		platform->ReportError(_T("[VK]Not all instance extensions requested are present"), true);
		return VK_NULL_HANDLE;
	}

	delete extensionsProperties;

	VkInstanceCreateInfo createInfo
	{
		VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		NULL,
		NULL,
		NULL,
		instanceLayers.size(),
		instanceLayers.data(),
		instanceExtensions.size(),
		instanceExtensions.data(),
	};

	VkResult err = vkCreateInstance(&createInfo, NULL, &instance);
	if (err != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to create vk instance"), true);
		return VK_NULL_HANDLE;
	}

	return instance;
}

bool VulkanAPI::IsLayerListPresent(const std::vector<const char *> & layersToCheck, VkLayerProperties * presentLayers, uint32_t presentLayersCount)
{
	for (uint32_t l = 0; l < layersToCheck.size(); l++)
	{
		bool layerFound = false;
		for (uint32_t i = 0; i < presentLayersCount; i++)
		{
			if (!strcmp(presentLayers[i].layerName, layersToCheck[l]))
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}

	return true;
}

bool VulkanAPI::IsExtensionListPresent(const std::vector<const char *> & extensionsToCheck, VkExtensionProperties * presentExtensions, uint32_t presentExtensionsCount)
{
	for (uint32_t l = 0; l < extensionsToCheck.size(); l++)
	{
		bool extensionFound = false;
		for (uint32_t i = 0; i < presentExtensionsCount; i++)
		{
			if (!strcmp(presentExtensions[i].extensionName, extensionsToCheck[l]))
			{
				extensionFound = true;
				break;
			}
		}

		if (!extensionFound)
		{
			return false;
		}
	}

	return true;
}

bool VulkanAPI::CreateWSISurface()
{
	Win32WindowData data = platform->GetWindowData();

	VkWin32SurfaceCreateInfoKHR win32SurfaceCreateInfo
	{
		VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		NULL,
		0,
		data.instance,
		data.window
	};

	if (vkCreateWin32SurfaceKHR(instance, &win32SurfaceCreateInfo, NULL, &surface) != VK_SUCCESS)
	{
		return false;
	}

	return true;
}

bool VulkanAPI::CreateSwapChainForPhysicalDevice(VkPhysicalDevice deviceToUse, VkFormat & swapchainFormatUsed, VkColorSpaceKHR & colorSpaceUsed, VkExtent2D & swapchainExtent)
{

	pfVkGetPhysicalDeviceSurfaceCapabilities = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	assert(pfVkGetPhysicalDeviceSurfaceCapabilities);

	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	if (pfVkGetPhysicalDeviceSurfaceCapabilities(deviceToUse, surface, &surfaceCapabilities) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to get device surface capabilities"));
		return false;
	}


	pfVKGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
	assert(pfVKGetPhysicalDeviceSurfacePresentModesKHR);

	uint32_t presentModeCount;
	if (pfVKGetPhysicalDeviceSurfacePresentModesKHR(deviceToUse, surface, &presentModeCount, NULL) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to get enumerate present modes"));
		return false;
	}

	VkPresentModeKHR *presentModes = new VkPresentModeKHR[presentModeCount];

	if (pfVKGetPhysicalDeviceSurfacePresentModesKHR(deviceToUse, surface, &presentModeCount, presentModes))
	{
		platform->ReportError(_T("[VK]Unable to get present modes"));
		return false;
	}

	Win32WindowData data = platform->GetWindowData();
	VkExtent2D swapchainTargetExtent;

	if (surfaceCapabilities.currentExtent.width == -1)
	{
		swapchainTargetExtent.width = data.windowInfo.width;
		swapchainTargetExtent.height = data.windowInfo.height;
	}
	else
	{
		swapchainTargetExtent = surfaceCapabilities.currentExtent;
	}

	swapchainExtent = swapchainTargetExtent;

	VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
	for (uint32_t i = 0; i < presentModeCount; i++)
	{
		if (presentModes[i] == VK_PRESENT_MODE_FIFO_KHR)
		{
			presentMode = VK_PRESENT_MODE_FIFO_KHR;
		}
	}

	delete presentModes;

	uint32_t desiredNumberOfSwapchainImages = surfaceCapabilities.minImageCount + 2;
	if ((surfaceCapabilities.maxImageCount > 0) &&
		(desiredNumberOfSwapchainImages > surfaceCapabilities.maxImageCount))
	{
		// Application must settle for fewer images than desired:
		desiredNumberOfSwapchainImages = surfaceCapabilities.maxImageCount;
	}


	pfVkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	assert(pfVkGetPhysicalDeviceSurfaceFormatsKHR);

	uint32_t surfaceFormatsCount = 0;
	if (pfVkGetPhysicalDeviceSurfaceFormatsKHR(deviceToUse, surface, &surfaceFormatsCount, NULL) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to enumerate surface formats"));
		return false;
	}

	VkSurfaceFormatKHR * surfaceFormats = new VkSurfaceFormatKHR[surfaceFormatsCount];

	if (!surfaceFormatsCount)
	{
		platform->ReportError(_T("[VK]No surface formats"));
		return false;
	}

	if (pfVkGetPhysicalDeviceSurfaceFormatsKHR(deviceToUse, surface, &surfaceFormatsCount, surfaceFormats) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to get surface formats"));
		return false;
	}


	VkFormat swapchainFormat = surfaceFormats[0].format;
	swapchainFormatUsed = swapchainFormat;
	VkColorSpaceKHR swapchainColorSpace = surfaceFormats[0].colorSpace;
	delete surfaceFormats;

	VkSwapchainCreateInfoKHR swapchainCreateInfo
	{
		VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		0,
		NULL,
		surface,
		desiredNumberOfSwapchainImages,
		swapchainFormat,
		swapchainColorSpace,
		swapchainTargetExtent,
		1,
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		VK_SHARING_MODE_EXCLUSIVE,
		0,
		NULL,
		surfaceCapabilities.currentTransform,
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		presentMode,
		VK_TRUE,
		VK_NULL_HANDLE,
	};

	if (vkCreateSwapchainKHR(device, &swapchainCreateInfo, NULL, &swapchain))
	{
		platform->ReportError(_T("[VK]Unable to create swapchain"));
		return false;
	}

	return true;
}

VkDevice VulkanAPI::CreateDevice(const std::vector<VkPhysicalDevice> & devices, VkPhysicalDevice phyisicalDeviceToUse, uint32_t deviceToUseId)
{
	std::stringstream ss;
	ss << "[VK]Using physical device " << deviceToUseId << std::endl;
	platform->LogString(ss.str());

	//Enumerate all the layers supported by the physical device and check if the layers we want to enable are there
	uint32_t deviceLayersPropertiesCount = 0;
	vkEnumerateDeviceLayerProperties(phyisicalDeviceToUse, &deviceLayersPropertiesCount, NULL);

	VkLayerProperties * properties = new VkLayerProperties[deviceLayersPropertiesCount];
	if (vkEnumerateDeviceLayerProperties(phyisicalDeviceToUse, &deviceLayersPropertiesCount, properties) != VK_SUCCESS)
	{
		delete properties;
		platform->ReportError(_T("[VK]Unable to enumerate device layer properties"), false);
		return VK_NULL_HANDLE;
	}

	ss.str("");
	for (uint32_t i = 0; i < deviceLayersPropertiesCount; i++)
	{
		ss << "[VK]Device Layer " << i << " has name " << properties[i].layerName << std::endl;
	}
	platform->LogString(ss.str());

	if (!IsLayerListPresent(deviceLayers, properties, deviceLayersPropertiesCount))
	{
		delete properties;
		platform->ReportError(_T("[VK]Unable to find a device layer"), false);
		return VK_NULL_HANDLE;
	}

	delete properties;

	//Interface with the window system by creating a surface we can render on
	if (!CreateWSISurface())
	{
		platform->ReportError(_T("[VK]Unable to create wsi surface"), false);
		return VK_NULL_HANDLE;
	}


	//Find the queue that supports presenting to the wsi surface
	uint32_t queueToUse = UINT32_MAX;
	pfVkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
	assert(pfVkGetPhysicalDeviceSurfaceSupportKHR);

	uint32_t queueFamilyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(phyisicalDeviceToUse, &queueFamilyCount, NULL);

	VkQueueFamilyProperties * queuesProperties = new VkQueueFamilyProperties[queueFamilyCount];

	vkGetPhysicalDeviceQueueFamilyProperties(phyisicalDeviceToUse, &queueFamilyCount, queuesProperties);
	//If the queue has present support on the wsi surface
	VkBool32 * supportPresent = new VkBool32[queueFamilyCount];

	for (uint32_t i = 0; i < queueFamilyCount; i++)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(phyisicalDeviceToUse, i, surface, &supportPresent[i]);
	}

	//For now we are gonna support only one queue for presenting and graphics 
	for (uint32_t i = 0; i < queueFamilyCount; i++)
	{
		if (queuesProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && supportPresent[i] == VK_TRUE)
		{
			queueToUse = i;
			break;
		}
	}

	delete supportPresent;
	delete queuesProperties;

	if (queueToUse == UINT32_MAX)
	{
		platform->ReportError(_T("[VK]Unable to find present and graphics queue"), false);
		return VK_NULL_HANDLE;
	}

	float queuePrio[] = { 1.0f };
	VkDeviceQueueCreateInfo queueCreateInfo
	{
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		NULL,
		0,
		queueToUse,
		1,
		queuePrio,
	};

	renderingPresentQueueFamilyIndex = queueToUse;

	//Enumerate layers and extensions and see if we can enable the ones we need
	uint32_t presentExtensionsCount;
	if (vkEnumerateDeviceExtensionProperties(phyisicalDeviceToUse, NULL, &presentExtensionsCount, NULL) != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to enumerate device extensions count"), false);
		return VK_NULL_HANDLE;
	}

	VkExtensionProperties * extensionsProperties = new VkExtensionProperties[presentExtensionsCount];
	if (vkEnumerateDeviceExtensionProperties(phyisicalDeviceToUse, NULL, &presentExtensionsCount, extensionsProperties) != VK_SUCCESS)
	{
		delete extensionsProperties;
		platform->ReportError(_T("[VK]Unable to enumerate device extensions"), false);
		return VK_NULL_HANDLE;
	}

	ss.str("");
	for (uint32_t i = 0; i < presentExtensionsCount; i++)
	{
		ss << "[VK]Device Extension " << i << " has name " << extensionsProperties[i].extensionName << std::endl;
	}
	platform->LogString(ss.str());

	if (!IsExtensionListPresent(deviceExtensions, extensionsProperties, presentExtensionsCount))
	{
		delete extensionsProperties;
		platform->ReportError(_T("[VK]Not all requested device extensions are present"), false);
		return VK_NULL_HANDLE;
	}

	delete extensionsProperties;

	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(phyisicalDeviceToUse, &features);

	VkDeviceCreateInfo deviceCreateInfo
	{
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		NULL,
		0,
		1,
		&queueCreateInfo,
		deviceLayers.size(),
		deviceLayers.data(),
		deviceExtensions.size(),
		deviceExtensions.data(),
		&features
	};

	VkDevice createdDevice;
	VkResult result = vkCreateDevice(phyisicalDeviceToUse, &deviceCreateInfo, NULL, &createdDevice);

	if (result != VK_SUCCESS)
	{
		platform->ReportError(_T("[VK]Unable to create device"), false);
		return VK_NULL_HANDLE;
	}

	vkGetDeviceQueue(createdDevice, renderingPresentQueueFamilyIndex, 0, &renderingPresentQueue);

	if (renderingPresentQueue == VK_NULL_HANDLE)
	{
		vkDestroyDevice(createdDevice, NULL);
		platform->ReportError(_T("[VK]Unable to get queue"));
		return VK_NULL_HANDLE;
	}

	return createdDevice;
}

bool VulkanAPI::Init(bool validate /*= false*/)
{
	//Enable validation layers for device and instance
	if (validate)
	{
		instanceLayers = { "VK_LAYER_GOOGLE_unique_objects",
			"VK_LAYER_LUNARG_device_limits",
			"VK_LAYER_LUNARG_draw_state",
			"VK_LAYER_LUNARG_image",
			"VK_LAYER_LUNARG_mem_tracker",
			"VK_LAYER_LUNARG_object_tracker",
			"VK_LAYER_LUNARG_param_checker",
			"VK_LAYER_LUNARG_swapchain",
			"VK_LAYER_LUNARG_threading",
			"VK_LAYER_LUNARG_api_dump" };
		deviceLayers = instanceLayers;
	}
	//Create and instance with its extensions and validation layers
	instance = CreateInstance();

	std::stringstream ss;
	ss << "[VK]Instance created"<<std::endl;
	platform->LogString(ss.str());
	ss.str("");

	//Enumerate all physical devices and find the first discrete one if present
	uint32_t pdCount = 0;
	vkEnumeratePhysicalDevices(instance, &pdCount, NULL);
	std::vector<VkPhysicalDevice> devices(pdCount);

	if (vkEnumeratePhysicalDevices(instance, &pdCount, devices.data()) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("Unable to enumerate physical devices"), true);
		return false;
	}

	ss << "[VK]found " << pdCount << " physical devices" << std::endl;
	platform->LogString(ss.str());

	for (uint32_t i = 0; i < pdCount; i++)
	{
		EnumeratePhysicalDeviceProperties(devices[i]);
	}

	//Use the first discrete gpu, if not present use the first in the array
	int deviceToUseId;
	VkPhysicalDevice physicalDeviceToUse = ChoosePhysicalDeviceToUse(devices.data(), pdCount, deviceToUseId);
	

	ss.str("");
	ss << "[VK]Using physical device " << deviceToUseId << std::endl;
	platform->LogString(ss.str());

	//Enumerate all the layers supported by the physical device and check if the layers we want to enable are there
	uint32_t deviceLayersPropertiesCount = 0;
	vkEnumerateDeviceLayerProperties(physicalDeviceToUse, &deviceLayersPropertiesCount, NULL);
	
	VkLayerProperties * properties = new VkLayerProperties[deviceLayersPropertiesCount];
	if (vkEnumerateDeviceLayerProperties(physicalDeviceToUse, &deviceLayersPropertiesCount, properties) != VK_SUCCESS)
	{
		delete properties;
		DeInit();
		platform->ReportError(_T("Unable to enumerate device layer properties"), true);
		return false;
	}

	ss.str("");
	for (uint32_t i = 0; i < deviceLayersPropertiesCount; i++)
	{
		ss << "[VK]Device Layer " << i << " has name " << properties[i].layerName << std::endl;
	}
	platform->LogString(ss.str());

	if (!IsLayerListPresent(deviceLayers, properties, deviceLayersPropertiesCount))
	{
		delete properties;
		DeInit();
		platform->ReportError(_T("Unable to find a device layer"), true);
		return false;
	}

	delete properties;

	//Interface with the window system by asking for a surface we can render on
	if (!CreateWSISurface())
	{
		DeInit();
		platform->ReportError(_T("Unable to create wsi surface"), true);
		return false;
	}

	//Create a device with all the layers and extensions requested
	device = CreateDevice(devices, physicalDeviceToUse, deviceToUseId);

	if (device == VK_NULL_HANDLE)
	{
		DeInit();
		platform->ReportError(_T("Unable to create device"), true);
		return false;
	}

	vkGetPhysicalDeviceMemoryProperties(physicalDeviceToUse, &currentDeviceMemoryProperties);

	//Create the swapchain
	if (!CreateSwapChainForPhysicalDevice(physicalDeviceToUse, swapchainFormat, swapchainColorSpace, swapchainExtent))
	{
		DeInit();
		platform->ReportError(_T("Unable to complete swapchain creation"), true);
		return false;
	}

	//Allocate a command buffer pool (used for the rendering and init command buffers)
	VkCommandPoolCreateInfo commandPoolCreateInfo
	{
		VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		NULL,
		VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		renderingPresentQueueFamilyIndex
	};

	if (vkCreateCommandPool(device, &commandPoolCreateInfo, NULL, &commandPool) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("Unable to create queue"), true);
		return false;
	}

	//Create a command buffer to use for the swapchain images layout transition 
	VkCommandBufferAllocateInfo allocateInfo
	{
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		NULL,
		commandPool,
		VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		1
	};

	//Get the swapchain images, for each one create an image view and set the image layout 
	//The command initCommandBuffer buffer is needed for the layout swap to color attachment
	VkCommandBuffer initCommandBuffer;
	if (vkAllocateCommandBuffers(device, &allocateInfo, &initCommandBuffer) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("Unable to allocate init command buffer"), true);
		return false;
	}

	VkCommandBufferBeginInfo commandBufferBeginInfo
	{
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		NULL,
		0,
		NULL
	};

	if (vkBeginCommandBuffer(initCommandBuffer, &commandBufferBeginInfo) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("Unable to begin command buffer"), true);
		return false;
	}

	swapchainImagesBuffer = GetImagesFromSwapchain(device, swapchain, swapchainFormat, swapchainColorSpace, initCommandBuffer, swapchainImagesCount);

	if (!swapchainImagesBuffer)
	{
		DeInit();
		platform->ReportError(_T("Unable to complete swapchain creation"), true);
		return false;
	}


	if (vkEndCommandBuffer(initCommandBuffer) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("Unable to end command buffer"), true);
		return false;
	}

	VkQueue renderingPresentQueue = VK_NULL_HANDLE;
	vkGetDeviceQueue(device, renderingPresentQueueFamilyIndex, 0, &renderingPresentQueue);

	if(renderingPresentQueue == VK_NULL_HANDLE)
	{
		DeInit();
		platform->ReportError(_T("Unable to get queue"), true);
		return false;
	}

	VkSubmitInfo submitInfo
	{
		VK_STRUCTURE_TYPE_SUBMIT_INFO,
		NULL,
		0,
		NULL,
		NULL,
		1,
		&initCommandBuffer,
		0,
		NULL
	};

	if (vkQueueSubmit(renderingPresentQueue, 1, &submitInfo, NULL) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("Unable to submit queue"), true);
		return false;
	}

	if (vkQueueWaitIdle(renderingPresentQueue) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("Unable to wait on queue idle"), true);
		return false;
	}

	vkFreeCommandBuffers(device, commandPool, 1, &initCommandBuffer);


	//Create a renderpass to use in the drawing command buffer
	renderPass = PrepareRenderPass(swapchainFormat, { (uint32_t)swapchainExtent.width, (uint32_t)swapchainExtent.height });

	if (renderPass == VK_NULL_HANDLE)
	{
		DeInit();
		platform->ReportError(_T("Unable to pepare renderpass"), true);
		return false;
	}

	//Create a framebuffer for each swaphcain image
	framebuffers = CreateFrameBufferFromSwapchainImages(device, renderPass, swapchainImagesBuffer, swapchainImagesCount);

	if (!framebuffers)
	{
		DeInit();
		platform->ReportError(_T("Unable to complete framebuffers creation"), true);
		return false;
	}

	//Create the vertex and fragment spir-v shaders

	VkShaderModule vertexShader = CreateShaderModule(device, ".\\Shaders\\tri-vert.spv");

	if (vertexShader == VK_NULL_HANDLE)
	{
		DeInit();
		platform->ReportError(_T("Unable to create vertex shader"), true);
		return false;
	}

	VkShaderModule pixelShader = CreateShaderModule(device, ".\\Shaders\\tri-frag.spv");

	if (pixelShader == VK_NULL_HANDLE)
	{
		DeInit();
		platform->ReportError(_T("Unable to create pixel shader"), true);
		return false;
	}


	//Create, allocate, and bind a vertex buffer
	vertices = CreateVertexBuffer(device, currentDeviceMemoryProperties);

	if (!vertices)
	{
		DeInit();
		platform->ReportError(_T("Unable to create vertex buffer"), true);
		return false;
	}

	pipeline = CreatePipeline(device, vertexShader, pixelShader, renderPass);

	if (pipeline == VK_NULL_HANDLE)
	{
		DeInit();
		platform->ReportError(_T("Unable to create pipeline"), true);
		return false;
	}

	vkDestroyShaderModule(device, pixelShader,  NULL);
	vkDestroyShaderModule(device, vertexShader, NULL);

	//Create the command buffer we will use for rendering and presenting to the screen
	VkCommandBufferAllocateInfo renderingPresentAllocateInfo
	{
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		NULL,
		commandPool,
		VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		1
	};

	if (vkAllocateCommandBuffers(device, &renderingPresentAllocateInfo, &renderingPresentCommandBuffer) != VK_SUCCESS)
	{
		DeInit();
		platform->ReportError(_T("[VK]Unable to allocate init command buffer"), true);
	}


	return true;
}