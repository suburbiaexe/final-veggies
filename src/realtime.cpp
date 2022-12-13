#include "realtime.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include "settings.h"
#include "glm/gtx/transform.hpp"

// added for skybox
#include <filesystem>
namespace fs = std::filesystem;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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
    m_keyMap[Qt::Key_C] = false;
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
    skyboxProgram = ShaderLoader::createShaderProgram(":/resources/shaders/skybox.vert", ":/resources/shaders/skybox.frag");

    initializeBuffers();
    bindVBO();
    bindVAO();
    makeFBO();

    std::vector<GLfloat> fullscreen_quad_data =
    { //     POSITIONS    //
        -1.0f,  1.0f, 0.0f,
         0.0f, 1.0f, 0.0f, // tl uv
        -1.0f, -1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, // bl uv
         1.0f, -1.0f, 0.0f,
         1.0f, 0.0f, 0.0f, // br uv
         1.0f,  1.0f, 0.0f,
         1.0f, 1.0f, 0.0f, // tr uv
        -1.0f,  1.0f, 0.0f,
         0.0f, 1.0f, 0.0f, // tr uv
         1.0f, -1.0f, 0.0f,
         1.0f, 0.0f, 0.0f // br uv
    };


    glGenBuffers(1, &m_fullscreen_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_fullscreen_vbo);
    glBufferData(GL_ARRAY_BUFFER, fullscreen_quad_data.size() * sizeof(GLfloat), fullscreen_quad_data.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &m_fullscreen_vao);
    glBindVertexArray(m_fullscreen_vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    glBindVertexArray(0);

    // skybox stuff
    glUniform1i(glGetUniformLocation(skyboxProgram, "skybox"), 0); // not sure if this is right?

    glEnable(GL_TEXTURE_CUBE_MAP_EXT);
    float points[] = {
      -10.0f,  10.0f, -10.0f,
      -10.0f, -10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,
       10.0f,  10.0f, -10.0f,
      -10.0f,  10.0f, -10.0f,

      -10.0f, -10.0f,  10.0f,
      -10.0f, -10.0f, -10.0f,
      -10.0f,  10.0f, -10.0f,
      -10.0f,  10.0f, -10.0f,
      -10.0f,  10.0f,  10.0f,
      -10.0f, -10.0f,  10.0f,

       10.0f, -10.0f, -10.0f,
       10.0f, -10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,

      -10.0f, -10.0f,  10.0f,
      -10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f, -10.0f,  10.0f,
      -10.0f, -10.0f,  10.0f,

      -10.0f,  10.0f, -10.0f,
       10.0f,  10.0f, -10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
      -10.0f,  10.0f,  10.0f,
      -10.0f,  10.0f, -10.0f,

      -10.0f, -10.0f, -10.0f,
      -10.0f, -10.0f,  10.0f,
       10.0f, -10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,
      -10.0f, -10.0f,  10.0f,
       10.0f, -10.0f,  10.0f
    };
    glGenBuffers(1, &sky_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, sky_vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &sky_vao);
    glBindVertexArray(sky_vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, sky_vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
    parentDir = parentDir + "/final-veggies/resources/skybox/";

    std::string front = parentDir+ "front.jpg";
    std::string back = parentDir+ "back.jpg";
    std::string top = parentDir+ "top.jpg";
    std::string bottom = parentDir+ "bottom.jpg";
    std::string left = parentDir+ "left.jpg";
    std::string right = parentDir+ "right.jpg";
    create_cube_map(front.c_str(),
                    back.c_str(),
                    top.c_str(),
                    bottom.c_str(),
                    left.c_str(),
                    right.c_str(),
                    &cubemapTexture);
}

void Realtime::create_cube_map(
    const char* front,
    const char* back,
    const char* top,
    const char* bottom,
    const char* left,
    const char* right,
    GLuint* tex_cube) {
    // generate a cube-map texture to hold all the sides
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, tex_cube);

    // load each image and copy into a side of the cube-map texture
    load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
    load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
    load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
    load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
    load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
    load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
      // format cube map texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool Realtime::load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int x, y, n;
    int force_channels = 4;
    unsigned char*  image_data = stbi_load(file_name, &x, &y, &n, force_channels);
    if (!image_data) {
      fprintf(stderr, "ERROR: could not load %s\n", file_name);
      return false;
    }
    // non-power-of-2 dimensions check
    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
      fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name);
    }

    // copy image data into 'target' side of cube map
    glTexImage2D(side_target, 0, GL_RGBA,
                 x, y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    free(image_data);
    return true;
}

