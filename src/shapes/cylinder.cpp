#include "cylinder.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

void Cylinder::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    m_param2 = std::max(3, param2);
    setVertexData();
}

void Cylinder::makeTile(glm::vec3 topLeft,
                      glm::vec3 topRight,
                      glm::vec3 bottomLeft,
                      glm::vec3 bottomRight,
                      float type) {
    // Task 5: Implement the makeTile() function for a Sphere
    // Note: this function is very similar to the makeTile() function for Cube,
    //       but the normals are calculated in a different way!
    glm::vec3 tlnorm;
    glm::vec3 trnorm;
    glm::vec3 blnorm;
    glm::vec3 brnorm;

    if (type == 0) {
        tlnorm = {2 * topLeft[0], 0, 2 * topLeft[2]};
        trnorm = {2 * topRight[0], 0, 2 * topRight[2]};
        blnorm = {2 * bottomLeft[0], 0, 2 * bottomLeft[2]};
        brnorm = {2 * bottomRight[0], 0, 2 * bottomRight[2]};
    } else if (type == 1) {
        tlnorm = {0, 1, 0};
        trnorm = {0, 1, 0};
        blnorm = {0, 1, 0};
        brnorm = {0, 1, 0};
    } else {
        tlnorm = {0, -1, 0};
        trnorm = {0, -1, 0};
        blnorm = {0, -1, 0};
        brnorm = {0, -1, 0};
    }

    tlnorm = glm::normalize(tlnorm);
    trnorm = glm::normalize(trnorm);
    blnorm = glm::normalize(blnorm);
    brnorm = glm::normalize(brnorm);

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, tlnorm);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, trnorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, brnorm);

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, tlnorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, trnorm);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, blnorm);
}

void Cylinder::makeWedge(float currentTheta, float nextTheta) {
    // Task 6: create a single wedge of the sphere using the
    //         makeTile() function you implemented in Task 5
    // Note: think about how param 1 comes into play here!
    float scale = 1.0 / m_param1;
    float r = 0.5;
    glm::vec3 tl;
    glm::vec3 tr;
    glm::vec3 bl;
    glm::vec3 br;
    for (int i = 0; i < m_param1; i++) {
        tl = {r * glm::cos(currentTheta),- 0.5 + scale * i, r * glm::sin(currentTheta)};
        tr = {r * glm::cos(nextTheta), -0.5 + scale * i, r * glm::sin(nextTheta)};
        bl = {r * glm::cos(currentTheta), -0.5 + scale * (i+1), r * glm::sin(currentTheta)};
        br = {r * glm::cos(nextTheta), -0.5 + scale * (i+1), r * glm::sin(nextTheta)};
        makeTile(tr, tl, br, bl, 0);
        tl = {r * glm::cos(currentTheta) * scale * i, 0.5, r * glm::sin(currentTheta) * scale * i};
        tr = {r * glm::cos(nextTheta) * scale * i, 0.5, r * glm::sin(nextTheta) * scale * i};
        bl = {r * glm::cos(currentTheta) * scale * (i+1), 0.5 , r * glm::sin(currentTheta) * scale * (i+1)};
        br = {r * glm::cos(nextTheta) * scale * (i+1), 0.5, r * glm::sin(nextTheta) * scale * (i+1)};
        makeTile(tl, tr, bl, br, 1);
        tl = {r * glm::cos(currentTheta) * scale * i, -0.5, r * glm::sin(currentTheta) * scale * i};
        tr = {r * glm::cos(nextTheta) * scale * i, -0.5, r * glm::sin(nextTheta) * scale * i};
        bl = {r * glm::cos(currentTheta) * scale * (i+1), -0.5 , r * glm::sin(currentTheta) * scale * (i+1)};
        br = {r * glm::cos(nextTheta) * scale * (i+1), -0.5, r * glm::sin(nextTheta) * scale * (i+1)};
        makeTile(tr, tl, br, bl, 2);
    }
}

void Cylinder::makeCylinder() {
    // Task 7: create a full sphere using the makeWedge() function you
    //         implemented in Task 6
    // Note: think about how param 2 comes into play here!
    float scale = 360.0 / m_param2;
    for (int i = 0; i < m_param2; i++) {
        float theta1 = glm::radians(i*scale);
        float theta2 = glm::radians((i+1)*scale);
        makeWedge(theta1, theta2);
    }
}

void Cylinder::setVertexData() {
    // TODO for Project 5: Lights, Camera
    makeCylinder();
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void Cylinder::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}
