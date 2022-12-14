#include "glm/gtx/transform.hpp"
#include "realtime.h"

/**
 * @brief Realtime::initializeBuffers
 */
void Realtime::initializeBuffers() {
    glGenBuffers(1, &m_cylinder_vbo);
    glGenBuffers(1, &m_cube_vbo);
    glGenBuffers(1, &m_sphere_vbo);
    glGenBuffers(1, &m_cone_vbo);
    glGenVertexArrays(1, &m_cylinder_vao);
    glGenVertexArrays(1, &m_cube_vao);
    glGenVertexArrays(1, &m_sphere_vao);
    glGenVertexArrays(1, &m_cone_vao);
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
        glBindVertexArray(m_cone_vao);
        glDrawArrays(GL_TRIANGLES, 0, coneDataSize / 6);
    }
}


void Realtime::drawTomato(glm::mat4 viewM, glm::mat4 projM) {
    std::vector<glm::mat4> tomato_ctms = {glm::mat4(1.0f), glm::mat4(1.0f),
                                          glm::mat4(1.0f), glm::mat4(1.0f),
                                          glm::mat4(1.0f), glm::mat4(1.0f),
                                          glm::mat4(1.0f), glm::mat4(1.0f),
                                          glm::mat4(1.0f), glm::mat4(1.0f),
                                          glm::mat4(1.0f), glm::mat4(1.0f),
                                          glm::mat4(1.0f)};
    for (int i = 0; i < tomato_ctms.size(); i++) {
        tomato_ctms[i] *= glm::scale(glm::vec3(.5,.5,.5));
    }
    std::vector<glm::vec4> tomato_kas = {glm::vec4(1,1,1,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0)};
    std::vector<glm::vec4> tomato_kds = {glm::vec4(.8,.006273,.006273,0), glm::vec4(0.01393,0.239888,0.030041,0),
                                         glm::vec4(0,0,0,0), glm::vec4(.8,.006273,.006273,0),
                                         glm::vec4(.8,.006273,.006273,0), glm::vec4(0.8,0.8,0.8,0),
                                         glm::vec4(0,0,0,0), glm::vec4(0.8,0.8,0.8,0),
                                         glm::vec4(0,0,0,0), glm::vec4(.8,.006273,.006273,0),
                                         glm::vec4(.8,.006273,.006273,0), glm::vec4(.8,.006273,.006273,0),
                                         glm::vec4(0.8,0.8,0.8,0)};
    std::vector<glm::vec4> tomato_kss = {glm::vec4(0.5,0.5,0.5,0), glm::vec4(0.5,0.5,0.5,0),
                                         glm::vec4(0.5,0.5,0.5,0), glm::vec4(0.5,0.5,0.5,0),
                                         glm::vec4(0.5,0.5,0.5,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0), glm::vec4(1,1,1,0),
                                         glm::vec4(1,1,1,0), glm::vec4(0.5,0.5,0.5,0),
                                         glm::vec4(0.5,0.5,0.5,0), glm::vec4(0.5,0.5,0.5,0),
                                         glm::vec4(0.5,0.5,0.5,0)};
    std::vector<float> shininesses = {sqrtf(360), sqrtf(250),
                                      sqrtf(360), sqrtf(250),
                                     sqrtf(250), sqrtf(640),
                                     sqrtf(722.5),sqrtf(640),
                                      sqrtf(722.5), sqrtf(250),
                                     sqrtf(250), sqrtf(360),
                                     sqrtf(250)};
    std::cout << "before uniforms" <<std::endl;
    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[0])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[0][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[0][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[0]);
    glBindVertexArray(tomato_material6_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_material6_size / 6);

    std::cout << "after uniform 1" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[1])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[1][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[1][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[1][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[1][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[1]);
    glBindVertexArray(tomato_stem_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_stem_size / 6);
    std::cout << "after uniform 2" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[2])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[2][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[2][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[2][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[2][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[2]);
    glBindVertexArray(tomato_material5_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_material5_size / 6);
    std::cout << "after uniform 3" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[3])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[3][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[3][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[3][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[3][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[3]);
    glBindVertexArray(tomato_blue_eyelids_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_blue_eyelids_size / 6);
    std::cout << "after uniform 4" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[4])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[4][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[4][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[4][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[4][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[4]);
    glBindVertexArray(tomato_blue_eyelids2_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_blue_eyelids2_size / 6);
    std::cout << "after uniform 5" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[5])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[5][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[5][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[5][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[5][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[5]);
    glBindVertexArray(tomato_eye_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_eye_size / 6);
    std::cout << "after uniform 6" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[6])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[6][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[6][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[0][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[6]);
    glBindVertexArray(tomato_pupil1_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_pupil1_size / 6);
    std::cout << "after uniform 7" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[7])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[7][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[7][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[7][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[7][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[7]);
    glBindVertexArray(tomato_eye2_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_eye2_size / 6);
    std::cout << "after uniform 8" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[8])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[8][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[8][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[8][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[8][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[8]);
    glBindVertexArray(tomato_pupil2_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_pupil2_size / 6);
    std::cout << "after uniform 9" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[9])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[9][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[9][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[9][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[9][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[9]);
    glBindVertexArray(tomato_blue_eyelids3_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_blue_eyelids3_size / 6);
    std::cout << "after uniform 10" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[10])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[10][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[10][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[10][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[10][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[10]);
    glBindVertexArray(tomato_blue_eyelids4_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_blue_eyelids4_size / 6);
    std::cout << "after uniform 11" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[11])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[11][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[11][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[11][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[11][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[11]);
    glBindVertexArray(tomato_material4_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_material4_size / 6);
    std::cout << "after uniform 12" <<std::endl;

    glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &glm::inverse(glm::transpose(glm::mat3(tomato_ctms[12])))[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &tomato_ctms[12][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewM[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projM[0][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &tomato_kas[12][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &tomato_kds[12][0]);
    glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &tomato_kss[12][0]);
    glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shininesses[12]);
    glBindVertexArray(tomato_material_vao);
    glDrawArrays(GL_TRIANGLES, 0, tomato_material_size / 6);
    std::cout << "after uniform 13" <<std::endl;

}
