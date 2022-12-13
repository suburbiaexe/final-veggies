#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "qimage.h"

class TerrainGenerator
{
public:
    bool m_wireshade;

    QImage m_image;

    int getResolution() { return m_resolution; };
    void updateParams(int param1, int param2);
    void generateTerrain();
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    std::vector<float> generateShape() { return m_vertexData; }

private:

    void makeTile(glm::vec3 topLeft,
                          glm::vec3 topRight,
                          glm::vec3 bottomLeft,
                          glm::vec3 bottomRight);

    void makeWedge(float currentTheta, float nextTheta);

    // Member variables for terrain generation. You will not need to use these directly.
    std::vector<glm::vec2> m_randVecLookup;
    int m_resolution;
    int m_lookupSize;

    std::vector<float> m_vertexData;
    float m_radius = 0.5;
    int m_param1;
    int m_param2;

    void setVertexData();

    // Samples the (infinite) random vector grid at (row, col)
    glm::vec2 sampleRandomVector(int row, int col);

    // Takes a grid coordinate (row, col), [0, m_resolution), which describes a vertex in a plane mesh
    // Returns a normalized position (x, y, z); x and y in range from [0, 1), and z is obtained from getHeight()
    glm::vec3 getPosition(int row, int col);

    // ================== Students, please focus on the code below this point

    // Takes a normalized (x, y) position, in range [0,1)
    // Returns a height value, z, by sampling a noise function
    float getHeight(float x, float y);

    // Computes the normal of a vertex by averaging neighbors
    glm::vec3 getNormal(int row, int col);

    // Computes color of vertex using normal and, optionally, position
    glm::vec3 getColor(glm::vec3 normal, glm::vec3 position);

    // Computes the intensity of Perlin noise at some point
    float computePerlin(float x, float y);
};
