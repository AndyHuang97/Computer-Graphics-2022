// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <cstdint> // Necessary for uint32_t
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

struct QueueFamilyIndices {
    /* Queue families may not overlap so we need to store them separately */
	std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Assignment13 {
public:
    void run() {
        initWindow();
        initVulkan();
        initApp();
        mainLoop();
        cleanup();
    }

private:	
    const char* APP_NAME = "Assignment 14";
    GLFWwindow* window;
    VkInstance instance; /* interface between app and Vulkan lib */
    VkSurfaceKHR surface; /* Object is platform agnostic but creation is not */
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice logicalDevice;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkCommandPool commandPool; /* Manages memory used to store the buffers */
    VkCommandBuffer commandBuffer;
    VkSwapchainKHR swapChain; /* Queue of images to presented on screen */
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews; /* Image views describe how to access the image and which part of the image to access, e.g. texture */

    void initWindow() {
        glfwInit(); // initialize GLFW library

		// Continue with window creation
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); /* do not create OpenGL context, which is default */
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, APP_NAME, nullptr, nullptr);  /* #4: monitor #5: only for OpenGL  */
    }

    void initVulkan() {
		createInstance();
		// Prsentation Surface Creation
        createSurface();
        // Physical Device selection
        pickPhysicalDevice();
		// Logical Device creation
        createLogicalDevice();
		// Command Pool creation
        createCommandPool();
		// Command Buffer creation
        createCommandBuffers();

        /********* New ********/
        // Swap chain creation
        createSwapChain();
        // Image view creation
        createImageViews();
    }

    void createInstance() {
    	// place your Vulkan instance creation code here [you can take it from Assingment 12]
        /* appInfo is optional, useful for drive optimization */
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = APP_NAME;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        // appInfo.pNext = nullptr; /* can point to extension information */

        /* createInfo is mandatory: tell driver which global extensions and validation layers to use */
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // query the number of GLFW extensions
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        // query the name of GLFW extensions
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        if (!requiredExtensionsAvailable(glfwExtensionCount, glfwExtensions))
            throw std::runtime_error("Some required extensions are missing!");

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0; /* validation layers */

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); /* #2: custom allocator callback */
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    bool requiredExtensionsAvailable(uint32_t glfwExtensionCount, const char** glfwExtensions) {
        // query the number of instance extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); /* #1: allows to filter extensions by specific validation layer */
        // query the name of the instance extensions
        /* VkExtensionProperties fields: extensionName, specVersion */
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::vector<std::string> extensionNames;
        std::transform(extensions.begin(), extensions.end(), std::back_inserter(extensionNames), 
                       [] (auto extension) -> std::string {return extension.extensionName;});

        bool allAvailable = true;
		for(int i = 0; i < glfwExtensionCount; i++) {
            if (std::find(extensionNames.begin(), extensionNames.end(), glfwExtensions[i]) == extensionNames.end()) {
                allAvailable = false;
                std::cout << "\tMissing " << glfwExtensions[i] << '\n';
            }
		}

        return allAvailable;
    }

    void createSurface() {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) { /* #3: custom allocator */
			throw std::runtime_error("failed to create window surface!");
		}
    }

    void pickPhysicalDevice() {
    	uint32_t deviceCount = 0;
    	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    	 
    	if (deviceCount == 0) {
			throw std::runtime_error("Failed to find GPUs with Vulkan support!");
		}
		
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
		
		for (const auto& device : devices) {
            /* Could also use a score of suitability for each device */
			if (isDeviceSuitable(device)) {
				physicalDevice = device;
		        std::cout << "\nFound suitable physical device!\n";
				break;
			}
		}
		
		if (physicalDevice == VK_NULL_HANDLE) {
			throw std::runtime_error("Failed to find a suitable GPU!");
		}
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        /* Use device properties and features to determine suitability */
        // VkPhysicalDeviceProperties deviceProperties;
        // VkPhysicalDeviceFeatures deviceFeatures;
        // vkGetPhysicalDeviceProperties(device, &deviceProperties);
        // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        QueueFamilyIndices indices = findQueueFamilies(device);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}

    bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }
    
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        std::cout << "Capabilities" << "\n";
        std::cout << "\tminImageCount = " << details.capabilities.minImageCount << "\n";
        std::cout << "\tmaxImageCount = " << details.capabilities.maxImageCount << "\n";
        // std::cout << "\tcurrentExtent = " << details.capabilities.currentExtent << "\n";
        // std::cout << "\tminImageExtent = " << details.capabilities.minImageExtent << "\n";
        // std::cout << "\tmaxImageExtent = " << details.capabilities.maxImageExtent << "\n";
        std::cout << "\tmaxImageArrayLayers = " << details.capabilities.maxImageArrayLayers << "\n";
        std::cout << "\tsupportedTransforms = " << details.capabilities.supportedTransforms << "\n";
        std::cout << "\tcurrentTransform = " << details.capabilities.currentTransform << "\n";
        std::cout << "\tsupportedCompositeAlpha = " << details.capabilities.supportedCompositeAlpha << "\n";
        std::cout << "\tsupportedUsageFlags = " << details.capabilities.supportedUsageFlags << "\n";


        std::cout << "\nFormats: " << details.formats.size() << "\n";

        std::cout << "\nPresentation Modes" << "\n";
        for (auto presentMode : details.presentModes)
        {   
            switch (presentMode)
            {
            case 0:
                std::cout << "\tVK_PRESENT_MODE_IMMEDIATE_KHR\n";
                break;
            case 1:
                std::cout << "\tVK_PRESENT_MODE_MAILBOX_KHR\n";
                break;
            case 2:
                std::cout << "\tVK_PRESENT_MODE_FIFO_KHR\n";
                break;
            case 3:
                std::cout << "\tVK_PRESENT_MODE_FIFO_RELAXED_KHR\n";
                break;
            case 1000111000:
                std::cout << "\tVK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR\n";
                break;
            case 1000111001:
                std::cout << "\tVK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR\n";
                break;
            default:
                break;
            }
        }
        
        return details;
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
		QueueFamilyIndices indices;
		
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        /* VkQueueFamilyProperties: queueFlags, queueCount, timestampValidBits, minImageTransferGranularity */
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
								queueFamilies.data());
								
		int i=0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) { /* Support for graphic commands */
				indices.graphicsFamily = i;
			}
				
			VkBool32 presentSupport = false; /* Support for presentation on a window surface */
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface,
												 &presentSupport);
			if (presentSupport) {
			 	indices.presentFamily = i;
			}
            /* Could add logic for preferring same graphic and presentation queue for performance */

			if (indices.isComplete()) {
				break;
			}	

			i++;
		}

		return indices;
	}

    /* Create a logical device to interface with the physical one */
    void createLogicalDevice() {
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
		
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies =
				{indices.graphicsFamily.value(), indices.presentFamily.value()};
		
		float queuePriority = 1.0f; /* 0 < p < 1 influences scheduling of command buffers */
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1; /* low number, but okay bc can use multiple command buffers */
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}
		
		VkPhysicalDeviceFeatures deviceFeatures{};
		
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
		
		VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice);
		
		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create logical device!");
		}
		
        /* 0 is the queue index, okay bc we create a single queue for each family */
		vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentQueue);
        std::cout << "Logical device created\n";
	}

    void createCommandPool() {
    	QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

        /* 
        Command buffers are executed by submitting them on one device queue.
        Each command buffer can only allocate command buffers for one single type of queue.
         */		
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; 
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
		
		VkResult result = vkCreateCommandPool(logicalDevice, &poolInfo, nullptr, &commandPool);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create command pool!");
		}
        std::cout << "Command Pool created\n";
	}
	
    void createCommandBuffers() {
    	VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; 
		allocInfo.commandBufferCount = 1;
		
		VkResult result = vkAllocateCommandBuffers(logicalDevice, &allocInfo, &commandBuffer);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to allocate command buffers!");
		}
        std::cout << "Command Buffers created\n";
	}

    void createSwapChain() {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1; /* always 1 unless stereoscopic 3D app */
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; /* VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing */


        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT; /* Must have at least 2 different queues */
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; /* Most common case when graphi=present queue */
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform; /* e.g. rotation or flip */
        
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; /* if alpha should be used for blending with other windows */

        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE; /* Don't care about color of obscured pixels, better performance */

        createInfo.oldSwapchain = VK_NULL_HANDLE; /* If window is resized, the swap chain may become unoptimized. Need a new one from scratch */

        if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create swap chain!");
        }

        std::cout << "Swap Chain created\n";

        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormat;
        }
        return availableFormats[0]; /* If our best is not found, could do ranking instead of just the first one */
    }

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    /* Swap extent is the resolution of the swap chain images, always equal to window's resolution in pixels */
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        } else { /* Not allowed to match currentExtent by window manager */
            int width, height;
            glfwGetFramebufferSize(window, &width, &height); /* For high DPI display like Apple's Retina display */

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }
    
    void createImageViews() {
        swapChainImageViews.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo createInfo{};

            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];

            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D; /* Texture type */
            createInfo.format = swapChainImageFormat;

            /* Can also be 0 or 1 */
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY; 
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            
            /* Image's purpose and which part should be accessed */
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1; /* More than 1 for stereographic 3D images */

            if (vkCreateImageView(logicalDevice, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image views!");
            }
            std::cout << "Image view created\n";
        }

    }

    void initApp() {
		// This will not be needed in this assignment!
	}

    void mainLoop() {
    	// Wait for the window to close [you can take it from Assingment 12]
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
    	// Add code to release all resources
        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(logicalDevice, imageView, nullptr);
        }
        vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);
        vkDestroyCommandPool(logicalDevice, commandPool, nullptr); /* #3: allocator callback */
        vkDestroyDevice(logicalDevice, nullptr);		
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "\nResources released correctly\n\n";
    }
};

int main() {
    Assignment13 app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}