#pragma once
#pragma once
#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif // GLFW_INCLUDE_VULKAN

namespace gpufeatures {
	VkPhysicalDeviceFeatures deviceFeatures{};
	void InitGraphicsFeatures(VkPhysicalDeviceFeatures* pFeatures) {
		VkBool32 samplerOnOff = VK_FALSE;
		pFeatures->samplerAnisotropy = samplerOnOff;
		if(pFeatures->samplerAnisotropy != samplerOnOff)
			throw std::runtime_error("Failed to initialize graphics features!");
		std::cout << "Graphics settings initialized" << std::endl;
	}
}