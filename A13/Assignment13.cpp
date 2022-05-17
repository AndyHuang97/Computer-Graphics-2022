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
    const char* APP_NAME = "Assignment 13";
    GLFWwindow* window;
    VkInstance instance; /* interface between app and Vulkan lib */
    VkSurfaceKHR surface; /* Object is platform agnostic but creation is not */
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice logicalDevice;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkCommandPool commandPool; /* Manages memory used to store the buffers */
    VkCommandBuffer commandBuffer;

    void initWindow() {
        glfwInit(); // initialize GLFW library

		// Continue with window creation
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); /* do not create OpenGL context, which is default */
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, APP_NAME, nullptr, nullptr);  /* #4: monitor #5: only for OpenGL  */
    }

    void initVulkan() {
		createInstance();
		// Continue with:
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
		        std::cout << "Found suitable physical device!\n";
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

        return indices.isComplete();
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
		createInfo.enabledExtensionCount = 0; /* VK_KHR_swapchain extension */
		
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
        vkDestroyCommandPool(logicalDevice, commandPool, nullptr); /* #3: allocator callback */
        vkDestroyDevice(logicalDevice, nullptr);		
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "Resources released correctly\n\n";
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