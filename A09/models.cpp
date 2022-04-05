glm::vec3 AXIS_X = glm::vec3(1,0,0);
glm::vec3 AXIS_Y = glm::vec3(0,1,0);
glm::vec3 AXIS_Z = glm::vec3(0,0,1);
glm::mat4 I = glm::mat4(1.0f);

void makeCube() {
    // Replace the code below, that creates a simple square, with the one to create a cube.

    // Resizes the vertices array. Repalce the values with the correct number of
    // vertices components (3 * number of vertices) [3 values vertex: x, y ,z]
    int nVertices;
    int nTriangles;

    nVertices = 8;
    M1_vertices.resize(3 * nVertices);

    // first vertex of M1
    M1_vertices[0] = -1.0;
    M1_vertices[1] = -1.0;
    M1_vertices[2] = -1.0;

    // second vertex of M1
    M1_vertices[3] =  1.0;
    M1_vertices[4] = -1.0;
    M1_vertices[5] = -1.0;

    // third vertex of M1
    M1_vertices[6] =  1.0;
    M1_vertices[7] =  1.0;
    M1_vertices[8] = -1.0;

    // fourth vertex of M1
    M1_vertices[9] =  -1.0;
    M1_vertices[10] =  1.0;
    M1_vertices[11] = -1.0;

    // 5
    M1_vertices[12] = -1.0;
    M1_vertices[13] =  1.0;
    M1_vertices[14] =  1.0;

    // 6
    M1_vertices[15] =  1.0;
    M1_vertices[16] =  1.0;
    M1_vertices[17] =  1.0;

    // 7
    M1_vertices[18] =  1.0;
    M1_vertices[19] = -1.0;
    M1_vertices[20] =  1.0;

    // 8
    M1_vertices[21] = -1.0;
    M1_vertices[22] = -1.0;
    M1_vertices[23] =  1.0;


    // Resizes the indices array. Repalce the values with the correct number of
    // indices (3 * number of triangles)
    nTriangles = 6 * 2; // 6 faces, 2 triangles each
    M1_indices.resize(3 * nTriangles);

    // first triangle
    M1_indices[0] = 0;
    M1_indices[1] = 1;
    M1_indices[2] = 2;

    // second triangle
    M1_indices[3] = 2;
    M1_indices[4] = 3;
    M1_indices[5] = 0;

    // 3
    M1_indices[6] = 2;
    M1_indices[7] = 3;
    M1_indices[8] = 4;

    // 4
    M1_indices[9] =  2;
    M1_indices[10] = 4;
    M1_indices[11] = 5;

    // 5
    M1_indices[12] = 1;
    M1_indices[13] = 2;
    M1_indices[14] = 5;

    // 6
    M1_indices[15] = 1;
    M1_indices[16] = 5;
    M1_indices[17] = 6;

    // 7
    M1_indices[18] = 1;
    M1_indices[19] = 6;
    M1_indices[20] = 7;

    // 8
    M1_indices[21] = 0;
    M1_indices[22] = 1;
    M1_indices[23] = 7;

    // 9
    M1_indices[24] = 0;
    M1_indices[25] = 3;
    M1_indices[26] = 4;

    // 10
    M1_indices[27] = 0;
    M1_indices[28] = 4;
    M1_indices[29] = 7;

    // 11
    M1_indices[30] = 4;
    M1_indices[31] = 5;
    M1_indices[32] = 7;

    // 12
    M1_indices[33] = 5;
    M1_indices[34] = 6;
    M1_indices[35] = 7;
}

void printTriangle(const int triangleID, const int vertex1, const int vertex2, const int vertex3) {
    std::cout << "Triangle: " << triangleID;
    std::cout << "\t{ "  << vertex1;
    std::cout << "\t" << vertex2;
    std::cout << "\t" << vertex3;
    std::cout << "}" << std::endl;
};

std::vector<float> coneVertices(std::vector<float> vertices, const float x,  const float y, const float z, const float coneHeight, const float r, const glm::mat4 rotMat, const int nSlices, const int centerIdx) {
	// Center
    vertices[centerIdx*3 + 0]  =  x;
    vertices[centerIdx*3 + 1]  =  y + coneHeight;
    vertices[centerIdx*3 + 2]  =  z;

    // Perimeter
    for (int i = 0; i < nSlices; i++) {
        float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;
        glm::vec4 v = glm::vec4(x + r * cos(alpha), 
                                y,
                                z + r * sin(alpha), 
                                1.0);
        v = rotMat * v;
        vertices[(i+1+centerIdx)*3 + 0] = v.x;
        vertices[(i+1+centerIdx)*3 + 1] = v.y;
        vertices[(i+1+centerIdx)*3 + 2] = v.z;
    }

    return vertices;
};

