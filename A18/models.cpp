glm::vec3 AXIS_X = glm::vec3(1,0,0);
glm::vec3 AXIS_Y = glm::vec3(0,1,0);
glm::vec3 AXIS_Z = glm::vec3(0,0,1);
glm::mat4 I = glm::mat4(1.0f);

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;

void makeCube() {
	//// M1 : Cube
	// Replace the code below, that creates a simple square, with the one to create a cube.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	int n_vertices = 8;
	M1_vertices.resize(3*n_vertices);


	M1_vertices[0].pos  = glm::vec3(-1.0,-1.0,-1.0);
	M1_vertices[0].norm = glm::vec3(-1.0,0.0,0.0);
	M1_vertices[1].pos  = M1_vertices[0].pos;
	M1_vertices[1].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[2].pos  = M1_vertices[0].pos;
	M1_vertices[2].norm = glm::vec3(0.0,0.0,-1.0);

	M1_vertices[3].pos  = glm::vec3(1.0,-1.0,-1.0);
	M1_vertices[3].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[4].pos  = M1_vertices[3].pos;
	M1_vertices[4].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[5].pos  = M1_vertices[3].pos;
	M1_vertices[5].norm = glm::vec3(0.0,0.0,-1.0);

	M1_vertices[6].pos  = glm::vec3(1.0,1.0,-1.0);
	M1_vertices[6].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[7].pos  = M1_vertices[6].pos;
	M1_vertices[7].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[8].pos  = M1_vertices[6].pos;
	M1_vertices[8].norm = glm::vec3(0.0,0.0,-1.0);

	M1_vertices[9].pos  =  glm::vec3(-1.0,1.0,-1.0);
	M1_vertices[9].norm =  glm::vec3(-1.0,0.0,0.0);
	M1_vertices[10].pos  = M1_vertices[9].pos;
	M1_vertices[10].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[11].pos  = M1_vertices[9].pos;
	M1_vertices[11].norm = glm::vec3(0.0,0.0,-1.0);

	M1_vertices[12].pos  = glm::vec3(-1.0,1.0,1.0);
	M1_vertices[12].norm = glm::vec3(-1.0,0.0,0.0);
	M1_vertices[13].pos  = M1_vertices[12].pos;
	M1_vertices[13].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[14].pos  = M1_vertices[12].pos;
	M1_vertices[14].norm = glm::vec3(0.0,0.0,1.0);

	M1_vertices[15].pos  = glm::vec3(1.0,1.0,1.0);
	M1_vertices[15].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[16].pos  = M1_vertices[15].pos;
	M1_vertices[16].norm = glm::vec3(0.0,1.0,0.0);
	M1_vertices[17].pos  = M1_vertices[15].pos;
	M1_vertices[17].norm = glm::vec3(0.0,0.0,1.0);

	M1_vertices[18].pos  = glm::vec3(1.0,-1.0,1.0);
	M1_vertices[18].norm = glm::vec3(1.0,0.0,0.0);
	M1_vertices[19].pos  = M1_vertices[18].pos;
	M1_vertices[19].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[20].pos  = M1_vertices[18].pos;
	M1_vertices[20].norm = glm::vec3(0.0,0.0,1.0);

	M1_vertices[21].pos  = glm::vec3(-1.0,-1.0,1.0);
	M1_vertices[21].norm = glm::vec3(-1.0,0.0,0.0);
	M1_vertices[22].pos  = M1_vertices[21].pos;
	M1_vertices[22].norm = glm::vec3(0.0,-1.0,0.0);
	M1_vertices[23].pos  = M1_vertices[21].pos;
	M1_vertices[23].norm = glm::vec3(0.0,0.0,1.0);

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
    for (int i = 0; i < nSlices; i++) {
        float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;
        glm::vec4 v = glm::vec4(x + r * cos(alpha), 
                                y,
                                z + r * sin(alpha), 
                                1.0);
        v = rotMat * v;
        vertices[lastAvailableIdx+i].pos = glm::vec3(v);
    }
};

void addCircleVerticesNorm(std::vector<Vertex> &vertices, const float r, const int nSlices, const int centerIdx, bool centerExists, bool isTop, const glm::mat4 rotMat) {
	float default_alpha = 0;
	glm::vec3 dalpha = glm::vec3(-r * sin(default_alpha), 0, r * cos(default_alpha));
	glm::vec3 r_dir = glm::vec3(  r * cos(default_alpha), 0, r * sin(default_alpha));
	glm::vec3 norm = isTop 
					? glm::normalize(glm::cross(dalpha, r_dir))
					: glm::normalize(glm::cross(r_dir, dalpha));
	
	// Center
	int lastAvailableIdx = centerIdx;
	if (centerExists)
		lastAvailableIdx++;
    // Perimeter
    for (int i = 0; i < nSlices; i++) {
		vertices[lastAvailableIdx+i].norm = norm; // same norm for all vertices on the surface of a circle 
    }
};

