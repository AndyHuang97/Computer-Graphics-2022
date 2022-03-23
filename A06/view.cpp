glm::mat4 I = glm::mat4(1.0);
glm::vec3 AXIS_X = glm::vec3(1,0,0);
glm::vec3 AXIS_Y = glm::vec3(0,1,0);
glm::vec3 AXIS_Z = glm::vec3(0,0,1);

 // Create a look in direction matrix
 // Pos    -> Position of the camera
 // Angs.x -> direction (alpha)
 // Angs.y -> elevation (beta)
 // Angs.z -> roll (rho)
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {
	float alpha = Angs.x; //already in radians
	float beta = Angs.y;
	float rho = Angs.z;

	glm::mat4 T = glm::translate(I, Pos);
	glm::mat4 Rx = glm::rotate(I, beta, AXIS_X);
	glm::mat4 Ry = glm::rotate(I, alpha, AXIS_Y);
	glm::mat4 Rz = glm::rotate(I, rho, AXIS_Z);

	glm::mat4 Mv = glm::inverse(T * Ry * Rx * Rz);
	return Mv;
}

 // Create a look at matrix
 // Pos    -> Position of the camera (c)
 // aim    -> Posizion of the target (a)
 // Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {
	glm::vec3 u = glm::vec3(0,1,0);
	glm::vec3 vz = glm::normalize(Pos - aim);
	glm::vec3 uXvz = glm::cross(u, vz);
	glm::vec3 vx = glm::normalize(uXvz);
	glm::vec3 vy = glm::cross(vz, vx);
	glm::mat4 Rz = glm::rotate(I, -Roll, AXIS_Z); // for tilting

	// 1.
	glm::mat4 Mc = glm::mat4(glm::vec4(vx,0), 
							 glm::vec4(vy,0), 
							 glm::vec4(vz,0), 
							 glm::vec4(Pos,1));
	glm::mat4 Mv = glm::inverse(Mc);

	// 2.
	// glm::mat4 Mv = glm::lookAt(Pos,
	// 						   aim,
	// 						   u
	// 						  );

	Mv = Rz * Mv;
	return Mv;
}



