float texture_unit = 1.0/8;
glm::mat4 I = glm::mat4(1.0f);
// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;



void makeCube() {
	//// M1 : Cube
	// Replace the code below, that creates a simple square, with the one to create a cube.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	int n_vertices = 8;
	M1_vertices.resize(3*n_vertices);

	// Each block contains vertices in the same spatial position but with different norms
	M1_vertices[0].pos  = glm::vec3(-1.0,-1.0,-1.0);
	M1_vertices[0].norm = glm::vec3(-1.0,0.0,0.0);
	M1_vertices[0].UV   = glm::vec2(texture_unit*0,texture_unit*2);
	M1_vertices[1].pos  = M1_vertices[0].pos;
	M1_vertices[1].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[1].UV   = glm::vec2(texture_unit*1,texture_unit*1);
	M1_vertices[2].pos  = M1_vertices[0].pos;
	M1_vertices[2].norm = glm::vec3(0.0,0.0,-1.0);
	M1_vertices[2].UV   = glm::vec2(texture_unit*1,texture_unit*1);

	M1_vertices[3].pos  = glm::vec3(1.0,-1.0,-1.0);
	M1_vertices[3].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[3].UV   = glm::vec2(texture_unit*3,texture_unit*2);
	M1_vertices[4].pos  = M1_vertices[3].pos;
	M1_vertices[4].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[4].UV   = glm::vec2(texture_unit*2,texture_unit*1);
	M1_vertices[5].pos  = M1_vertices[3].pos;
	M1_vertices[5].norm = glm::vec3(0.0,0.0,-1.0);
	M1_vertices[5].UV   = glm::vec2(texture_unit*2,texture_unit*1);

	M1_vertices[6].pos  = glm::vec3(1.0,1.0,-1.0);
	M1_vertices[6].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[6].UV   = glm::vec2(texture_unit*2,texture_unit*2);
	M1_vertices[7].pos  = M1_vertices[6].pos;
	M1_vertices[7].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[7].UV   = glm::vec2(texture_unit*2,texture_unit*2);
	M1_vertices[8].pos  = M1_vertices[6].pos;
	M1_vertices[8].norm = glm::vec3(0.0,0.0,-1.0);
	M1_vertices[8].UV   = glm::vec2(texture_unit*2,texture_unit*2);

	M1_vertices[9].pos  =  glm::vec3(-1.0,1.0,-1.0);
	M1_vertices[9].norm =  glm::vec3(-1.0,0.0,0.0);
	M1_vertices[9].UV   = glm::vec2(texture_unit*1,texture_unit*2);
	M1_vertices[10].pos  = M1_vertices[9].pos;
	M1_vertices[10].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[10].UV   = glm::vec2(texture_unit*1,texture_unit*2);
	M1_vertices[11].pos  = M1_vertices[9].pos;
	M1_vertices[11].norm = glm::vec3(0.0,0.0,-1.0);
	M1_vertices[11].UV   = glm::vec2(texture_unit*1,texture_unit*2);

	M1_vertices[12].pos  = glm::vec3(-1.0,1.0,1.0);
	M1_vertices[12].norm = glm::vec3(-1.0,0.0,0.0);
	M1_vertices[12].UV   = glm::vec2(texture_unit*1,texture_unit*3);
	M1_vertices[13].pos  = M1_vertices[12].pos;
	M1_vertices[13].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[13].UV   = glm::vec2(texture_unit*1,texture_unit*3);
	M1_vertices[14].pos  = M1_vertices[12].pos;
	M1_vertices[14].norm = glm::vec3(0.0,0.0,1.0);
	M1_vertices[14].UV   = glm::vec2(texture_unit*1,texture_unit*3);

	M1_vertices[15].pos  = glm::vec3(1.0,1.0,1.0);
	M1_vertices[15].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[15].UV   = glm::vec2(texture_unit*2,texture_unit*3);
	M1_vertices[16].pos  = M1_vertices[15].pos;
	M1_vertices[16].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[16].UV   = glm::vec2(texture_unit*2,texture_unit*3);
	M1_vertices[17].pos  = M1_vertices[15].pos;
	M1_vertices[17].norm = glm::vec3(0.0,0.0,1.0);
	M1_vertices[17].UV   = glm::vec2(texture_unit*2,texture_unit*3);

	M1_vertices[18].pos  = glm::vec3(1.0,-1.0,1.0);
	M1_vertices[18].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[18].UV   = glm::vec2(texture_unit*3,texture_unit*3);
	M1_vertices[19].pos  = M1_vertices[18].pos;
	M1_vertices[19].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[19].UV   = glm::vec2(texture_unit*2,texture_unit*0);
	M1_vertices[20].pos  = M1_vertices[18].pos;
	M1_vertices[20].norm = glm::vec3(0.0,0.0,1.0);
	M1_vertices[20].UV   = glm::vec2(texture_unit*2,texture_unit*4);

	M1_vertices[21].pos  = glm::vec3(-1.0,-1.0,1.0);
	M1_vertices[21].norm = glm::vec3(-1.0,0.0,0.0);
	M1_vertices[21].UV   = glm::vec2(texture_unit*0,texture_unit*3);
	M1_vertices[22].pos  = M1_vertices[21].pos;
	M1_vertices[22].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[22].UV   = glm::vec2(texture_unit*1,texture_unit*0);
	M1_vertices[23].pos  = M1_vertices[21].pos;
	M1_vertices[23].norm = glm::vec3(0.0,0.0,1.0);
	M1_vertices[23].UV   = glm::vec2(texture_unit*1,texture_unit*4);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	int n_triangles = 6 * 2;
	M1_indices.resize(3 * n_triangles);

	// first triangle
	M1_indices[0] = 2; 	// 0*3 + 2;
	M1_indices[1] = 5; 	// 1*3 + 2;
	M1_indices[2] = 8; 	// 2*3 + 2;

	// second triangle
	M1_indices[3] = 8;  // 2*3 + 2;
	M1_indices[4] = 11; // 3*3 + 2;
	M1_indices[5] = 2;  // 0*3 + 2;

	// 3
    M1_indices[6] = 7;	// 2*3 + 1;
    M1_indices[7] = 10;	// 3*3 + 1;
    M1_indices[8] = 13;	// 4*3 + 1;

    // 4
    M1_indices[9] =  7;	// 2*3 + 1;
    M1_indices[10] = 13;// 4*3 + 1;
    M1_indices[11] = 16;// 5*3 + 1;

    // 5
    M1_indices[12] = 3; // 1*3 + 0;
    M1_indices[13] = 6; // 2*3 + 0;
    M1_indices[14] = 15;// 5*3 + 0;

    // 6
    M1_indices[15] = 3;	// 1*3 + 0;
    M1_indices[16] = 15;// 5*3 + 0;
    M1_indices[17] = 18;// 6*3 + 0;

    // 7
    M1_indices[18] = 4; // 1*3 + 1;
    M1_indices[19] = 19;// 6*3 + 1;
    M1_indices[20] = 22;// 7*3 + 1;

    // 8
    M1_indices[21] = 1; // 0*3 + 1;
    M1_indices[22] = 4; // 1*3 + 1;
    M1_indices[23] = 22;// 7*3 + 1;

    // 9
    M1_indices[24] = 0; // 0*3 + 0;
    M1_indices[25] = 9; // 3*3 + 0;
    M1_indices[26] = 12;// 4*3 + 0;

    // 10
    M1_indices[27] = 0; // 0*3 + 0;
    M1_indices[28] = 12;// 4*3 + 0;
    M1_indices[29] = 21;// 7*3 + 0;

    // 11
    M1_indices[30] = 14;// 4*3 + 2;
    M1_indices[31] = 17;// 5*3 + 2;
    M1_indices[32] = 23;// 7*3 + 2;

    // 12
    M1_indices[33] = 17;// 5*3 + 2;
    M1_indices[34] = 20;// 6*3 + 2;
    M1_indices[35] = 23;// 7*3 + 2;
}