void Realtime::makeFBO() {
    glGenTextures(1, &m_fbo_texture);
    glActiveTexture(GL_TEXTURE0);
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
        // change back to colorProgram
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
            glUniform1f(glGetUniformLocation(colorProgram, "sun"), 0.0);

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
            glUniform1f(glGetUniformLocation(colorProgram, "sun"), 0.0);
            SceneMaterial mat = shape.primitive.material;
            glUniform4fv(glGetUniformLocation(phongProgram, "cambient"), 1, &mat.cAmbient[0]);
            glUniform4fv(glGetUniformLocation(phongProgram, "cdiffuse"), 1, &mat.cDiffuse[0]);
            glUniform4fv(glGetUniformLocation(phongProgram, "cspecular"), 1, &mat.cSpecular[0]);
            glUniform1f(glGetUniformLocation(phongProgram, "shininess"), shape.primitive.material.shininess);

            PrimitiveType type = shape.primitive.type;
            bindDraw(type);
        }

    }
    glBindVertexArray(0);
    glUseProgram(0);
}

void Realtime::paintSun() {
    // change to colorProgram
    glUseProgram(colorProgram);

    // when initializing camera, set view and proj mats and then always pass those in, dont get new ones
    glm::mat3 invTransposeModel;
    glm::mat4 ctm = glm::mat4(1.0f);

    glm::mat4 proj = cam.projMat;
//    glm::mat4 view = cam.viewMat;
    glm::mat4 view = glm::mat4(glm::mat3(cam.viewMat));

    glUniformMatrix4fv(glGetUniformLocation(colorProgram, "viewmat"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(colorProgram, "projmat"), 1, GL_FALSE, &proj[0][0]);


    glUniform1f(glGetUniformLocation(colorProgram, "sun"), 1.0);
    ctm *= glm::translate(glm::vec3(10, 10, -30));
    ctm *= glm::scale(glm::vec3(6,6,6));

    invTransposeModel = inverse(transpose(glm::mat3(ctm)));
    glUniformMatrix3fv(glGetUniformLocation(colorProgram, "invTransposeModel"), 1, GL_FALSE, &invTransposeModel[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(colorProgram, "modelmat"), 1, GL_FALSE, &ctm[0][0]);

    glUniform1f(glGetUniformLocation(colorProgram, "color"), 1.0);

    glDisable(GL_DEPTH_TEST);

    bindDraw(PrimitiveType::PRIMITIVE_SPHERE);

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);
    glUseProgram(0);
}


void Realtime::paintGL() {
    // Students: anything requiring OpenGL calls every frame should be done here

    glm::mat4 proj = cam.projMat;
//    glm::mat4 view = cam.viewMat;
    glm::mat4 view = glm::mat4(glm::mat3(cam.viewMat));

//    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);
//    glDepthMask(GL_FALSE);
//    glUseProgram(skyboxProgram);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//    glBindVertexArray(sky_vao);

//    glUniformMatrix4fv(glGetUniformLocation(skyboxProgram, "viewmat"), 1, GL_FALSE, &view[0][0]);
//    glUniformMatrix4fv(glGetUniformLocation(skyboxProgram, "projmat"), 1, GL_FALSE, &proj[0][0]);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glDepthMask(GL_TRUE);

    // Render pass 1: render sun and occluding shapes to fbo texture
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_screen_width, m_screen_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintSun();
    paintGeometry(1);

    // Render pass 2: render shapes to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);
    glViewport(0, 0, m_screen_width, m_screen_height);
    paintGeometry(0);

    // Render pass 3: render shapes with sun and add rays
    glDepthMask(GL_TRUE);
    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // no longer blending - not drawing shapes in front anymore ?
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);
    glViewport(0, 0, m_screen_width, m_screen_height);

    glUseProgram(postpassProgram);

    glUniform1f(glGetUniformLocation(postpassProgram, "occlusiontexture"), 0);
    glm::vec4 sunPos = glm::vec4(0, 0, -40, 1.0);
    sunPos = sunPos * view;
    sunPos = sunPos * cam.projMat;
//    sunPos = sunPos * (1.f / sunPos[3]);
    sunPos = sunPos + glm::vec4(1.0, 1.0, 0.0, 0.0);
    sunPos = sunPos * 0.5f;
    glm::vec2 sun = glm::vec2(sunPos[0], sunPos[1]);

    glUniform2fv(glGetUniformLocation(postpassProgram, "sunPos"), 1, &sun[0]);

    glBindVertexArray(m_fullscreen_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fbo_texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);

//    glDisable(GL_BLEND);
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
    cam.init(metaData.cameraData, size().width(), size().height(), 200, settings.nearPlane);
    initialView = cam.viewMat;
    initialProj = cam.projMat;

    bezA = cam.cdata.pos;
    bezB = glm::vec4{ bezA[0] + 5, bezA[1], bezA[2] + 5, bezA[3] };
    bezC = glm::vec4{ bezA[0] + 5, bezA[1], bezA[2] - 5, bezA[3] };
    bezD = glm::vec4{ bezA[0] + 10, bezA[1], bezA[2] - 4, bezA[3] };
    bezFlag = false;
    bezT = 1;

    update(); // asks for a PaintGL() call to occur
}

