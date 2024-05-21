#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Util.h>
#include <iostream>

NGLScene::NGLScene()
{
    setTitle("Blank NGL");
}

NGLScene::~NGLScene()
{
    std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w, int _h)
{
    m_win.width = static_cast<int>(_w * devicePixelRatio());
    m_win.height = static_cast<int>(_h * devicePixelRatio());
    m_project = ngl::perspective(45.0f, float(_w) / _h, 0.1, 100);
}

void NGLScene::initializeGL()
{
    ngl::NGLInit::initialize();
    glClearColor(0.7f, 0.6f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    ngl::ShaderLib::loadShader("ParticleShader", "shaders/ParticleVertex.glsl", "shaders/ParticleFragment.glsl");
    ngl::ShaderLib::loadShader("BlurShader", "shaders/ParticleVertex.glsl", "shaders/ParticleBlur.glsl");
    ngl::ShaderLib::use("ParticleShader");
    ngl::ShaderLib::use("BlurShader");
    m_view = ngl::lookAt({30, 0, 15}, {0, 5, 0}, {0, 1, 0});

    // Sets up framebuffer and textures
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

    glGenTextures(2, colourBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colourBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_win.width, m_win.height, 0, GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colourBuffers[i], 0);
    }

    unsigned int attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }

    glGenFramebuffers(2, blurFBO);
    glGenTextures(2, blurTextures);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[i]);
        glBindTexture(GL_TEXTURE_2D, blurTextures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_win.width, m_win.height, 0, GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurTextures[i], 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "Blur Framebuffer " << i << " is not complete!" << std::endl;
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
    update();
}

void NGLScene::paintGL()
{
    // First pass: render the scene to framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO); //Binds the HDR framebuffer object
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the previous frame of colour and depth
    glViewport(0, 0, m_win.width, m_win.height); //viewport dimensions

    auto rotX = ngl::Mat4::rotateX(m_win.spinXFace);
    auto rotY = ngl::Mat4::rotateY(m_win.spinYFace);
    auto mouseRotation = rotX * rotY;
    mouseRotation.m_m[3][0] = m_modelPos.m_x;
    mouseRotation.m_m[3][1] = m_modelPos.m_y;
    mouseRotation.m_m[3][2] = m_modelPos.m_z;

    // Transformations through NGL
    ngl::Transformation tx;
    tx.setScale(1.0f, 1.0f, 1.0f);
    tx.setPosition(0.0f, 0.0f, 0.0f);

    ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
    ngl::ShaderLib::setUniform("MVP", m_project * m_view * mouseRotation);
    ngl::ShaderLib::use("ParticleShader");
    ngl::VAOPrimitives::draw("dragon");

    // Apply horizontal and vertical blur
    bool horizontal = true, first_iteration = true;
    unsigned int amount = 100;
    ngl::ShaderLib::use("BlurShader");

    for (unsigned int i = 0; i < amount; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[horizontal]);
//        glUniform1i(glGetUniformLocation(ngl::ShaderLib::getShaderID("ParticleShader"), "horizontal"), horizontal);
        glBindTexture(GL_TEXTURE_2D, (i == 0) ? colourBuffers[1] : blurTextures[!horizontal]);

        // Render the scene with the blurred texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, m_win.width, m_win.height);

        // Add the dragon into the scene in this loop
        ngl::ShaderLib::use("ParticleShader");
        glBindTexture(GL_TEXTURE_2D, first_iteration ? colourBuffers[1] : blurTextures[!horizontal]);
        ngl::VAOPrimitives::draw("dragon");

        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }
}


void NGLScene::keyPressEvent(QKeyEvent *_event)
{
    switch (_event->key())
    {
        case Qt::Key_Escape:
            QGuiApplication::exit(EXIT_SUCCESS);
            break;
        case Qt::Key_Space:
            m_win.spinXFace = 0;
            m_win.spinYFace = 0;
            m_modelPos.set(ngl::Vec3::zero());
            break;
        default:
            break;
    }
    update();
}
