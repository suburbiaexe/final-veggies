#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>

#include "utils/shaderloader.h"
#include "utils/sceneparser.h"
#include "camera/camera.h"

#include "shapes/cone.h"
#include "shapes/cube.h"
#include "shapes/cylinder.h"
#include "shapes/sphere.h"

class Realtime : public QOpenGLWidget
{
public:
    Realtime(QWidget *parent = nullptr);
    void finish();                                      // Called on program exit
    void sceneChanged();
    void settingsChanged();

public slots:
    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

protected:
    void initializeGL() override;                       // Called once at the start of the program
    void paintGL() override;                            // Called whenever the OpenGL context changes or by an update() request
    void resizeGL(int width, int height) override;      // Called when window size changes

private:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // Tick Related Variables
    int m_timer;                                        // Stores timer which attempts to run ~60 times per second
    QElapsedTimer m_elapsedTimer;                       // Stores timer which keeps track of actual time between frames

    // Input Related Variables
    bool m_mouseDown = false;                           // Stores state of left mouse button
    glm::vec2 m_prev_mouse_pos;                         // Stores mouse position
    std::unordered_map<Qt::Key, bool> m_keyMap;         // Stores whether keys are pressed or not

    // Device Correction Variables
    int m_devicePixelRatio;

    GLuint phongProgram;     // Stores id of shader program
    GLuint colorProgram;
    GLuint postpassProgram;


    Camera cam;
    RenderData metaData;

    Cone cone;
    Sphere sphere;
    Cube cube;
    Cylinder cylinder;

    // shape vbos
    GLuint m_sphere_vbo; // Stores id of vbo
    GLuint m_cube_vbo; // Stores id of vbo
    GLuint m_cylinder_vbo; // Stores id of vbo
    GLuint m_cone_vbo; // Stores id of vbo

    // shape vaos
    GLuint m_cone_vao; // Stores id of vao
    GLuint m_cylinder_vao; // Stores id of vao
    GLuint m_sphere_vao; // Stores id of vao
    GLuint m_cube_vao; // Stores id of vao

    // sizes of shape data
    float sphereDataSize;
    float coneDataSize;
    float cylinderDataSize;
    float cubeDataSize;

    // shape data
    std::vector<GLfloat> m_sphereData;
    std::vector<GLfloat> m_cubeData;
    std::vector<GLfloat> m_coneData;
    std::vector<GLfloat> m_cylinderData;


    void makeFBO();
    void generateShapeData();
    void initializeBuffers();
    void bindVBO();
    void bindVAO();
    void bindDraw(PrimitiveType type);

    int m_fbo_width;
    int m_fbo_height;
    int m_screen_width;
    int m_screen_height;


    GLuint m_fbo;
    GLuint m_fbo_texture; // occlusion texture
    GLuint m_fbo_renderbuffer;
    GLuint m_defaultFBO;

    void paintGeometry(int pass);
    void paintSun();

};
