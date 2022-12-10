#include "cube.h"

void Cube::updateParams(int param1) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    setVertexData();
}

void Cube::makeTile(glm::vec3 topLeft,
                    glm::vec3 topRight,
                    glm::vec3 bottomLeft,
                    glm::vec3 bottomRight) {
    // Task 2: create a tile (i.e. 2 triangles) based on 4 given points.
    glm::vec3 topnorm = glm::normalize(glm::cross(bottomRight - topRight, bottomRight - topLeft));
    glm::vec3 bottomnorm = glm::normalize(glm::cross(bottomLeft - bottomRight, bottomLeft - topLeft));
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, bottomnorm);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, bottomnorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, bottomnorm);
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, topnorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, topnorm);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, topnorm);
}

void Cube::makeFace(glm::vec3 topLeft,
                    glm::vec3 topRight,
                    glm::vec3 bottomLeft,
                    glm::vec3 bottomRight) {
    // Task 3: create a single side of the cube out of the 4
    //         given points and makeTile()
    // Note: think about how param 1 affects the number of triangles on
    //       the face of the cubex
    // get the horizontal and vertical distances of the face
    glm::vec3 horzDist = topRight - topLeft;
    glm::vec3 vertDist = bottomLeft - topLeft;
    float scale = 1.0 / m_param1;
    // resize so that new face remains the same size
    glm::vec3 vertSize = vertDist * scale;
    glm::vec3 horzSize = horzDist * scale;
    //
    for (int i = 0; i < m_param1; i++) {
        for (int j = 0; j < m_param1; j++) {
            glm::vec3 topLeftOffset = ((float) i * horzSize) + ((float) j * vertSize);
            glm::vec3 topRightOffset = ((float) (i+1) * horzSize) + ((float) j * vertSize);
            glm::vec3 bottomLeftOffset = ((float) i * horzSize) + ((float) (j+1) * vertSize);
            glm::vec3 bottomRightOffset = ((float) (i+1) * horzSize) + ((float) (j+1) * vertSize);
            makeTile(topLeft+topLeftOffset, topLeft+topRightOffset, topLeft+bottomLeftOffset, topLeft+bottomRightOffset);
        }
    }

}

void Cube::setVertexData() {
    // Uncomment these lines for Task 2, then comment them out for Task 3:

//     makeTile(glm::vec3(-0.5f,  0.5f, 0.5f),
//              glm::vec3( 0.5f,  0.5f, 0.5f),
//              glm::vec3(-0.5f, -0.5f, 0.5f),
//              glm::vec3( 0.5f, -0.5f, 0.5f));

    // Uncomment these lines for Task 3:

    // front
     makeFace(glm::vec3(-0.5f,  0.5f, 0.5f),
              glm::vec3( 0.5f,  0.5f, 0.5f),
              glm::vec3(-0.5f, -0.5f, 0.5f),
              glm::vec3( 0.5f, -0.5f, 0.5f));

    // Task 4: Use the makeFace() function to make all 6 sides of the cube

     // back of the cube
     makeFace(glm::vec3( 0.5f,  0.5f, -0.5f),
              glm::vec3(-0.5f,  0.5f, -0.5f),
              glm::vec3( 0.5f, -0.5f, -0.5f),
              glm::vec3(-0.5f, -0.5f, -0.5f));
    // left size
     makeFace(glm::vec3(-0.5f,  0.5f, -0.5f),
              glm::vec3(-0.5f,  0.5f, 0.5f),
              glm::vec3(-0.5f, -0.5f, -0.5f),
              glm::vec3(-0.5f, -0.5f, 0.5f));
     // right side
     makeFace(glm::vec3( 0.5f,  0.5f, 0.5f),
              glm::vec3( 0.5f,  0.5f, -0.5f),
              glm::vec3( 0.5f, -0.5f, 0.5f),
              glm::vec3( 0.5f, -0.5f, -0.5f));
     // top
     makeFace(glm::vec3(-0.5f,  0.5f, -0.5f),
              glm::vec3( 0.5f,  0.5f, -0.5f),
              glm::vec3(-0.5f,  0.5f, 0.5f),
              glm::vec3( 0.5f,  0.5f, 0.5f));
     // bottom
     makeFace(glm::vec3(-0.5f, -0.5f, 0.5f),
              glm::vec3( 0.5f, -0.5f, 0.5f),
              glm::vec3(-0.5f, -0.5f, -0.5f),
              glm::vec3( 0.5f, -0.5f, -0.5f));

}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void Cube::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}
