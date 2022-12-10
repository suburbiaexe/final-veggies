#include "realtime.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
//#include "glm/ext/matrix_clip_space.hpp"
//#include "glm/ext/matrix_transform.hpp"
#include "settings.h"
#include "glm/gtx/transform.hpp"


// ================== Project 5: Lights, Camera

Realtime::Realtime(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_prev_mouse_pos = glm::vec2(size().width()/2, size().height()/2);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    m_keyMap[Qt::Key_W]       = false;
    m_keyMap[Qt::Key_A]       = false;
    m_keyMap[Qt::Key_S]       = false;
    m_keyMap[Qt::Key_D]       = false;
    m_keyMap[Qt::Key_Control] = false;
    m_keyMap[Qt::Key_Space]   = false;

    // If you must use this function, do not edit anything above this
}

void Realtime::finish() {
    killTimer(m_timer);
    this->makeCurrent();

    // Students: anything requiring OpenGL calls when the program exits should be done here

    this->doneCurrent();
}

void Realtime::generateShapeData() {
    m_sphereData = sphere.generateShape();
    m_cubeData = cube.generateShape();
    m_cylinderData = cylinder.generateShape();
    m_coneData = cone.generateShape();
}


void Realtime::initializeGL() {
    m_devicePixelRatio = this->devicePixelRatio();

    m_defaultFBO = 2;
    m_screen_width = size().width() * m_devicePixelRatio;
    m_screen_height = size().height() * m_devicePixelRatio;
    m_fbo_width = m_screen_width;
    m_fbo_height = m_screen_height;

    m_timer = startTimer(1000/60);
    m_elapsedTimer.start();

    // Initializing GL.
    // GLEW (GL Extension Wrangler) provides access to OpenGL functions.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error while initializing GL: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Initialized GL: Version " << glewGetString(GLEW_VERSION) << std::endl;

    // Allows OpenGL to draw objects appropriately on top of one another
    glEnable(GL_DEPTH_TEST);
    // Tells OpenGL to only draw the front face
    glEnable(GL_CULL_FACE);
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

    // Students: anything requiring OpenGL calls when the program starts should be done here
    phongProgram = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/default.frag");
    colorProgram = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/color.frag");
    postpassProgram = ShaderLoader::createShaderProgram(":/resources/shaders/postpass.vert", ":/resources/shaders/postpass.frag");

    initializeBuffers();
    bindVBO();
    bindVAO();
    makeFBO();
}