std::vector<uint32_t> coneIndices(std::vector<uint32_t> indices, const int nSlices, const int centerIdx, const int triangleIdxOffset) {
	for (int i = 0; i < nSlices; i++) {
        indices[(i+triangleIdxOffset)*3 + 0] = centerIdx;
        indices[(i+triangleIdxOffset)*3 + 1] = (i+1) + centerIdx;
        indices[(i+triangleIdxOffset)*3 + 2] = (i+1) % nSlices + 1 + centerIdx;

        printTriangle(i+triangleIdxOffset, 
                    indices[(i+triangleIdxOffset)*3 + 0], 
                    indices[(i+triangleIdxOffset)*3 + 1], 
                    indices[(i+triangleIdxOffset)*3 + 2]);

    }
    return indices;
};

std::vector<uint32_t> drawLateralFaces(std::vector<uint32_t> indices, int nSlices, int triangleIdxOffset, int prevCenterIdx) {
    std::cout << "\nDrawing lateral faces ...\n";
    for (int i = 0; i < nSlices; i++) {
        indices[(triangleIdxOffset+i)*3 + 0] = i + 1 + prevCenterIdx; //i+1 to skip the center
        indices[(triangleIdxOffset+i)*3 + 1] = (i + 1) % nSlices + 1 + prevCenterIdx;
        indices[(triangleIdxOffset+i)*3 + 2] = (i + 1) % nSlices + 1 + (nSlices + 1) + prevCenterIdx;//(i + 1) + (nSlices + 1) + prevCenterIdx;
        printTriangle(i+triangleIdxOffset, 
                        indices[(i+triangleIdxOffset)*3 + 0], 
                        indices[(i+triangleIdxOffset)*3 + 1], 
                        indices[(i+triangleIdxOffset)*3 + 2]);

        triangleIdxOffset +=1;

        indices[(triangleIdxOffset+i)*3 + 0] = (i + 1) + prevCenterIdx;
        indices[(triangleIdxOffset+i)*3 + 1] = (i + 1) + (nSlices + 1) + prevCenterIdx;
        indices[(triangleIdxOffset+i)*3 + 2] = (i + 1) % nSlices + 1 + (nSlices + 1) + prevCenterIdx;
        printTriangle(i+triangleIdxOffset, 
                        indices[(i+triangleIdxOffset)*3 + 0], 
                        indices[(i+triangleIdxOffset)*3 + 1], 
                        indices[(i+triangleIdxOffset)*3 + 2]);

    }
    return indices;
};

void makeCylinder(const float cX, const float cY, const float cZ, const int nSlices) {
    // Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

    // Resizes the vertices array. Repalce the values with the correct number of
    // vertices components (3 * number of vertices)
    float radius = 1.0;
    float cylinderHeight = 1.0;
    M2_vertices.resize(3 * 2*(nSlices+1)); // n+1 for each cicle (x2)
    M2_indices.resize(3 * (4*nSlices)); // n for each circle (x2), 2*n vertical rectangles


    // Vertices definitions
    int triangleIdxOffset = 0;
    int centerIdx = 0;
    int coneHeight = 0;

    M2_vertices = coneVertices(M2_vertices, cX, cY+cylinderHeight, cZ, coneHeight, radius, I, nSlices, centerIdx);
    M2_indices = coneIndices(M2_indices, nSlices, centerIdx, triangleIdxOffset);
    triangleIdxOffset += nSlices;   // how many triangles assigned so far
    centerIdx = nSlices+1;          // consider the first center point too
    std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;

    M2_vertices = coneVertices(M2_vertices, cX, cY-cylinderHeight, cZ, -coneHeight, radius, I, nSlices, centerIdx);
    M2_indices = coneIndices(M2_indices, nSlices, centerIdx, triangleIdxOffset);
    triangleIdxOffset += nSlices;
    std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;

    int prevCenterIdx = centerIdx-nSlices-1;
    M2_indices = drawLateralFaces(M2_indices, nSlices, triangleIdxOffset, prevCenterIdx);
    triangleIdxOffset += nSlices*2;
    std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;
}

