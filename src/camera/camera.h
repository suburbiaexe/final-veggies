#pragma once

#include <glm/glm.hpp>
#include "utils/scenedata.h"

// A class representing a virtual camera.

// Feel free to make your own design choices for Camera class, the functions below are all optional / for your convenience.
// You can either implement and use these getters, or make your own design.
// If you decide to make your own design, feel free to delete these as TAs won't rely on them to grade your assignments.

class Camera {
public:
    void init(SceneCameraData camdata, int w, int h, float far, float near);
    // Returns the view matrix for the current camera settings.
    // You might also want to define another function that return the inverse of the view matrix.


    // Returns the aspect ratio of the camera.
    float getAspectRatio() const;

    // Returns the height angle of the camera in RADIANS.
    float getHeightAngle() const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getFocalLength() const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getAperture() const;

    glm::vec4 getCameraPosition() const;
    glm::mat4 inverseViewMat;
    glm::mat4 viewMat;
    glm::mat4 projMat;
    void updatePlanes(float n, float f);
    void updateDims(int w, int h);
    void updateTranslation(glm::mat4 translationmat);
    glm::mat4 updateRotation(glm::vec3 axis, float angle);
    float farPlane;
    float nearPlane;
    glm::vec4 camworldpos;
    SceneCameraData cdata;
    void updatePerspective();
private:

    int width;
    int height;

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjMat() const;
};
