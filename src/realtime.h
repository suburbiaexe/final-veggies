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

#include "utils/objparser.h"

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

    //TOMATO
    GLuint tomato_blue_eyelids_vbo;
    GLuint tomato_blue_eyelids_vao;
    GLuint tomato_blue_eyelids2_vbo;
    GLuint tomato_blue_eyelids2_vao;
    GLuint tomato_blue_eyelids3_vbo;
    GLuint tomato_blue_eyelids3_vao;
    GLuint tomato_blue_eyelids4_vbo;
    GLuint tomato_blue_eyelids4_vao;
    GLuint tomato_eye_vbo;
    GLuint tomato_eye_vao;
    GLuint tomato_eye2_vbo;
    GLuint tomato_eye2_vao;
    GLuint tomato_material_vbo;
    GLuint tomato_material_vao;
    GLuint tomato_material4_vbo;
    GLuint tomato_material4_vao;
    GLuint tomato_material5_vbo;
    GLuint tomato_material5_vao;
    GLuint tomato_material6_vbo;
    GLuint tomato_material6_vao;
    GLuint tomato_pupil1_vbo;
    GLuint tomato_pupil1_vao;
    GLuint tomato_pupil2_vbo;
    GLuint tomato_pupil2_vao;
    GLuint tomato_stem_vbo;
    GLuint tomato_stem_vao;
    int tomato_blue_eyelids_size;
    int tomato_blue_eyelids2_size;
    int tomato_blue_eyelids3_size;
    int tomato_blue_eyelids4_size;
    int tomato_eye_size;
    int tomato_eye2_size;
    int tomato_material_size;
    int tomato_material4_size;
    int tomato_material5_size;
    int tomato_material6_size;
    int tomato_pupil1_size;
    int tomato_pupil2_size;
    int tomato_stem_size;
    void drawTomato(glm::mat4 viewM, glm::mat4 projM);

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

    GLuint m_fullscreen_vbo;
    GLuint m_fullscreen_vao;


    GLuint m_fbo;
    GLuint m_fbo_texture; // occlusion texture
    GLuint m_fbo_renderbuffer;
    GLuint m_defaultFBO;

    void paintGeometry(int pass);
    void paintSun();

    glm::mat4 initialView; // sky dome view and proj basically
    glm::mat4 initialProj;

    bool rotating;
};
