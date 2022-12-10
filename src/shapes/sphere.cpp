#include "sphere.h"

void Sphere::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = std::max(2, param1);
    m_param2 = std::max(3, param2);
    setVertexData();
}

void Sphere::makeTile(glm::vec3 topLeft,
                      glm::vec3 topRight,
                      glm::vec3 bottomLeft,
                      glm::vec3 bottomRight) {
    // Task 5: Implement the makeTile() function for a Sphere
    // Note: this function is very similar to the makeTile() function for Cube,
    //       but the normals are calculated in a different way!

    glm::vec3 topLeftnorm = glm::normalize(topLeft);
    glm::vec3 topRightnorm = glm::normalize(topRight);
    glm::vec3 bottomLeftnorm = glm::normalize(bottomLeft);
    glm::vec3 bottomRightnorm = glm::normalize(bottomRight);

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, topLeftnorm);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, topRightnorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, bottomRightnorm);

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, topLeftnorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, bottomRightnorm);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, bottomLeftnorm);
}

void Sphere::makeWedge(float currentTheta, float nextTheta) {
    // Task 6: create a single wedge of the sphere using the
    //         makeTile() function you implemented in Task 5
    // Note: think about how param 1 comes into play here!
    float scale = 180.0 / m_param1;
    float r = 0.5;
    for (int i = 0; i < m_param1; i++) {
        float phi1 = glm::radians(i*scale);
        float phi2 = glm::radians((i+1)*scale);
        glm::vec3 tl{r * glm::sin(phi1) * glm::cos(currentTheta), r * glm::cos(phi1), r * glm::sin(phi1)*glm::sin(currentTheta)};
        glm::vec3 tr{r * glm::sin(phi1) * glm::cos(nextTheta), r * glm::cos(phi1), r * glm::sin(phi1)*glm::sin(nextTheta)};
        glm::vec3 bl{r * glm::sin(phi2) * glm::cos(currentTheta), r * glm::cos(phi2), r * glm::sin(phi2)*glm::sin(currentTheta)};
        glm::vec3 br{r * glm::sin(phi2) * glm::cos(nextTheta), r * glm::cos(phi2),  r * glm::sin(phi2)*glm::sin(nextTheta)};
        makeTile(tl, tr, bl, br);
    }
}

void Sphere::makeSphere() {
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

void Sphere::setVertexData() {
     makeSphere();
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void Sphere::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}