void printTriangle(const int triangleID, const int vertex1, const int vertex2, const int vertex3) {
    std::cout << "Triangle: " << triangleID;
    std::cout << "\t{ "  << vertex1;
    std::cout << "\t" << vertex2;
    std::cout << "\t" << vertex3;
    std::cout << "}" << std::endl;
};

void addCircleVerticesPos(std::vector<Vertex> &vertices, const float x,  const float y, const float z, const float coneHeight, const float r, const glm::mat4 rotMat, const int nSlices, const int centerIdx, bool centerExists) {
	// Center
	int lastAvailableIdx = centerIdx;
	if (centerExists) {
		vertices[centerIdx].pos = glm::vec3(x, y + coneHeight, z);
		lastAvailableIdx++;
	}
    // Perimeter
    for (int i = 0; i < nSlices+1; i++) {// add one more slice for initial vertex replication
        float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;
        glm::vec4 v = glm::vec4(x + r * cos(alpha), 
                                y,
                                z + r * sin(alpha), 
                                1.0);
        v = rotMat * v;
        vertices[lastAvailableIdx+i].pos = glm::vec3(v);
    }
};

void addCircleVerticesNorm(std::vector<Vertex> &vertices, const float r, const int nSlices, const int centerIdx, bool isTop, const glm::mat4 rotMat) {
	float default_alpha = 0;
	glm::vec3 dalpha = glm::vec3(-r * sin(default_alpha), 0, r * cos(default_alpha));
	glm::vec3 r_dir = glm::vec3(  r * cos(default_alpha), 0, r * sin(default_alpha));
	glm::vec3 norm = isTop 
					? glm::cross(dalpha, r_dir)
					: glm::cross(r_dir, dalpha);
	norm = glm::normalize(rotMat * glm::vec4(norm, 0.0));
	
	// Center
	int lastAvailableIdx = centerIdx;
    // Perimeter
    for (int i = 0; i < nSlices+1; i++) { // +1 for center
		vertices[lastAvailableIdx+i].norm = norm; // same norm for all vertices on the surface of a circle 
    }
};

