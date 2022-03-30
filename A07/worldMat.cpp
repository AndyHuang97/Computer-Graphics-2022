glm::mat4 I = glm::mat4(1.0);
glm::vec3 AXIS_X = glm::vec3(1,0,0);
glm::vec3 AXIS_Y = glm::vec3(0,1,0);
glm::vec3 AXIS_Z = glm::vec3(0,0,1);
// Create a world matrix using position, Euler angles, and size
// Euler angles are passed in YPR parameter:
// YPR.x : Yaw
// YPR.y : Pitch
// YPR.z : Roll
glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size) {
	float roll = glm::radians(YPR.z);
	float pitch = glm::radians(YPR.y);
	float yaw = glm::radians(YPR.x);
	
	glm::mat4 T = glm::translate(I, pos);
	glm::mat4 Ry = glm::rotate(I, yaw, AXIS_Y);
	glm::mat4 Rx = glm::rotate(I, pitch, AXIS_X);
	glm::mat4 Rz = glm::rotate(I, roll, AXIS_Z);
	glm::mat4 S = glm::scale(I, size);
	glm::mat4 out = T * Ry * Rx * Rz * S;
	return out;
}

// Create a world matrix using position, quaternion angles, and size
glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size) {
	glm::mat4 T = glm::translate(I, pos);
	glm::mat4 R = glm::mat4(rQ);
	glm::mat4 S = glm::scale(I, size);

	glm::mat4 out = T * R * S;
	return out;
}

