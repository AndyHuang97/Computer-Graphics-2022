	glm::vec3 AXIS_X = glm::vec3(1,0,0);
	glm::vec3 AXIS_Y = glm::vec3(0,1,0);
	glm::vec3 AXIS_Z = glm::vec3(0,0,1);

	// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). 
	// The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, 
	// and then -60 degrees around the y-axis.
	glm::vec3 axisPoint = glm::vec3(1,0,-1);
	glm::mat4 T = glm::translate(glm::mat4(1), axisPoint);
	float angX = glm::radians(45.0f);
	float angY = glm::radians(-60.0f);
	float angZ = glm::radians(30.0f);
	glm::mat4 Rx = glm::rotate(glm::mat4(1), angX, AXIS_X);
	glm::mat4 Ry = glm::rotate(glm::mat4(1), angY, AXIS_Y);
	glm::mat4 Rz = glm::rotate(glm::mat4(1), angZ, AXIS_Z);
	
	glm::mat4 MT1 = T * Ry * Rz * Rx * inverse(Rz) * inverse(Ry) * inverse(T);
			   
	// Half the size of an object, using as fixed point (5,0,-2)
	glm::vec3 fixedPoint = glm::vec3(5,0,-2);
	T = glm::translate(glm::mat4(1), fixedPoint);
	float scaling = 0.5;
	glm::mat4 S = glm::scale(glm::mat4(1), glm::vec3(scaling));

	glm::mat4 MT2 = T * S * inverse(T);
			   
	// Mirror the starship along a plane passing through (1,1,1), 
	// and obtained rotating 15 degree around the x axis the xz plane
	glm::vec3 planePoint = glm::vec3(1,1,1);
	T = glm::translate(glm::mat4(1), planePoint);
	angX = glm::radians(15.0f);
	Rx = glm::rotate(glm::mat4(1), angX, AXIS_X);
	glm::vec3 mirrorY = glm::vec3(1,-1,1);
	glm::mat4 M = glm::scale(glm::mat4(1), mirrorY);

	glm::mat4 MT3 = T * Rx * M * inverse(Rx) * inverse(T);
			   
	// Apply the inverse of the following sequence of transforms: 
	// Translation of (0, 0, 5) then rotation of 30 degree around the Y axis,
	// and finally a uniform scaling of a factor of 3.
	T = glm::translate(glm::mat4(1), glm::vec3(0,0,5));
	angY = glm::radians(30.0f);
	Ry = glm::rotate(glm::mat4(1), angY, AXIS_Y);
	scaling = 3.0;
	S = glm::scale(glm::mat4(1), glm::vec3(scaling));

	glm::mat4 MT4 = inverse(T) * inverse(Ry) * inverse(S);