void addCircleVerticesUV(std::vector<Vertex> &vertices, const float texture_center_u, const float texture_center_v, const float texture_r, const int nSlices, const int centerIdx) {
	// Center
	int lastAvailableIdx = centerIdx;
	vertices[centerIdx].UV = glm::vec2(texture_center_u, texture_center_v);
	lastAvailableIdx++;
    // Perimeter
    for (int i = 0; i < nSlices+1; i++) { // +1 for replicated point
		float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;
		vertices[lastAvailableIdx+i].UV = glm::vec2(texture_center_u + texture_r * cos(alpha),
													texture_center_v + texture_r * sin(alpha)); 
    }
};

void addCircleIndices(std::vector<uint32_t> &indices, const int nSlices, const int centerIdx, const int assignedTriangles) {
	for (int i = 0; i < nSlices; i++) {
        indices[(assignedTriangles + i)*3 + 0] = centerIdx;
        indices[(assignedTriangles + i)*3 + 1] = (i+1) + centerIdx;
        indices[(assignedTriangles + i)*3 + 2] = (i+1) % (nSlices+1) + 1 + centerIdx; // nSlices+1 mod for replicated final vertex

        printTriangle(assignedTriangles + i, 
                    indices[(assignedTriangles + i)*3 + 0], 
                    indices[(assignedTriangles + i)*3 + 1], 
                    indices[(assignedTriangles + i)*3 + 2]);
    }
};