void makeSphere(const float cX, const float cY, const float cZ, const int nSlices, const int nStripes) {
    // Replace the code below, that creates a simple triangle, with the one to create a sphere.

    // Resizes the vertices array. Repalce the values with the correct number of
    // vertices components (3 * number of vertices)

    int nCircles = nStripes-1;
    float sphereRadius = 1.0;
    M3_vertices.resize(3 * nCircles*(nSlices+1));
    M3_indices.resize(3  * nCircles*(2*nSlices));


    
    // Vertices and indices definitions
    int triangleIdxOffset = 0;
    float stripeHeight = 2*sphereRadius / nStripes;
    float coneBaseY = sphereRadius - stripeHeight;

    std::cout << "==================================== SPHERE(" << nStripes << ") ===================================="  << std::endl;
    std::cout << "nStripes = "  << nStripes << std::endl;
    std::cout << "coneBaseY = "  << coneBaseY << std::endl;
    std::cout << "stripeHeight = " << stripeHeight << std::endl << std::endl;

    // inner circles
    float coneHeight;
    int centerIdx = 0;
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
        M3_vertices = coneVertices(M3_vertices, cX, cY+coneBaseY, cZ, coneHeight, circleRadius, I, nSlices, centerIdx);
        if (i==0 || i == nCircles-1) { // do not add triangles to inner circles
            M3_indices = coneIndices(M3_indices, nSlices, centerIdx, triangleIdxOffset);
            triangleIdxOffset += nSlices;
        }
        std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;

        if (i>0) {
            int prevCenterIdx = centerIdx - nSlices - 1;
            std::cout << std::endl << "prevCenterIdx: " << prevCenterIdx << std::endl;
            M3_indices = drawLateralFaces(M3_indices, nSlices, triangleIdxOffset, prevCenterIdx);
            triangleIdxOffset += nSlices*2;
            std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;
        }
        centerIdx += nSlices+1;
    }
}

void makeSpring(const float cX, const float cY, const float cZ, const int nRevolutions, const float height, const float width, const int nSlices, const int nStripes, const float radius) {
    int nCircles = nStripes + 1;
    float revolutionRadius = width/2;
    M4_vertices.resize(3 * nCircles*(nSlices+1));
    M4_indices.resize(3  * nCircles*(2*nSlices));

    
    // Vertices and indices definitions
    int triangleIdxOffset = 0;
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
    int centerIdx = 0;
    for(int i=0; i < nCircles; i++) {
        // spring equations
        float beta = (float) i * nRevolutions / nStripes * 2.0 * M_PI;
        float circleCx = cX + revolutionRadius * cos(beta);
        float circleCy = cY + stripeHeight * (nStripes/2 - i);
        float circleCz = cZ + revolutionRadius * sin(beta);
        glm::vec3 circleCenter = glm::vec3(circleCx, circleCy, circleCz);
        glm::mat4 T = glm::translate(I, circleCenter);
        glm::mat4 Ry = glm::rotate(I, -beta, AXIS_Y);
        glm::mat4 Rx = glm::rotate(I, glm::radians(90.0f), AXIS_X); // rotate around z of 90°
        glm::mat4 refPos = T * Ry;
        glm::mat4 rotateCircle = refPos * Rx * glm::inverse(refPos);
        std::cout << "\nbeta = " << beta / 2 / M_PI * 360 << std::endl;
        std::cout << "circleCx = " << circleCx << std::endl;
        std::cout << "circleCy = " << circleCy << std::endl;
        std::cout << "circleCz = " << circleCz << std::endl;

        M4_vertices = coneVertices(M4_vertices, circleCx, circleCy, circleCz, coneHeight, radius, rotateCircle, nSlices, centerIdx);

        if (i>0) {
            int prevCenterIdx = centerIdx - nSlices - 1;
            std::cout << std::endl << "prevCenterIdx: " << prevCenterIdx << std::endl;
            M4_indices = drawLateralFaces(M4_indices, nSlices, triangleIdxOffset, prevCenterIdx);
            triangleIdxOffset += nSlices*2;
            std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;
        }
        centerIdx += nSlices+1;
    }
    
    
}

// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
//// M1 : Cube
makeCube();


//// M2 : Cylinder
float cX = 0.0f;
float cY = 0.0f;
float cZ = -1.0f;
int resolution;
resolution = 64;
makeCylinder(cX, cY, cZ, resolution);


//// M3 : Sphere
int hResolution = 64;
int vResolution = 64;
makeSphere(cX, cY, cZ, hResolution, vResolution);



//// M4 : Spring
hResolution = 1 << 6;
vResolution = 1 << 8;
int nRevolutions = 3;
float springWidth = 2.0f;
float springHeight = springWidth / 2;
float springRadius = springWidth/20;
makeSpring(cX, cY, cZ, 
            nRevolutions, 
            springHeight, 
            springWidth, 
            hResolution,  // slices
            vResolution,  // stripes
            springRadius);

}