void Realtime::settingsChanged() {
    makeCurrent();
    cam.updatePlanes(settings.nearPlane, 200);
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
        glm::mat4 view;
        if (event-> buttons() == Qt::LeftButton) {
            if (deltaX != 0) {
                glm::vec3 axis = {0,1,0};
                view = cam.updateRotation(axis, deltaX * 0.005f);
            }
            if (deltaY != 0) {
                glm::vec3 r = glm::cross(glm::vec3(cam.cdata.look), glm::vec3(cam.cdata.up));
                view = cam.updateRotation(r, deltaY * 0.005f);
            }
        }
        update(); // asks for a PaintGL() call to occur
    }
}

glm::vec4 Realtime::interp(glm::vec4 a, glm::vec4 b, float t) {
    glm::vec4 dest;
    dest[0] = a[0] + ((b[0] - a[0]) * t);
    dest[1] = a[1] + ((b[1] - a[1]) * t);
    dest[2] = a[2] + ((b[2] - a[2]) * t);
    dest[3] = 1.f;
    return dest;
}

void Realtime::bezier() {
    glm::vec4 ab,bc,cd,abbc,bccd,dest;

    ab = interp(bezA, bezB, bezT/999.f);
    bc = interp(bezB, bezC, bezT/999.f);
    cd = interp(bezC, bezD, bezT/999.f);
    abbc = interp(ab, bc, bezT/999.f);
    bccd = interp(bc, cd, bezT/999.f);
    dest = interp(abbc, bccd, bezT/999.f);
    cam.updatePosAndView(dest);
}

void Realtime::run_bezier() {
        bezier();
        bezT += 1;
}




void Realtime::timerEvent(QTimerEvent *event) {
    //run bezier fuction -- update position
    int elapsedms   = m_elapsedTimer.elapsed();
    float deltaTime = elapsedms * 0.001f;
//    deltaTime *= 5;
    m_elapsedTimer.restart();

    // Use deltaTime and m_keyMap here to move around
    glm::vec4 look = cam.cdata.look;
    glm::vec4 pos = cam.cdata.pos;
    glm::vec3 left = glm::normalize(glm::cross(glm::vec3(cam.cdata.up), glm::vec3(cam.cdata.look)));
    glm::vec4 normalized = glm::normalize(look - pos);
    if (bezT > 1000) {

            bezFlag = false;
            bezT = 1;
        } else if (bezFlag) {
            run_bezier();
        } else {
            if (m_keyMap.at(Qt::Key_C)) {
                bezFlag = true;
                //set bezier global flag to true
            }

            if (m_keyMap.at(Qt::Key_W)) {
                float val0 = (float) normalized[0] * deltaTime;
                float val1 = (float) normalized[1] * deltaTime;
                float val2 = (float) normalized[2] * deltaTime;
                glm::mat4 translate = glm::mat4(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         val0, val1, val2, 1);
                cam.updateTranslation(translate);
            }
            if (m_keyMap.at(Qt::Key_S)) {
                float val0 = (float) -normalized[0] * deltaTime;
                float val1 = (float) -normalized[1] * deltaTime;
                float val2 = (float) -normalized[2] * deltaTime;
                glm::mat4 translate = glm::mat4(1, 0, 0, 0,
                         0, 1, 0 ,0,
                         0, 0, 1, 0,
                         val0, val1, val2, 1);
                cam.updateTranslation(translate);
            }
            if (m_keyMap.at(Qt::Key_A)) {
                float val0 = (float) left[0] * deltaTime;
                float val1 = (float) left[1] * deltaTime;
                float val2 = (float) left[2] * deltaTime;
                glm::mat4 translate = glm::mat4(1, 0, 0, 0,
                         0, 1, 0 ,0,
                         0, 0, 1, 0,
                         val0, val1, val2, 1);
                cam.updateTranslation(translate);
            }
            if (m_keyMap.at(Qt::Key_D)) {
                float val0 = -(float) left[0] * deltaTime;
                float val1 = -(float) left[1] * deltaTime;
                float val2 = -(float) left[2] * deltaTime;
                glm::mat4 translate = glm::mat4(1, 0, 0, 0,
                         0, 1, 0 ,0,
                         0, 0, 1, 0,
                         val0, val1, val2, 1);
                cam.updateTranslation(translate);
            }
            if (m_keyMap.at(Qt::Key_Space)) {
                float val0 = 0.0f * deltaTime;
                float val1 = 1.0f * deltaTime;
                float val2 = 0.0f * deltaTime;
                glm::mat4 translate = glm::mat4(1, 0, 0, 0,
                         0, 1, 0 ,0,
                         0, 0, 1, 0,
                         val0, val1, val2, 1);
                cam.updateTranslation(translate);
            }
            if (m_keyMap.at(Qt::Key_Control) ) {
                float val0 = 0.0f * deltaTime;
                float val1 = -1.0f * deltaTime;
                float val2 = 0.0f * deltaTime;
                glm::mat4 translate = glm::mat4(1, 0, 0, 0,
                         0, 1, 0 ,0,
                         0, 0, 1, 0,
                         val0, val1, val2, 1);
                cam.updateTranslation(translate);
            }
    }

    update(); // asks for a PaintGL() call to occur
}