void addCylinderSidePos(std::vector<Vertex> &vertices, const int nSlices,  const float r, const int assignedVertices, const int circleIdx) {

	for (int i = 0; i < nSlices+1; i++) { // add new circles in previous positions (+1 for replicated vertex)
        vertices[assignedVertices + i].pos  = vertices[circleIdx + i].pos;
		printf("[POS] assignedVertices + i: %d,\t circleIdx + i: %d\n", assignedVertices + i, circleIdx + i);
    }
};

void addCylinderSideNorm(std::vector<Vertex> &vertices, const int nSlices,  const float r, const int circleStartIdx, const glm::mat4 rotMat) {
	for (int i = 0; i < nSlices+1; i++) {
		float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;

		glm::vec4 r_dir = glm::vec4(r * cos(alpha), 0, r * sin(alpha), 0.0);
		r_dir = rotMat * r_dir;
        vertices[circleStartIdx + i].norm = glm::normalize(glm::vec3(r_dir));
		// printf("[NORM] circleStartIdx + i: %d\n", circleStartIdx + i);
    }
};


void addCylinderSideUV(std::vector<Vertex> &vertices, const float texture_u_start, const float texture_u_end, const float texture_v, const int nSlices, const int centerIdx) {
	// Center
	int lastAvailableIdx = centerIdx;
	float length = texture_u_end - texture_u_start;
	float slice_length = length / nSlices;
    // Perimeter
    for (int i = 0; i < nSlices+1; i++) { // +1 for replicated point
		vertices[lastAvailableIdx+i].UV = glm::vec2(texture_u_end - slice_length*i,
													texture_v); 
		printf("[UV] lastAvailableIdx+i: %d\ttexture_u_start + slice_length*i: %.3f,\ttexture_v: %.3f\n", lastAvailableIdx+i, texture_u_start + slice_length*i, texture_v);
    }
};



void addCylinderSideIndices(std::vector<uint32_t> &indices, const int nSlices, const int assignedTriangles, const int topCircleIdx, const int botCircleIdx) {
    std::cout << "\nDrawing lateral faces (top-right to bottom-left triangles)...\n";
	
    for (int i = 0; i < nSlices; i++) {
        indices[(assignedTriangles + 2*i)*3 + 0] = i + topCircleIdx;// + topCircleIdx;  
        indices[(assignedTriangles + 2*i)*3 + 1] = (i + 1) % (nSlices+1) + topCircleIdx;// + topCircleIdx;
        indices[(assignedTriangles + 2*i)*3 + 2] = (i + 1) % (nSlices+1) + botCircleIdx;// + botCircleIdx;
        printTriangle(assignedTriangles + 2*i, 
                        indices[(assignedTriangles + 2*i)*3 + 0], 
                        indices[(assignedTriangles + 2*i)*3 + 1], 
                        indices[(assignedTriangles + 2*i)*3 + 2]);

        indices[(assignedTriangles + 2*i + 1)*3 + 0] = i + topCircleIdx;// + topCircleIdx;
        indices[(assignedTriangles + 2*i + 1)*3 + 1] = i + botCircleIdx; // + botCircleIdx;
        indices[(assignedTriangles + 2*i + 1)*3 + 2] = (i + 1) % (nSlices+1) + botCircleIdx;// + botCircleIdx;
        printTriangle(assignedTriangles + 2*i + 1, 
                        indices[(assignedTriangles + 2*i + 1)*3 + 0], 
                        indices[(assignedTriangles + 2*i + 1)*3 + 1], 
                        indices[(assignedTriangles + 2*i + 1)*3 + 2]);

    }
};