void addSphereVerticesNorm(std::vector<Vertex> &vertices, const float y, const float r, const int nSlices, const int centerIdx, const bool centerExists) {
	
	// Center
	int lastAvailableIdx = centerIdx;
	if (centerExists) {
		vertices[lastAvailableIdx].norm = glm::normalize(glm::vec3(0,y,0));
		lastAvailableIdx++;
	}

    // Perimeter
    for (int i = 0; i < nSlices; i++) {
		float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;
        glm::vec3 r_dir = glm::vec3(r * cos(alpha), 
                                y,
                                r * sin(alpha));
		glm::vec3 norm = glm::normalize(r_dir);
		vertices[lastAvailableIdx+i].norm = norm;
	}
};

void addCircleIndices(std::vector<uint32_t> &indices, const int nSlices, const int centerIdx, const int assignedTriangles) {
	for (int i = 0; i < nSlices; i++) {
        indices[(assignedTriangles + i)*3 + 0] = centerIdx;
        indices[(assignedTriangles + i)*3 + 1] = (i+1) + centerIdx;
        indices[(assignedTriangles + i)*3 + 2] = (i+1) % nSlices + 1 + centerIdx;

        printTriangle(assignedTriangles + i, 
                    indices[(assignedTriangles + i)*3 + 0], 
                    indices[(assignedTriangles + i)*3 + 1], 
                    indices[(assignedTriangles + i)*3 + 2]);
    }
};

void addCylinderSidePos(std::vector<Vertex> &vertices, const int nSlices,  const float r, const int assignedVertices) {
	int topCircleIdx = assignedVertices - 2*(nSlices + 1) + 1; // ignore the first vertex which is a center
	int botCircleIdx = assignedVertices -   (nSlices + 1) + 1;

	for (int i = 0; i < nSlices; i++) { // add new circles in previous positions
        vertices[assignedVertices + i].pos  = vertices[topCircleIdx + i].pos;
        vertices[assignedVertices + nSlices + i].pos  = vertices[botCircleIdx + i].pos;
    }
};

void addCylinderSideNorm(std::vector<Vertex> &vertices, const int nSlices,  const float r, const int circleStartIdx, const glm::mat4 rotMat) {
	for (int i = 0; i < nSlices; i++) {
		float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;
		
		glm::vec4 r_dir = glm::vec4(r * cos(alpha), 0, r * sin(alpha), 0.0);
		r_dir = rotMat * r_dir;
        vertices[circleStartIdx + i].norm = glm::normalize(glm::vec3(r_dir));
    }
};

