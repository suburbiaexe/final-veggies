#include "terraingenerator.h"

void TerrainGenerator::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    //m_param1 = param1;
    m_param1 = 100; // TODO CHANGED FROM 200
    m_param2 = param2;
    setVertexData();
}

void TerrainGenerator::generateTerrain() {
    // Task 7: create a full sphere using the makeWedge() function you
    //         implemented in Task 6
    // Note: think about how param 2 comes into play here!

//    float delta_theta = glm::radians(360.0 / m_param2);

//    for (int i=0;i<m_param2;i++) {
//        makeWedge(i*delta_theta, (i+1)*delta_theta);
//    }

    //std::vector<float> verts;
    //verts.reserve(m_resolution * m_resolution * 6);

    m_vertexData.clear();
    m_randVecLookup.clear();

    // Task 8: turn off wireframe shading
    m_wireshade = false; // STENCIL CODE
    // m_wireshade = false; // TA SOLUTION

    // Define resolution of terrain generation
    m_resolution = m_param1;

    // Generate random vector lookup table
    m_lookupSize = 1024;
    m_randVecLookup.reserve(m_lookupSize);

    QString kitten_filepath = QString("/Users/Hannah/Desktop/cs1230/final/final-veggies/resources/texture_mountain.png");

    // Task 1: Obtain image from filepath

    m_image = QImage(kitten_filepath);

    // Task 2: Format image to fit OpenGL

    m_image = m_image.convertToFormat(QImage::Format_RGBA8888).mirrored();

    // Initialize random number generator

    // Populate random vector lookup table
    for (int i = 0; i < m_lookupSize; i++)
    {
      m_randVecLookup.push_back(glm::vec2(std::rand() * 2.0 / RAND_MAX - 1.0,
                                          std::rand() * 2.0 / RAND_MAX - 1.0));
    }

    for(int x = 0; x < m_resolution; x++) {
        for(int y = 0; y < m_resolution; y++) {
            int x1 = x;
            int y1 = y;

            int x2 = x + 1;
            int y2 = y + 1;

            glm::vec3 p1 = getPosition(x1,y1);
            glm::vec3 p2 = getPosition(x2,y1);
            glm::vec3 p3 = getPosition(x2,y2);
            glm::vec3 p4 = getPosition(x1,y2);

            glm::vec3 n1 = getNormal(x1,y1);
            glm::vec3 n2 = getNormal(x2,y1);
            glm::vec3 n3 = getNormal(x2,y2);
            glm::vec3 n4 = getNormal(x1,y2);


            // get color to sample from a texture and then add that as a third vao attribute
            // add third vao in default vert
            // out vec3 texture
            // in default frag -> condition on if we do this -> add this in to the diffuse term
            // tris 1
            // x1y1z1
            // x2y1z2
            // x2y2z3
            insertVec3(m_vertexData, p1);
            insertVec3(m_vertexData, n1);
            insertVec3(m_vertexData, getColor(n1, p1));
//            insertVec3(m_vertexData, glm::vec3(1.0f));

            insertVec3(m_vertexData, p3);
            insertVec3(m_vertexData, n3);
            insertVec3(m_vertexData, getColor(n2, p2));
//            insertVec3(m_vertexData, glm::vec3(1.0f));

            insertVec3(m_vertexData, p2);
            insertVec3(m_vertexData, n2);
            insertVec3(m_vertexData, getColor(n3, p3));
//            insertVec3(m_vertexData, glm::vec3(1.0f));

            // tris 2
            // x1y1z1
            // x2y2z3
            // x1y2z4
            insertVec3(m_vertexData, p1);
            insertVec3(m_vertexData, n1);
            insertVec3(m_vertexData, getColor(n1, p1));
//            insertVec3(m_vertexData, glm::vec3(1.0f));

            insertVec3(m_vertexData, p4);
            insertVec3(m_vertexData, n4);
            insertVec3(m_vertexData, getColor(n3, p3));
//            insertVec3(m_vertexData, glm::vec3(1.0f));

            insertVec3(m_vertexData, p3);
            insertVec3(m_vertexData, n3);
            insertVec3(m_vertexData, getColor(n4, p4));
//            insertVec3(m_vertexData, glm::vec3(1.0f));
        }
    }
    //m_vertexData = verts;
}

void TerrainGenerator::setVertexData() {
    // Uncomment these lines to make a wedge for Task 6, then comment them out for Task 7:

//     float thetaStep = glm::radians(360.f / m_param2);
//     float currentTheta = 0 * thetaStep;
//     float nextTheta = 1 * thetaStep;
//     makeWedge(currentTheta, nextTheta);

    // Uncomment these lines to make sphere for Task 7:

    generateTerrain();
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void TerrainGenerator::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}


//// Generates the geometry of the output triangle mesh
//std::vector<float> Sphere::generateTerrain() {

//}

// Samples the (infinite) random vector grid at (row, col)
glm::vec2 TerrainGenerator::sampleRandomVector(int row, int col)
{
    std::hash<int> intHash;
    int index = intHash(row * 41 + col * 43) % m_lookupSize;
    return m_randVecLookup.at(index);
}

// Takes a grid coordinate (row, col), [0, m_resolution), which describes a vertex in a plane mesh
// Returns a normalized position (x, y, z); x and y in range from [0, 1), and z is obtained from getHeight()
glm::vec3 TerrainGenerator::getPosition(int row, int col) {
    // Normalizing the planar coordinates to a unit square
    // makes scaling independent of sampling resolution.
    float x = 7.0 * row / m_resolution; // TODO CHANGED FROM 16
    float z = 7.0 * col / m_resolution;

    float y = getHeight(x, z);
    return glm::vec3(x,y,z);
    //return glm::vec3(0.f,0.f,0.f);
}