void Realtime::makeFBO() {
    glGenTextures(1, &m_fbo_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_fbo_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 m_fbo_width, m_fbo_height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &m_fbo_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_fbo_renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fbo_width, m_fbo_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           m_fbo_texture, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, m_fbo_renderbuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Realtime::paintGeometry(int pass) {
    glm::mat4 viewMat = cam.viewMat;
    glm::mat4 projMat = cam.projMat;

    if (pass == 1) {
        glUseProgram(colorProgram);

        glm::mat3 invTransposeModel;
        glm::mat4 ctm = glm::mat4(1.0f);

        for (RenderShapeData &shape : metaData.shapes) {
            ctm = shape.ctm;
            invTransposeModel = inverse(transpose(glm::mat3(ctm)));
            glUniformMatrix3fv(glGetUniformLocation(colorProgram, "invTransposeModel"), 1, GL_FALSE, &invTransposeModel[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(colorProgram, "modelmat"), 1, GL_FALSE, &ctm[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(colorProgram, "viewmat"), 1, GL_FALSE, &viewMat[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(colorProgram, "projmat"), 1, GL_FALSE, &projMat[0][0]);

            glUniform1f(glGetUniformLocation(colorProgram, "color"), 0.0);
            PrimitiveType type = shape.primitive.type;
            bindDraw(type);
        }

    } else {
        glUseProgram(phongProgram);

        glUniform1f(glGetUniformLocation(phongProgram, "ka"), metaData.globalData.ka);
        glUniform1f(glGetUniformLocation(phongProgram, "kd"), metaData.globalData.kd);
        glUniform1f(glGetUniformLocation(phongProgram, "ks"), metaData.globalData.ks);

        glm::vec4 camerapos = cam.getCameraPosition();
        glUniform4fv(glGetUniformLocation(phongProgram, "camerapos"), 1, &camerapos[0]);

        std::vector<SceneLightData> lights = metaData.lights;
        int lightSize = std::fmin(metaData.lights.size(), 8);
        for (int i = 0; i < lightSize; i++) {
            std::string str = ("lightdir[" + std::to_string(i) + "]");
            int loc = glGetUniformLocation(phongProgram, str.c_str());
            glUniform4f(loc, lights[i].dir[0], lights[i].dir[1], lights[i].dir[2], lights[i].dir[3]);

            str = ("lightcolor[" + std::to_string(i) + "]");
            loc = glGetUniformLocation(phongProgram, str.c_str());
            glUniform4f(loc, lights[i].color[0], lights[i].color[1], lights[i].color[2], lights[i].color[3]);

            float type = 3;
            if (lights[i].type == LightType::LIGHT_DIRECTIONAL || (lights[i].dir.length() > 0 && lights[i].pos.length() == 0)) {
                type = 0;
            } else if (lights[i].type == LightType::LIGHT_POINT || (lights[i].dir.length() == 0 && lights[i].pos.length() > 0)) {
                type = 1;
            } else if (lights[i].type == LightType::LIGHT_SPOT || (lights[i].dir.length() > 0 && lights[i].pos.length() > 0)) {
                type = 2;
            }
            str = ("type[" + std::to_string(i) + "]");
            loc = glGetUniformLocation(phongProgram, str.c_str());
            glUniform1f(loc, type);

            // penumbra and angle
            str = ("outerangle[" + std::to_string(i) + "]");
            loc = glGetUniformLocation(phongProgram, str.c_str());
            glUniform1f(loc, lights[i].angle);

            str = ("innerangle[" + std::to_string(i) + "]");
            loc = glGetUniformLocation(phongProgram, str.c_str());
            glUniform1f(loc, lights[i].angle - lights[i].penumbra);

            str = ("lightpos[" + std::to_string(i) + "]");
            loc = glGetUniformLocation(phongProgram, str.c_str());
            glUniform4f(loc, lights[i].pos[0], lights[i].pos[1], lights[i].pos[2], lights[i].pos[3]);

            str = ("function[" + std::to_string(i) + "]");
            loc = glGetUniformLocation(phongProgram, str.c_str());
            glUniform3f(loc, lights[i].function[0], lights[i].function[1], lights[i].function[2]);
        }
        glUniform1f(glGetUniformLocation(phongProgram, "lightsize"), lightSize);
        glm::mat3 invTransposeModel;
        glm::mat4 ctm;
        for (RenderShapeData &shape : metaData.shapes) {
            ctm = shape.ctm;
            invTransposeModel = inverse(transpose(glm::mat3(ctm)));
            glUniformMatrix3fv(glGetUniformLocation(phongProgram, "invTransposeModel"), 1, GL_FALSE, &invTransposeModel[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(phongProgram, "modelmat"), 1, GL_FALSE, &ctm[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(phongProgram, "viewmat"), 1, GL_FALSE, &viewMat[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(phongProgram, "projmat"), 1, GL_FALSE, &projMat[0][0]);
            SceneMaterial mat = shape.primitive.material;
            glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &mat.cAmbient[0]);
            glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &mat.cDiffuse[0]);
            glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &mat.cSpecular[0]);
            glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shape.primitive.material.shininess);

            PrimitiveType type = shape.primitive.type;
            bindDraw(type);
        }

    }

    // bind geometry texture




    glBindVertexArray(0);
    glUseProgram(0);
}

void Realtime::paintSun() {

    glUseProgram(colorProgram);

    // color a white circle - or black if it is covered

    glm::mat4 viewMat = cam.viewMat;
    glm::mat4 projMat = cam.projMat;

    glm::mat3 invTransposeModel;
    glm::mat4 ctm = glm::mat4(1.0f);

    glm::vec4 cval = {1,1,1,0};

    glUniformMatrix4fv(glGetUniformLocation(colorProgram, "viewmat"), 1, GL_FALSE, &viewMat[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(colorProgram, "projmat"), 1, GL_FALSE, &projMat[0][0]);
    ctm *= glm::translate(glm::vec3(20,30,-80));
    ctm *= glm::scale(glm::vec3(7,7,7));

    invTransposeModel = inverse(transpose(glm::mat3(ctm)));
    glUniformMatrix3fv(glGetUniformLocation(colorProgram, "invTransposeModel"), 1, GL_FALSE, &invTransposeModel[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(colorProgram, "modelmat"), 1, GL_FALSE, &ctm[0][0]);

    glUniform1f(glGetUniformLocation(colorProgram, "color"), 1.0); // send color in as white

    bindDraw(PrimitiveType::PRIMITIVE_SPHERE);

    glBindVertexArray(0);
    glUseProgram(0);
}


void Realtime::paintGL() {
    // Students: anything requiring OpenGL calls every frame should be done here

    // Render pass 1: render
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);
    glViewport(0, 0, m_screen_width, m_screen_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintSun();
    paintGeometry(1);

//    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
//    glViewport(0, 0, m_screen_width, m_screen_height);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    paintGeometry(0);



}

void Realtime::resizeGL(int w, int h) {
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

    // Students: anything requiring OpenGL calls when the program starts should be done here
    cam.updateDims(w, h);
    glDeleteTextures(1, &m_fbo_texture);
    glDeleteRenderbuffers(1, &m_fbo_renderbuffer);
    glDeleteFramebuffers(1, &m_fbo);
    m_screen_width = size().width() * m_devicePixelRatio;
    m_screen_height = size().height() * m_devicePixelRatio;
    m_fbo_width = m_screen_width;
    m_fbo_height = m_screen_height;
    makeFBO();
    settingsChanged();
    cam.updatePerspective();
}

void Realtime::sceneChanged() {

    bool success = SceneParser::parse(settings.sceneFilePath, metaData);

    if (!success) {
        std::cerr << "Error loading scene: \"" << settings.sceneFilePath << "\"" << std::endl;
        return;
    }
    cam.init(metaData.cameraData, size().width(), size().height(), settings.farPlane, settings.nearPlane);

    update(); // asks for a PaintGL() call to occur
}

void Realtime::settingsChanged() {
    makeCurrent();
    cam.updatePlanes(settings.nearPlane, settings.farPlane);
    int param1 = settings.shapeParameter1;
    int param2 = settings.shapeParameter2;

    cone.updateParams(param1, param2);
    cube.updateParams(param1);
    sphere.updateParams(param1, param2);
    cylinder.updateParams(param1, param2);

    generateShapeData();
    bindVBO();

    update(); // asks for a PaintGL() call to occur
}

// ================== Project 6: Action!

void Realtime::keyPressEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = true;
}

void Realtime::keyReleaseEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = false;
}

void Realtime::mousePressEvent(QMouseEvent *event) {
    if (event->buttons().testFlag(Qt::LeftButton)) {
        m_mouseDown = true;
        m_prev_mouse_pos = glm::vec2(event->position().x(), event->position().y());
    }
}

void Realtime::mouseReleaseEvent(QMouseEvent *event) {
    if (!event->buttons().testFlag(Qt::LeftButton)) {
        m_mouseDown = false;
    }
}

void Realtime::mouseMoveEvent(QMouseEvent *event) {
    if (m_mouseDown) {
        int posX = event->position().x();
        int posY = event->position().y();
        int deltaX = posX - m_prev_mouse_pos.x;
        int deltaY = posY - m_prev_mouse_pos.y;
        m_prev_mouse_pos = glm::vec2(posX, posY);

        // Use deltaX and deltaY here to rotate

        update(); // asks for a PaintGL() call to occur
    }
}

void Realtime::timerEvent(QTimerEvent *event) {
    int elapsedms   = m_elapsedTimer.elapsed();
    float deltaTime = elapsedms * 0.001f;
    m_elapsedTimer.restart();

    // Use deltaTime and m_keyMap here to move around

    update(); // asks for a PaintGL() call to occur
}
