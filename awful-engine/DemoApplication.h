#pragma once
#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif // GLFW_INCLUDE_VULKAN

#include "InitCfg.h";
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class DemoTriangleApplication {
public:
    void Run() {
        std::cout << "Begin running demo app" << std::endl;
        InitWindow();
        InitVulkan();
        MainLoop();
        Cleanup();
    }

private:
    void InitWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(gamecfg::WIDTH, gamecfg::HEIGHT, gamecfg::NAME, nullptr, nullptr);
    }

    void InitVulkan() {
        CreateInstance();
    }

    void CreateInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        if(vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
            throw std::runtime_error("vkCreateInstance -> failed to create instance");

        // Check for extension count
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:\n";

        for(const auto& extension : extensions)
            std::cout << '\t' << "'" << extension.extensionName << "'" << '\n';

        uint32_t requiredExtensionCount;
        auto reqExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionCount);

        std::cout << "Required extension count: " << requiredExtensionCount << std::endl;
        for(int i = 0; i < requiredExtensionCount; i++) {
            std::cout << "Required extension: " << "'" << reqExtensions[i] << "'" << std::endl;
        }



        for(int i = 0; i < requiredExtensionCount; i++) {
            bool found = false;

            for(const auto& available : extensions) {
                if(strcmp(reqExtensions[i], available.extensionName) == 0) {
                    found = true;
                    break;
                }
            }

            if(found) {
                std::cout << "Extension " << reqExtensions[i] << " is supported!" << std::endl;
            }
            else
                std::cout << "Extension " << reqExtensions[i] << " is NOT supported!" << std::endl;
        }


    }

    void MainLoop() 
    {
        while(!glfwWindowShouldClose(_window))
        {
            glfwPollEvents();
        }
    }

    void Cleanup() 
    {
        vkDestroyInstance(_instance, nullptr);
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    GLFWwindow* _window;
    VkInstance _instance;
};

int MainDemo() {
    DemoTriangleApplication app;

    try {
        app.Run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}