// ================== Students, please focus on the code below this point

// Helper for computePerlin() and, possibly, getColor()
float interpolate(float A, float B, float alpha) {
    // Task 4: implement your easing/interpolation function below

    float ease = 3.f*powf(alpha, 2.f) - 2*powf(alpha, 3.f);

    // Return 0 as placeholder
    return A + (ease*(B - A));
}

// Takes a normalized (x, y) position, in range [0,1)
// Returns a height value, z, by sampling a noise function
float TerrainGenerator::getHeight(float x, float y) {
    float z = computePerlin(x * 0.5f, y * 0.5f) / 0.5f;
    z += computePerlin(x * 1, y * 1) / 1;
    z += computePerlin(x * 2, y * 2) / 2;
    z += computePerlin(x * 4, y * 4) / 4;

    float f = 2.f;
    float g = 1.f;
    float h = 2.f;

    float max = std::max(x,y);
    float min = std::min(x,y);

    if (max > 15.1f) {
        g = 1.f-((max-15.1f));
    } else if (min < 0.9f) {
        g = 1.f-(0.9f-min);
    }

    float mid = (powf(fmax((z+0.1), 0.f), 1.4f))  * (pow(f*((abs(x-8.f)/8.f) + (abs(y-8.f)/8.f)), 1.4f)/3.f);

    float centerdist = pow((x-8.f), 2.f) + pow((y-8.f), 2.f);

    if (centerdist > 6.f) {
        float modifier = std::min((centerdist-6.f)/2.f, 1.f);
        mid += modifier*computePerlin(x * 1, y * 1) / 1;
    }

    return mid*g;
}

// Computes the normal of a vertex by averaging neighbors
glm::vec3 TerrainGenerator::getNormal(int row, int col) {
    // Task 9: Compute the average normal for the given input indices

//    glm::vec3 center = getPosition(row, col);

//    glm::vec3 n_fin = glm::cross(getPosition(row-1, col-1) - center, getPosition(row, col-1) - center);
//    n_fin = n_fin + glm::cross(center, getPosition(row, col-1));
//    n_fin = n_fin + glm::cross(center, getPosition(row+1, col-1));
//    n_fin = n_fin + glm::cross(center, getPosition(row-1, col));
//    n_fin = n_fin + glm::cross(center, getPosition(row+1, col));
//    n_fin = n_fin + glm::cross(center, getPosition(row-1, col+1));
//    n_fin = n_fin + glm::cross(center, getPosition(row, col+1));
//    n_fin = n_fin + glm::cross(center, getPosition(row+1, col+1));

//    return glm::normalize(n_fin);

    glm::vec3 normal = glm::vec3(0, 0, 0);
        std::vector<std::vector<int>> neighborOffsets = { // Counter-clockwise around the vertex
         {-1, -1},
         { 0, -1},
         { 1, -1},
         { 1,  0},
         { 1,  1},
         { 0,  1},
         {-1,  1},
         {-1,  0}
        };
        glm::vec3 V = getPosition(row,col);
        for (int i = 0; i < 8; ++i) {
         int n1RowOffset = neighborOffsets[i][0];
         int n1ColOffset = neighborOffsets[i][1];
         int n2RowOffset = neighborOffsets[(i + 1) % 8][0];
         int n2ColOffset = neighborOffsets[(i + 1) % 8][1];
         glm::vec3 n1 = getPosition(row + n1RowOffset, col + n1ColOffset);
         glm::vec3 n2 = getPosition(row + n2RowOffset, col + n2ColOffset);
         normal = normal + glm::cross(n1 - V, n2 - V);
        }
    //return glm::vec3{0.f, 1.f, 0.f};
    return glm::normalize(-normal);

    // Return up as placeholder
    //return glm::vec3(0,0,1);
}

// Computes color of vertex using normal and, optionally, position
glm::vec3 TerrainGenerator::getColor(glm::vec3 normal, glm::vec3 position) {

    int u = (position[0]/2.f)*m_image.width();
    int v = (position[1]/2.f)*m_image.height();

    QColor pix(m_image.pixel(u, v));

    glm::vec3 out{float(pix.red())/255.f, float(pix.green())/255.f, float(pix.blue())/255.f};

    return out;
}

// Computes the intensity of Perlin noise at some point
float TerrainGenerator::computePerlin(float x, float y) {
    // Task 1: get grid indices (as ints)

    float x_min = floor(x);
    float x_max = ceil(x);
    float y_min = floor(y);
    float y_max = ceil(y);

    glm::vec2 loc{x, y};

    // Task 2: compute offset vectors

    glm::vec2 tl_offset = loc - glm::vec2(x_min, y_min);
    glm::vec2 tr_offset = loc - glm::vec2(x_max, y_min);
    glm::vec2 bl_offset = loc - glm::vec2(x_min, y_max);
    glm::vec2 br_offset = loc - glm::vec2(x_max, y_max);

    // Task 3: compute the dot product between offset and grid vectors

    float tl = glm::dot(sampleRandomVector(int(x_min), int(y_min)), tl_offset);
    float tr = glm::dot(sampleRandomVector(int(x_max), int(y_min)), tr_offset);
    float bl = glm::dot(sampleRandomVector(int(x_min), int(y_max)), bl_offset);
    float br = glm::dot(sampleRandomVector(int(x_max), int(y_max)), br_offset);

    // Task 5: use your interpolation function to produce the final value

    float dx = x - x_min;
    float dy = y - y_min;

    return interpolate(interpolate(tl, tr, dx), interpolate(bl, br, dx), dy);

    // Return 0 as a placeholder
    //return 0;
}