void addCylinderSideIndices(std::vector<uint32_t> &indices, const int nSlices, const int assignedTriangles, const int topCircleIdx, const int botCircleIdx) {
    std::cout << "\nDrawing lateral faces (top-right to bottom-left triangles)...\n";
	
    for (int i = 0; i < nSlices; i++) {
        indices[(assignedTriangles + 2*i)*3 + 0] = i + topCircleIdx;// + topCircleIdx;  
        indices[(assignedTriangles + 2*i)*3 + 1] = (i + 1) % nSlices + topCircleIdx;// + topCircleIdx;
        indices[(assignedTriangles + 2*i)*3 + 2] = (i + 1) % nSlices + botCircleIdx;// + botCircleIdx;
        printTriangle(assignedTriangles + 2*i, 
                        indices[(assignedTriangles + 2*i)*3 + 0], 
                        indices[(assignedTriangles + 2*i)*3 + 1], 
                        indices[(assignedTriangles + 2*i)*3 + 2]);

        indices[(assignedTriangles + 2*i + 1)*3 + 0] = i + topCircleIdx;// + topCircleIdx;
        indices[(assignedTriangles + 2*i + 1)*3 + 1] = i + botCircleIdx; // + botCircleIdx;
        indices[(assignedTriangles + 2*i + 1)*3 + 2] = (i + 1) % nSlices + botCircleIdx;// + botCircleIdx;
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
    M2_vertices.resize(1 + 4 * (nSlices) + 1); // +1 top center + 4 x nSlices perimeter + 1 bottom center
    M2_indices.resize(3 * (4*nSlices)); // n for each circle (x2), 2*n vertical rectangles

    // Vertices definitions
    int assignedTriangles = 0;
	int assignedVertices = 0;
    int centerIdx = 0;
    int coneHeight = 0;

	// top circle
	bool centerExists = true;
	bool isTop = true;
    addCircleVerticesPos(M2_vertices, cX, cY+height, cZ, coneHeight, r, I, nSlices, centerIdx, centerExists);
	addCircleVerticesNorm(M2_vertices, r, nSlices, centerIdx, centerExists, isTop,I);
    addCircleIndices(M2_indices, nSlices, centerIdx, assignedTriangles);
    assignedTriangles += nSlices;  
	assignedVertices += nSlices+1;  // consider the first center point too
    centerIdx = nSlices+1;
    std::cout << std::endl << "The new offset is: " << assignedTriangles << std::endl;

	// bottom circle
	isTop = false;
    addCircleVerticesPos(M2_vertices, cX, cY-height, cZ, -coneHeight, r, I, nSlices, centerIdx, centerExists);
	addCircleVerticesNorm(M2_vertices, r, nSlices, centerIdx, centerExists, isTop, I);
    addCircleIndices(M2_indices, nSlices, centerIdx, assignedTriangles);
	assignedTriangles += nSlices;
	assignedVertices += nSlices+1;
    std::cout << std::endl << "The new offset is: " << assignedTriangles << std::endl;
	

	int topCircleIdx = assignedVertices;
	int botCircleIdx = assignedVertices + nSlices;
	addCylinderSidePos(M2_vertices, nSlices, r, assignedVertices);
	addCylinderSideNorm(M2_vertices, nSlices, r, assignedVertices, I);
	addCylinderSideNorm(M2_vertices, nSlices, r, assignedVertices + nSlices, I);
	addCylinderSideIndices(M2_indices, nSlices, assignedTriangles, topCircleIdx, botCircleIdx);
    assignedTriangles += nSlices*2;
	assignedVertices += (nSlices+1)*2;
    std::cout << std::endl << "The new offset is: " << assignedTriangles << std::endl;
}

void makeSphere(const float cX, const float cY, const float cZ, const int nSlices, const int nStripes) {
	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	int nCircles = nStripes-1;
    float sphereRadius = 1.0;
    M3_vertices.resize(3 * nCircles*(nSlices+1));
    M3_indices.resize( 3 * nCircles*(2*nSlices));

    // Vertices and indices definitions
    int assignedTriangles = 0;
    float stripeHeight = 2*sphereRadius / nStripes;
    float coneBaseY = sphereRadius - stripeHeight;

    std::cout << "==================================== SPHERE(" << nStripes << ") ===================================="  << std::endl;
    std::cout << "nStripes = "  << nStripes << std::endl;
    std::cout << "coneBaseY = "  << coneBaseY << std::endl;
    std::cout << "stripeHeight = " << stripeHeight << std::endl << std::endl;

    // inner circles
    float coneHeight;
    int assignedVertices = 0;
    for(int i=0; i < nCircles; i++) {
        if (i == 0)
            coneHeight = stripeHeight;
        else if ( i == nCircles-1)
            coneHeight = -stripeHeight;
            else
                coneHeight = 0;
        
        float coneBaseY = sphereRadius - (i+1)*stripeHeight;
        float circleRadius = sqrt(pow(sphereRadius,2) - pow(coneBaseY,2));
        std::cout << "coneBaseY = "  << coneBaseY << std::endl;
        std::cout << "circleRadius = "  << circleRadius << std::endl;

		bool centerExists = true;
        if (i==0 || i == nCircles-1) { // do not add triangles to inner circles
    		addCircleIndices(M3_indices, nSlices, assignedVertices, assignedTriangles);
            assignedTriangles += nSlices;
			centerExists = true;
        }
		addCircleVerticesPos(M3_vertices, cX, cY+coneBaseY, cZ, coneHeight, circleRadius, I, nSlices, assignedVertices, centerExists);
		addSphereVerticesNorm(M3_vertices, cY+coneBaseY, circleRadius, nSlices, assignedVertices, centerExists);
        std::cout << std::endl << "The new offset is: " << assignedTriangles << std::endl;

        if (i>0) {
            int prevCenterIdx = assignedVertices - nSlices - 1;
            std::cout << std::endl << "prevCenterIdx: " << prevCenterIdx << std::endl;
			int topCircleIdx = prevCenterIdx + 1;
			int botCircleIdx = prevCenterIdx + 1 + nSlices + 1;
			addCylinderSideIndices(M3_indices, nSlices, assignedTriangles, topCircleIdx, botCircleIdx);
            assignedTriangles += nSlices*2;
            std::cout << std::endl << "The new offset is: " << assignedTriangles << std::endl;
        }
        assignedVertices += nSlices+1;
    }

}

void makeSpring(const float cX, const float cY, const float cZ, const int nRevolutions, const float height, const float width, const int nSlices, const int nStripes, const float radius) {
    int nCircles = nStripes + 1;
    float revolutionRadius = width/2;
    M4_vertices.resize(3 * nCircles*(nSlices+1));
    M4_indices.resize(3  * nCircles*(2*nSlices));

    
    // Vertices and indices definitions
    int assignedTriangles = 0;
    float revolutionHeight = height / nRevolutions;
    float stripeHeight = height / nStripes;
    int stripesPerRevolution = nStripes / nRevolutions;

    std::cout << "==================================== Spring(" << nRevolutions << ") ===================================="  << std::endl;
    std::cout << "nStripes = "  << nStripes << std::endl;
    std::cout << "nRevolutions = " << nRevolutions << std::endl;
    std::cout << "stripesPerRevolution = " << stripesPerRevolution << std::endl;
    std::cout << "revolutionRadius = " << revolutionRadius << std::endl;
    std::cout << "radius = " << radius << std::endl;
    std::cout << "height = " << height << std::endl;
    std::cout << "width = " << width << std::endl;
    std::cout << "stripeHeight = " << stripeHeight << std::endl << std::endl;

    // inner circles
    const float coneHeight = 0.0f;
    int assignedVertices = 0;
    for(int i=0; i < nCircles; i++) {
        // spring equations
        float beta = (float) i * nRevolutions / nStripes * 2.0 * M_PI;
        float circleCx = cX + revolutionRadius * cos(beta);
        float circleCy = cY + stripeHeight * (nStripes/2 - i);
        float circleCz = cZ + revolutionRadius * sin(beta);
        glm::vec3 circleCenter = glm::vec3(circleCx, circleCy, circleCz);
        glm::mat4 T = glm::translate(I, circleCenter);
        glm::mat4 Ry = glm::rotate(I, -beta, AXIS_Y);
        glm::mat4 Rx = glm::rotate(I, glm::radians(90.0f), AXIS_X); // rotate around x of 90°
        glm::mat4 refPos = T * Ry;
        glm::mat4 rotateCircle = refPos * Rx * glm::inverse(refPos);
        std::cout << "\nbeta = " << beta / 2 / M_PI * 360 << std::endl;
        std::cout << "circleCx = " << circleCx << std::endl;
        std::cout << "circleCy = " << circleCy << std::endl;
        std::cout << "circleCz = " << circleCz << std::endl;

        // addConeVertices(M4_vertices, circleCx, circleCy, circleCz, coneHeight, radius, rotateCircle, nSlices, assignedVertices);
		bool centerExists = true;
		addCircleVerticesPos(M4_vertices, circleCx, circleCy, circleCz, coneHeight, radius, rotateCircle, nSlices, assignedVertices, centerExists);
		addCylinderSideNorm(M4_vertices, nSlices, radius, assignedVertices+1, rotateCircle); // +1 to skip center

        if (i>0) {
            int prevCenterIdx = assignedVertices - nSlices - 1;
            std::cout << std::endl << "prevCenterIdx: " << prevCenterIdx << std::endl;
            int topCircleIdx = prevCenterIdx + 1;
			int botCircleIdx = prevCenterIdx + 1 + nSlices + 1;
			addCylinderSideIndices(M4_indices, nSlices, assignedTriangles, topCircleIdx, botCircleIdx);
            assignedTriangles += nSlices*2;
            std::cout << std::endl << "The new offset is: " << assignedTriangles << std::endl;
        }
        assignedVertices += nSlices+1;
    }    
}

// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
	// M1: Cube
	makeCube();

	// M2 : Cylinder
	float cX = 0.0f;
	float cY = 0.0f;
	float cZ = -1.0f;
	float radius = 1.0;
	float cylinderHeight = 1.0;
	int resolution = 1 << 4;
	makeCylinder(cX, cY, cZ, radius, cylinderHeight, resolution);
	
	// M3 : Sphere
	int hResolution = 1 << 4;
	int vResolution = 1 << 7;
	makeSphere(cX, cY, cZ, hResolution, vResolution);

	// M4: Spring
	hResolution = 1 << 4; // slices
	vResolution = 1 << 6; // stripes
	int nRevolutions = 3;
	float springWidth = 2.0f;
	float springHeight = springWidth / 1.5;
	float springRadius = springWidth/20;
	makeSpring(cX, cY, cZ, 
				nRevolutions, 
				springHeight, 
				springWidth, 
				hResolution,  
				vResolution,  
				springRadius);
}