float angX, angY, angZ;
glm::vec3 AXIS_X = glm::vec3(1,0,0);
glm::vec3 AXIS_Y = glm::vec3(0,1,0);
glm::vec3 AXIS_Z = glm::vec3(0,0,1);
glm::vec3 MIRROR_Y = glm::vec3(1,-1,1);
glm::mat4 Rx, Ry;
glm::mat4 I = glm::mat4(1);
float w = 2;
float n = -4;
float f = 12;
float l = -w;
float r = w;


// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a) {
	angX = glm::radians(35.26f);
	angY = glm::radians(45.0f);
	Rx = glm::rotate(I, angX, AXIS_X);
	Ry = glm::rotate(I, angY, AXIS_Y);

	float t = w/a;
	float b = -w/a;

	// 1.
	// glm::mat4 Port = glm::translate(I, glm::vec3(0,0,n/(n-f))) * glm::scale(I, glm::vec3(1/w, -a/w, 1/(n-f)));
	
	// 2.
	// glm::mat4 T = glm::translate(I, glm::vec3(0,0,n/(n-f)));
	// glm::mat4 Port = glm::scale(T, glm::vec3(1/w, -a/w, 1/(n-f)));

	// 3.
	// glm::mat4 Port = glm::transpose(glm::mat4(1/w,			0,			0,			0,
	// 											0,		 -a/w, 			0, 			0,
	// 											0,			0,	  1/(n-f), 	  n/(n-f),
	// 											0,			0,			0,			1));

	// 4.
	glm::mat4 Port = glm::scale(I, MIRROR_Y) * glm::ortho(l, r, b, t, n, f);
	glm::mat4 out = Port * Rx * Ry;
	return out;
}

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a) {
	float alpha = 45.0f;
	angX = glm::radians(alpha);
	angY = glm::radians(45.0f);
	Rx = glm::rotate(I, angX, AXIS_X);
	Ry = glm::rotate(I, angY, AXIS_Y);

	float t = w/a;
	float b = -w/a;

	glm::mat4 Port = glm::scale(I, MIRROR_Y) * glm::ortho(l, r, b, t, n, f);
	glm::mat4 out = Port * Rx * Ry;
	return out;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a) {
	float alpha = 45.0f;
	float beta = 60.0f;
	angX = glm::radians(alpha);
	angY = glm::radians(beta);
	Rx = glm::rotate(I, angX, AXIS_X);
	Ry = glm::rotate(I, angY, AXIS_Y);

	float t = w/a;
	float b = -w/a;

	glm::mat4 Port = glm::scale(I, MIRROR_Y) * glm::ortho(l, r, b, t, n, f);
	glm::mat4 out = Port * Rx * Ry;
	return out;
}

// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a) {
	float alpha = glm::radians(45.0f);
	float ro = 0.5f;
	float sXZ = - ro * std::cos(alpha);
	float sYZ = - ro * std::sin(alpha);
	glm::mat4 ShearZ = glm::transpose(glm::mat4(1,			0,		  sXZ,			0,
												0,		 	1, 		  sYZ, 			0,
												0,			0,	  		1, 	  		0,
												0,			0,			0,			1));

	float t = w/a;
	float b = -w/a;

	glm::mat4 Port = glm::scale(I, MIRROR_Y) * glm::ortho(l, r, b, t, n, f);
	glm::mat4 out = Port * ShearZ;
	return out;
}

