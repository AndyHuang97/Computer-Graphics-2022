glm::mat4 I = glm::mat4(1.0);
glm::vec3 AXIS_X = glm::vec3(1,0,0);
glm::vec3 AXIS_Y = glm::vec3(0,1,0);
glm::vec3 AXIS_Z = glm::vec3(0,0,1);

glm::vec3 MOVE_SPEED = glm::vec3(1.0f);
float UP = glm::radians(90.0f);
float DOWN = glm::radians(270.0f);
float RIGHT = glm::radians(0.0f);
float LEFT = glm::radians(180.0f);

// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	static glm::vec3 pos = glm::vec3(-3,0,2);	// variable to store robot position
												// here glm::vec3(-3,0,2) represents a
												// meaningful initial position for the robot
	
	glm::mat4 out;
	glm::mat4 T = I;
	static glm::mat4 R = I;
	glm::mat4 S = glm::scale(I, glm::vec3(1.5f));
	
	static auto startTime = std::chrono::high_resolution_clock::now();
	static float lastTime = 0.0;

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period> (currentTime - startTime).count();
	float deltaT = time - lastTime;
	lastTime = time;

	if(glfwGetKey(window, GLFW_KEY_A)){
		pos += MOVE_SPEED * glm::vec3(-1,0,0) * deltaT; 
		R = glm::rotate(I, LEFT, AXIS_Y);
	}
	if(glfwGetKey(window, GLFW_KEY_D)){
		pos += MOVE_SPEED * glm::vec3(1,0,0) * deltaT;
		R = glm::rotate(I, RIGHT, AXIS_Y);
	}
	if(glfwGetKey(window, GLFW_KEY_W)){
		pos += MOVE_SPEED * glm::vec3(0,0,-1) * deltaT;
		R = glm::rotate(I, UP, AXIS_Y);
	}
	if(glfwGetKey(window, GLFW_KEY_S)){
		pos += MOVE_SPEED * glm::vec3(0,0,1) * deltaT;
		R = glm::rotate(I, DOWN, AXIS_Y);
	}
	T = glm::translate(I, pos);
	
	out = T * R * S;
	return out;
}

