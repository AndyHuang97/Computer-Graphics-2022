// Following the Vulkan Tutorial until the
// Drawing a triangle -> Setup -> Instance
// section (currently at https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance)
// create a 640 x 480 window, with title "Assignment 12", and list the global
// extensions supported by your O.S. 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment12 {
public:
    // complete the Assignment class here 
    void run() {
        initWindow();
        initVulkan();
        // initApp();
        mainLoop();
        cleanup();
    }

private:
    VkInstance instance;
    GLFWwindow* window;
    const char* APP_NAME = "Assignment 12";

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, APP_NAME, nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();   
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
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

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0; /* validation layers */

        if (!requiredExtensionsAvailable(glfwExtensionCount, glfwExtensions))
            throw std::runtime_error("Some required extensions are missing!");

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

        std::cout << "available extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }

        std::cout << "\nExtensions required by GLFW:\n";
        bool allAvailable = true;
		for(int i = 0; i < glfwExtensionCount; i++) {
            std::cout << "\t" << glfwExtensions[i] << '\n';
            if (std::find(extensionNames.begin(), extensionNames.end(), glfwExtensions[i]) == extensionNames.end()) {
                allAvailable = false;
                std::cout << "\tMissing " << glfwExtensions[i] << '\n';
            }
		}

        return allAvailable;
    }
};

int main() 
{
    Assignment12 app;

    try 
    {
        app.run();
    } catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}