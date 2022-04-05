// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
//// M1 : Cube
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








//// M2 : Cylinder
// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)
int nSlices = 32*2;
float radius = 1.0;
float height = 1.0;
int cX = 0;
int cY = 0;
int cZ = 0;
M2_vertices.resize(3 * 2*(nSlices+1)); // n+1 for eachh cicle and 2 triangles for each slice
M2_indices.resize(3 * (4*nSlices)); // 2*n for circles, 2*n for vertical rectangles

auto circleVertices = [&] (float x,  float y, float z, float h, float r, int nSlices, int centerIdx) {
	// Center
    M2_vertices[centerIdx*3 + 0]  =  x;
    M2_vertices[centerIdx*3 + 1]  =  y + h;
    M2_vertices[centerIdx*3 + 2]  =  z;

    // Perimeter
    for (int i = 0; i < nSlices; i++) {
        float alpha = (float) (i % nSlices) / nSlices * 2.0 * M_PI;
        M2_vertices[(i+1+centerIdx)*3 + 0] = x + r * cos(alpha);
        M2_vertices[(i+1+centerIdx)*3 + 1] = y + h;
        M2_vertices[(i+1+centerIdx)*3 + 2] = z + r * sin(alpha);
    }
};

auto circleIndices = [&] (int nSlices, int centerIdx, int triangleIdxOffset) {
	for (int i = 0; i < nSlices; i++) {
        M2_indices[(i+triangleIdxOffset)*3 + 0] = centerIdx;
        M2_indices[(i+triangleIdxOffset)*3 + 1] = (i+1) + centerIdx;
        M2_indices[(i+triangleIdxOffset)*3 + 2] = (i+1) % nSlices + 1 + centerIdx;
        std::cout << "Triangle: " << i+triangleIdxOffset  << "\tVertex1: " << M2_indices[(i+triangleIdxOffset)*3 + 0] << "\tVertex2: " << M2_indices[(i+triangleIdxOffset)*3 + 1] << "\tVertex3: " << M2_indices[(i+triangleIdxOffset)*3 + 2] << std::endl;
    }
};

// Vertices definitions
int triangleIdxOffset = 0;
int centerIdx = 0;
circleVertices(cX, cY, cZ, height, radius, nSlices, centerIdx);
circleIndices(nSlices, centerIdx, triangleIdxOffset);

triangleIdxOffset += nSlices;   // how many triangles assigned so far
centerIdx = nSlices+1;          // consider the center point too
std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;
circleVertices(cX, cY, cZ, -height, radius, nSlices, centerIdx);
circleIndices(nSlices, centerIdx, triangleIdxOffset);

triangleIdxOffset += nSlices;
std::cout << std::endl << "The new offset is: " << triangleIdxOffset << std::endl;
for (int i = 0; i < nSlices; i++) { // WARNING: this may not cover an ODD number of slices

    M2_indices[(triangleIdxOffset+i)*3 + 0] = i + 1; //skip the center
    M2_indices[(triangleIdxOffset+i)*3 + 1] = (i + 1) % nSlices + 1;
    M2_indices[(triangleIdxOffset+i)*3 + 2] = (i + 1) + (nSlices + 1);
    std::cout << "Triangle: " << i+triangleIdxOffset  << "\tVertex1: " << M2_indices[(triangleIdxOffset+i)*3 + 0] << "\tVertex2: " << M2_indices[(triangleIdxOffset+i)*3 + 1] << "\tVertex3: " << M2_indices[(triangleIdxOffset+i)*3 + 2] << std::endl;

    triangleIdxOffset +=1;

    M2_indices[(triangleIdxOffset+i)*3 + 0] = (i + 1) % nSlices + 1;
    M2_indices[(triangleIdxOffset+i)*3 + 1] = (i + 1) + (nSlices + 1);
    M2_indices[(triangleIdxOffset+i)*3 + 2] = (i + 1) % nSlices + (nSlices + 1) + 1;
    std::cout << "Triangle: " << i+triangleIdxOffset  << "\tVertex1: " << M2_indices[(triangleIdxOffset+i)*3 + 0] << "\tVertex2: " << M2_indices[(triangleIdxOffset+i)*3 + 1] << "\tVertex3: " << M2_indices[(triangleIdxOffset+i)*3 + 2] << std::endl;

}















//// M3 : Sphere
// Replace the code below, that creates a simple triangle, with the one to create a sphere.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)
M3_vertices.resize(9);

// Vertices definitions
M3_vertices[0]  =  0.0;
M3_vertices[1]  =  1.0;
M3_vertices[2]  = -1.2;
M3_vertices[3]  = -0.866;
M3_vertices[4]  = -0.5;
M3_vertices[5]  = -1.2;
M3_vertices[6]  =  0.866;
M3_vertices[7]  = -0.5;
M3_vertices[8]  = -1.2;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M3_indices.resize(3);

// indices definitions
M3_indices[0] = 0;
M3_indices[1] = 1;
M3_indices[2] = 2;









//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.
M4_vertices.resize(3 * 6);

// Vertices definitions
M4_vertices[0]  =  0.0;
M4_vertices[1]  =  1.414;
M4_vertices[2]  = -1.0;
M4_vertices[3]  =  0.0;
M4_vertices[4]  = -1.414;
M4_vertices[5]  = -1.0;
M4_vertices[6]  = -1.0;
M4_vertices[7]  =  0.0;
M4_vertices[8]  = -2.0;
M4_vertices[9]  = -1.0;
M4_vertices[10] =  0.0;
M4_vertices[11] =  0.0;
M4_vertices[12] =  1.0;
M4_vertices[13] =  0.0;
M4_vertices[14] =  0.0;
M4_vertices[15] =  1.0;
M4_vertices[16] =  0.0;
M4_vertices[17] = -2.0;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M4_indices.resize(3 * 8);

// indices definitions
M4_indices[0]  = 0;
M4_indices[1]  = 2;
M4_indices[2]  = 3;
M4_indices[3]  = 1;
M4_indices[4]  = 3;
M4_indices[5]  = 2;
M4_indices[6]  = 0;
M4_indices[7]  = 3;
M4_indices[8]  = 4;
M4_indices[9]  = 1;
M4_indices[10] = 4;
M4_indices[11] = 3;
M4_indices[12] = 0;
M4_indices[13] = 4;
M4_indices[14] = 5;
M4_indices[15] = 1;
M4_indices[16] = 5;
M4_indices[17] = 4;
M4_indices[18] = 0;
M4_indices[19] = 5;
M4_indices[20] = 2;
M4_indices[21] = 1;
M4_indices[22] = 2;
M4_indices[23] = 5;
}