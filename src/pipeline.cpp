#include "realtime.h"

/**
 * @brief Realtime::initializeBuffers
 */
void Realtime::initializeBuffers() {
    glGenBuffers(1, &m_cylinder_vbo);
    glGenBuffers(1, &m_cube_vbo);
    glGenBuffers(1, &m_sphere_vbo);
    glGenBuffers(1, &m_cone_vbo);
    glGenBuffers(1, &terrain_vbo);

    glGenVertexArrays(1, &m_cylinder_vao);
    glGenVertexArrays(1, &m_cube_vao);
    glGenVertexArrays(1, &m_sphere_vao);
    glGenVertexArrays(1, &m_cone_vao);
     glGenVertexArrays(1, &terrain_vao);
}

/**
 * @brief Realtime::bindVBO
 */
void Realtime::bindVBO() {
    if (glewExperimental) {
        glBindBuffer(GL_ARRAY_BUFFER, m_cylinder_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_cylinderData.size(), m_cylinderData.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, m_cube_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_cubeData.size(), m_cubeData.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, m_sphere_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_sphereData.size(), m_sphereData.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, m_cone_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_coneData.size(), m_coneData.data(), GL_STATIC_DRAW);
        cylinderDataSize = m_cylinderData.size();
        coneDataSize = m_coneData.size();
        cubeDataSize = m_cubeData.size();
        sphereDataSize = m_sphereData.size();


        glBindBuffer(GL_ARRAY_BUFFER, terrain_vbo);
        std::vector<GLfloat> terrainData = terrain.generateShape();
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*terrainData.size(), terrainData.data(), GL_STATIC_DRAW);
        terrainDataSize = terrainData.size();

        glBindBuffer(GL_ARRAY_BUFFER, 0);


    }
}

/**
 * @brief Realtime::bindVAO
 */
void Realtime::bindVAO() {
    if (glewExperimental) {
        glBindBuffer(GL_ARRAY_BUFFER, m_sphere_vbo);
        glBindVertexArray(m_sphere_vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

        glBindBuffer(GL_ARRAY_BUFFER, m_cylinder_vbo);
        glBindVertexArray(m_cylinder_vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

        glBindBuffer(GL_ARRAY_BUFFER, m_cube_vbo);
        glBindVertexArray(m_cube_vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

        glBindBuffer(GL_ARRAY_BUFFER, m_cone_vbo);
        glBindVertexArray(m_cone_vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

        glBindVertexArray(terrain_vao);
        glBindBuffer(GL_ARRAY_BUFFER, terrain_vbo);
        //Add attributes to your VAO here
        //Vertices
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*9, reinterpret_cast<void*>(0));
        //Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*9, reinterpret_cast<void*>(3*sizeof(GLfloat)));
        // Colors
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*9, reinterpret_cast<void*>(6*sizeof(GLfloat)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

/**
 * @brief Realtime::bindDraw
 * @param type sceneprimitive type
 */
void Realtime::bindDraw(PrimitiveType type) {
    if (type == PrimitiveType::PRIMITIVE_SPHERE) {
        glBindVertexArray(m_sphere_vao);
        glDrawArrays(GL_TRIANGLES, 0, sphereDataSize / 6);
    } else if (type == PrimitiveType::PRIMITIVE_CUBE) {
        glBindVertexArray(m_cube_vao);
        glDrawArrays(GL_TRIANGLES, 0, cubeDataSize / 6);
    } else if (type == PrimitiveType::PRIMITIVE_CYLINDER) {
        glBindVertexArray(m_cylinder_vao);
        glDrawArrays(GL_TRIANGLES, 0, cylinderDataSize / 6);
    } else if (type == PrimitiveType::PRIMITIVE_CONE) {
//        glBindVertexArray(m_cone_vao);
//        glDrawArrays(GL_TRIANGLES, 0, coneDataSize / 6);
        glBindVertexArray(terrain_vao);
        glDrawArrays(GL_TRIANGLES, 0, terrainDataSize / 6);
    }
}
