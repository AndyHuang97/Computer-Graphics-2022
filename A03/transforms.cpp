	glm::vec3 AXIS_X = glm::vec3(1,0,0);
	glm::vec3 AXIS_Y = glm::vec3(0,1,0);
	glm::vec3 AXIS_Z = glm::vec3(0,0,1);
	glm::vec3 MIRROR_Y = glm::vec3(1,-1,1);
	glm::mat4 T, Rx, Ry, Rz, S, refPos;
	glm::mat4 I = glm::mat4(1);
	float angX, angY, angZ;
	float scaling;

	auto transform = [=] (glm::mat4 refPos, glm::mat4 transformMatrix) {
		return refPos * transformMatrix * inverse(refPos);
	};

	// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). 
	// The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, 
	// and then -60 degrees around the y-axis.
	glm::vec3 axisPoint = glm::vec3(1,0,-1);
	T = glm::translate(I, axisPoint);
	angX = glm::radians(45.0f);
	angY = glm::radians(-60.0f);
	angZ = glm::radians(30.0f);
	Ry = glm::rotate(I, angY, AXIS_Y);
	Rz = glm::rotate(I, angZ, AXIS_Z);

	Rx = glm::rotate(I, angX, AXIS_X);
	refPos = T * Ry * Rz;

	glm::mat4 MT1 = transform(refPos, Rx);
			   
	// Half the size of an object, using as fixed point (5,0,-2)
	glm::vec3 fixedPoint = glm::vec3(5,0,-2);
	T = glm::translate(I, fixedPoint);
	scaling = 0.5;

	S = glm::scale(I, glm::vec3(scaling));
	refPos = T;

	glm::mat4 MT2 = transform(refPos, S);
			   
	// Mirror the starship along a plane passing through (1,1,1), 
	// and obtained rotating 15 degree around the x axis the xz plane
	glm::vec3 planePoint = glm::vec3(1,1,1);
	T = glm::translate(I, planePoint);
	angX = glm::radians(15.0f);
	Rx = glm::rotate(I, angX, AXIS_X);

	S = glm::scale(I, MIRROR_Y);
	refPos = T * Rx;

	glm::mat4 MT3 = transform(refPos, S);
			   
	// Apply the inverse of the following sequence of transforms: 
	// Translation of (0, 0, 5) then rotation of 30 degree around the Y axis,
	// and finally a uniform scaling of a factor of 3.
	T = glm::translate(I, glm::vec3(0,0,5));
	angY = glm::radians(30.0f);
	Ry = glm::rotate(I, angY, AXIS_Y);
	scaling = 3.0;
	S = glm::scale(I, glm::vec3(scaling));

	glm::mat4 MT4 = inverse(S * Ry * T);