void makeCylinder(const float cX, const float cY, const float cZ, const float r, const float height, const int nSlices) {

	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
    M2_vertices.resize(1 + 4 * (nSlices+1) + 1); // +1 top center + 4 x (nSlices+1) perimeter with replication + 1 bottom center
    M2_indices.resize(3 * (4*nSlices)); // n for each circle (x2), 2*n vertical rectangles

    // Vertices definitions
    int assignedTriangles = 0;
	int assignedVertices = 0;
    int centerIdx = 0;
    int coneHeight = 0;

	// top circle
	bool centerExists = true;
	bool isTop = true;
	float texture_center_u, texture_center_v;
	float texture_r = texture_unit;
	texture_center_u = texture_unit * 5;
	texture_center_v = texture_unit * 1;
    addCircleVerticesPos(M2_vertices, cX, cY+height, cZ, coneHeight, r, I, nSlices, assignedVertices, centerExists);
	addCircleVerticesNorm(M2_vertices, r, nSlices, assignedVertices, isTop,I);
	addCircleVerticesUV(M2_vertices, texture_center_u, texture_center_v, texture_r, nSlices, assignedVertices); 
    addCircleIndices(M2_indices, nSlices, assignedVertices, assignedTriangles);
    assignedTriangles += nSlices;  
	assignedVertices += nSlices+2;  // +2 to consider the first center point and replicated point
    centerIdx = nSlices+2;
    std::cout << std::endl << "The new triangle offset is: " << assignedTriangles << std::endl;

	// bottom circle
	isTop = false;
	texture_center_u = texture_unit * 7;
	texture_center_v = texture_unit * 1;
    addCircleVerticesPos(M2_vertices, cX, cY-height, cZ, -coneHeight, r, I, nSlices, assignedVertices, centerExists);
	addCircleVerticesNorm(M2_vertices, r, nSlices, assignedVertices, isTop, I);
	addCircleVerticesUV(M2_vertices, texture_center_u, texture_center_v, texture_r, nSlices, assignedVertices);
    addCircleIndices(M2_indices, nSlices, assignedVertices, assignedTriangles);
	assignedTriangles += nSlices;
	assignedVertices += nSlices+2;
    std::cout << std::endl << "The new triangle offset is: " << assignedTriangles << std::endl;
	


	int oldTopCircleIdx = assignedVertices - 2*(nSlices + 2) + 1; // ignore the first vertex which is a center
	int oldBotCircleIdx = assignedVertices -   (nSlices + 2) + 1;
	int newTopCircleIdx = assignedVertices;
	int newBotCircleIdx = assignedVertices + (nSlices+1);
	float texture_u_start = texture_unit * 4;
	float texture_u_end = texture_unit * 8;
	float texture_v_start = texture_unit * 2;
	float texture_v_end = texture_unit * 4;
	addCylinderSidePos(M2_vertices, nSlices, r, newTopCircleIdx, oldTopCircleIdx);
	addCylinderSidePos(M2_vertices, nSlices, r, newBotCircleIdx, oldBotCircleIdx);
	addCylinderSideNorm(M2_vertices, nSlices, r, newTopCircleIdx, I);
	addCylinderSideNorm(M2_vertices, nSlices, r, newBotCircleIdx, I);
	addCylinderSideUV(M2_vertices, texture_u_start, texture_u_end, texture_v_start, nSlices, newTopCircleIdx);
	addCylinderSideUV(M2_vertices, texture_u_start, texture_u_end, texture_v_end, nSlices, newBotCircleIdx);
	addCylinderSideIndices(M2_indices, nSlices, assignedTriangles, newTopCircleIdx, newBotCircleIdx);
    assignedTriangles += nSlices*2;
	assignedVertices += (nSlices+1)*2;
    std::cout << std::endl << "The new triangle offset is: " << assignedTriangles << std::endl;
}

void makeModels() {
	makeCube();

	float cX = 0.0f;
	float cY = 0.0f;
	float cZ = -1.0f;
	float radius = 1.0;
	float cylinderHeight = 2.0;
	int resolution = 1 << 4;
	makeCylinder(cX, cY, cZ, radius, cylinderHeight, resolution);
	
}