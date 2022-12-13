#include <stdexcept>
#include "camera.h"
#include "../settings.h"
#include "glm/gtx/transform.hpp"

void Camera::init(SceneCameraData camdata, int w, int h, float far, float near) {
    cdata = camdata;
    width = w;
    height = h;
    viewMat = getViewMatrix();
    inverseViewMat = glm::inverse(viewMat);
    projMat = getProjMat();
    farPlane = far;
    nearPlane = near;
    camworldpos = inverseViewMat * cdata.pos;
}

void Camera::updateTranslation(glm::mat4 translationmat) {
    cdata.pos = translationmat * cdata.pos;
    viewMat = getViewMatrix();
}

void Camera::updatePosAndView(glm::vec4 p) {
    cdata.pos = p;
    viewMat = getViewMatrix();
}

glm::mat4 Camera::updateRotation(glm::vec3 axis, float angle) {
    float cosval = cos(angle);
    float sinval = sin(angle);
    float ux = axis[0];
    float uy = axis[1];
    float uz = axis[2];
    glm::mat4 rotateVal = {cosval + pow(ux,2)*(1-cosval), ux*uy*(1-cosval) - uz * sinval, ux*uz*(1-cosval) + uy*sinval, 0,
                          ux*uy*(1-cosval) + uz*sinval, cosval + pow(uy, 2)*(1-cosval), uy*uz*(1-cosval) - ux*sinval, 0,
                          ux*uz*(1-cosval) - uy*sinval, uy*uz*(1-cosval) + uz*sinval, cosval + pow(uz, 2)*(1-cosval), 0,
                           0, 0, 0, 1};

    cdata.look = cdata.look * rotateVal;
    viewMat = getViewMatrix();
    return viewMat;
}

glm::mat4 Camera::getProjMat() const {
    glm::mat4 convertToSpace = {1.0, 0.0, 0.0, 0.0,
                                0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, -2.0, 0.0,
                                0.0, 0.0, -1.0, 1.0};
    float c = - nearPlane / farPlane;
    glm::mat4 parallelization = {1.0, 0.0, 0.0, 0.0,
                                0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, 1.0 / (1.0 + c), -1.0,
                                0.0, 0.0,  -c / (1.0 + c), 0.0};
    float heightAngle = getHeightAngle();
    float widthAngle = 2 * atan(getAspectRatio() * tan(heightAngle / 2));
    glm::mat4 scale = {1.0 / (farPlane * tan(widthAngle/2.0)), 0.0, 0.0, 0.0,
                       0.0, 1.0 / (farPlane * tan(heightAngle/2.0)), 0.0, 0.0,
                       0.0, 0.0, 1.0 / farPlane, 0.0,
                       0.0, 0.0, 0.0, 1.0};
    // where do we get width angle
    return convertToSpace * parallelization * scale;
}

glm::mat4 Camera::getViewMatrix() const {
    // Optional TODO: implement the getter or make your own design
    glm::vec4 look = cdata.look;
    glm::vec4 pos = cdata.pos;
    glm::vec4 up = cdata.up;
    float lookLen = glm::length(look);
    glm::vec4 w = -look / lookLen;

    // get v
    glm::vec4 vIntermediate = up - (glm::dot(up, w)) * w;
    float vIntermediateLen = glm::length(vIntermediate);
    glm::vec4 v = vIntermediate / vIntermediateLen;

    // get u
    glm::vec3 u = glm::cross(glm::vec3(v), glm::vec3(w));

    // get M_translate and M_rotate
    glm::mat4 M_translate = glm::mat4(1, 0, 0, 0,
                                      0, 1, 0 ,0,
                                      0, 0, 1, 0,
                                      -pos[0], -pos[1], -pos[2], 1);
    glm::mat4 M_rotate = glm::mat4(u[0], v[0], w[0], 0,
                                   u[1], v[1], w[1], 0,
                                   u[2], v[2], w[2], 0,
                                   0, 0, 0, 1);
    glm::mat4 mat = M_rotate * M_translate;
    return mat;
}

float Camera::getAspectRatio() const {
    // Optional TODO: implement the getter or make your own design
    return float(width) / float(height);
}

float Camera::getHeightAngle() const {
    // Optional TODO: implement the getter or make your own design
    return cdata.heightAngle;
}

float Camera::getFocalLength() const {
    // Optional TODO: implement the getter or make your own design
    return cdata.focalLength;
}

float Camera::getAperture() const {
    // Optional TODO: implement the getter or make your own design
    return cdata.aperture;
}

glm::vec4 Camera::getCameraPosition() const {
    return cdata.pos;
}

void Camera::updatePlanes(float n, float f) {
    farPlane = f;
    nearPlane = n;
    projMat = getProjMat();
}

void Camera::updateDims(int w, int h) {
    width = w;
    height = h;
    projMat = getProjMat();
}

void Camera::updatePerspective() {
    projMat = glm::perspective(glm::radians(45.0), 1.0 * width / height, 0.01, 100.0);
}
