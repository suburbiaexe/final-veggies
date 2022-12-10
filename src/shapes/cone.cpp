#include "cone.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

void Cone::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    m_param2 = param2;
    setVertexData();
}


void Cone::makeTile(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft, glm::vec3 bottomRight, int type) {
    glm::vec3 tlNorm;
    glm::vec3 trNorm;
    glm::vec3 blNorm;
    glm::vec3 brNorm;

    glm::vec3 normal;
    if (type == 0) {
        // cone body
        tlNorm = glm::vec3{ 2 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2 * topLeft[2] };
        trNorm = glm::vec3{ 2 * topRight[0], 0.25 - (0.5 * topRight[1]), 2 * topRight[2] };
        blNorm = glm::vec3{ 2 * bottomLeft[0], 0.25 - (0.5 * bottomLeft[1]), 2 * bottomLeft[2] };
        brNorm = glm::vec3{ 2 * bottomRight[0], 0.25 - (0.5 * bottomRight[1]), 2 * bottomRight[2] };
    } else {
        // cone base
        normal = glm::vec3{0.0, -0.5, 0};
    }

    tlNorm = glm::normalize(tlNorm);
    trNorm = glm::normalize(trNorm);
    blNorm = glm::normalize(blNorm);
    brNorm = glm::normalize(brNorm);

    if (type == 0) {
        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, tlNorm);
        insertVec3(m_vertexData, bottomLeft);
        insertVec3(m_vertexData, blNorm);
        insertVec3(m_vertexData, topRight);
        insertVec3(m_vertexData, trNorm);

        insertVec3(m_vertexData, bottomLeft);
        insertVec3(m_vertexData, blNorm);
        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, brNorm);
        insertVec3(m_vertexData, topRight);
        insertVec3(m_vertexData, trNorm);
    } else {
        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, normal);
        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, normal);
        insertVec3(m_vertexData, topRight);
        insertVec3(m_vertexData, normal);

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, normal);
        insertVec3(m_vertexData, bottomLeft);
        insertVec3(m_vertexData, normal);
        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, normal);
    }

}

void Cone::makeTip(glm::vec3 tl, glm::vec3 tr) {
    glm::vec3 tlNorm = glm::vec3{ 2 * tl[0], 0.25 - (0.5 * tl[1]), 2 * tl[2] };
    glm::vec3 trNorm = glm::vec3{ 2 * tr[0], 0.25 - (0.5 * tr[1]), 2 * tr[2] };

    tlNorm = glm::normalize(tlNorm);
    trNorm = glm::normalize(trNorm);

    insertVec3(m_vertexData, tr);
    insertVec3(m_vertexData, trNorm);
    insertVec3(m_vertexData, tl);
    insertVec3(m_vertexData, tlNorm);
}

void Cone::makeWedge(float currTheta, float nextTheta) {
    glm::vec3 topLeft;
    glm::vec3 topRight;
    glm::vec3 bottomLeft;
    glm::vec3 bottomRight;

    float r = 0.5;
    float y = 1.f / m_param1;

    for (int i = 0; i < m_param1 - 1; i++) {
        topLeft = {(r * (1 - (y * i))) * cos(currTheta), (y * i) - 0.5, (r * (1 - (y * i))) * sin(currTheta) };
        topRight = {(r * (1 - (y * i))) * cos(nextTheta), (y * i) - 0.5, (r * (1 - (y * i))) * sin(nextTheta) };
        bottomLeft = {(r * (1 - (y * (i+1)))) * cos(currTheta), (y * (i+1)) - 0.5, (r * (1 - (y * (i+1)))) * sin(currTheta) };
        bottomRight = {(r * (1 - (y * (i+1)))) * cos(nextTheta), (y * (i+1)) - 0.5, (r * (1 - (y * (i+1)))) * sin(nextTheta) };

        makeTile(topLeft, topRight, bottomLeft, bottomRight, 0);

        topLeft = {r * cos(currTheta) * (y * i), -0.5, r * sin(currTheta) * (y * i)};
        topRight = {r * cos(nextTheta) * (y * i), -0.5, r * sin(nextTheta) * (y * i)};
        bottomLeft = {r * cos(currTheta) * (y * (i+1)), -0.5, r * sin(currTheta) * (y * (i+1))};
        bottomRight = {r * cos(nextTheta) * (y * (i+1)), -0.5, r * sin(nextTheta) * (y * (i+1))};

        makeTile(topLeft, topRight, bottomLeft, bottomRight, 1);
    }

    float thetaOffset = (nextTheta - currTheta) / 2.f;
    topLeft = {cos(currTheta + thetaOffset), 0.5, sin(currTheta + thetaOffset) };
    glm::vec3 tipNorm = glm::vec3{ topLeft[0], 0.5f, topLeft[2] };
    tipNorm = glm::normalize(tipNorm);
    insertVec3(m_vertexData, glm::vec3{ 0, 0.5, 0 }); // tip
    insertVec3(m_vertexData, tipNorm);

    topLeft = {r * (1 - (y * (m_param1 - 1))) * cos(currTheta), (y * (m_param1 - 1)) - 0.5, r * (1 - (y * (m_param1 - 1))) * sin(currTheta)};
    topRight = {r * (1 - (y * (m_param1 - 1))) * cos(nextTheta), (y * (m_param1 - 1)) - 0.5, r * (1 - (y * (m_param1 - 1))) * sin(nextTheta)};

    makeTip(topLeft, topRight);

    topLeft = {r * cos(currTheta) * (y * m_param1 - 1), -0.5, r * sin(currTheta) * (y * m_param1 - 1)};
    topRight = {r * cos(nextTheta) * (y * m_param1 - 1), -0.5, r * sin(nextTheta) * (y * m_param1 - 1)};
    bottomLeft = {r * cos(currTheta) * (y * (m_param1)), -0.5, r * sin(currTheta) * (y * (m_param1))};
    bottomRight = {r * cos(nextTheta) * (y * (m_param1)), -0.5, r * sin(nextTheta) * (y * (m_param1))};

    makeTile(topLeft, topRight, bottomLeft, bottomRight, 1);

}

void Cone::makeCone() {
    float scale = 360.f / m_param2;
    float theta1;
    float theta2;

    for (int i = 0; i < m_param2; i++) {
        theta1 = glm::radians(i * scale);
        theta2 = glm::radians((i + 1) * scale);
        makeWedge(theta1, theta2);
    }
}

void Cone::setVertexData() {
    // TODO for Project 5: Lights, Camera
    m_param2 = std::max(m_param2, 3);
    makeCone();
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void Cone::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}
