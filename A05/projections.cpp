glm::vec3 MIRROR_Y = glm::vec3(1,-1,1);
glm::mat4 I = glm::mat4(1.0f);

float n = 0.1f; // remember: for perspective projections n > 0
float f = 9.9f;

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o
glm::mat4 PO1(float a) {
	float fov = 90.0f;
	float ang = glm::radians(fov/2);

	float t = n * std::tan(ang);
	float b = - t;
	float r = a * t;
	float l = - r;

	// 1.
	glm::mat4 out = glm::scale(I, MIRROR_Y) * glm::frustum(l, r, b, t, n, f);

	// 2.
	// glm::mat4 out = glm::perspective(glm::radians(fov), a, n ,f);
	// out[1][1] *= -1;
	return out;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a) {
	float fov = 120.0f;

	glm::mat4 out = glm::perspective(glm::radians(fov), a, n ,f);
	out[1][1] *= -1;
	return out;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a) {
	float fov = 30.0f;

	glm::mat4 out = glm::perspective(glm::radians(fov), a, n ,f);
	out[1][1] *= -1;
	return out;
}

// Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
	float fov = 90.0f;
	float ang = glm::radians(fov/2);

	float t = n * std::tan(ang);
	float b = - t;

	float r = 0;
	float l = - a * n * std::tan(ang) * 2; // show the entire left screen --> x2

	// 1.
	glm::mat4 out = glm::scale(I, MIRROR_Y) * glm::frustum(l, r, b, t, n, f);
	return out;
}

