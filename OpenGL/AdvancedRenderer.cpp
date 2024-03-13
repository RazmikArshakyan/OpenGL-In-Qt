#include "AdvancedRenderer.h"

AdvancedRenderer::AdvancedRenderer(QWidget *parent) : QOpenGLWidget(parent) {}

AdvancedRenderer::~AdvancedRenderer() {
    makeCurrent();
    delete vertexShader;
    delete fragmentShader;
    delete shaderProgram;
    glDeleteBuffers(1, &VBO);
    doneCurrent();
    delete timer;
}

void AdvancedRenderer::initializeGL() {
    initializeOpenGLFunctions();

    // Vertex shader source
    const char *vertexSource =
        "#version 330 core\n"
        "in vec3 position;"
        "uniform mat4 mvp_matrix;"
        "void main() {"
        "   gl_Position = mvp_matrix * vec4(position, 1.0);"
        "}";

    // Fragment shader source
    const char *fragmentSource =
        "#version 330 core\n"
        "out vec4 fragColor;"
        "void main() {"
        "   fragColor = vec4(1.0, 0.5, 0.2, 1.0);"
        "}";

    // Compile vertex shader
    vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vertexShader->compileSourceCode(vertexSource);

    // Compile fragment shader
    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fragmentShader->compileSourceCode(fragmentSource);

    // Link shader program
    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);
    shaderProgram->link();

    // Vertex data
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f
    };

    // Create vertex buffer object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Enable vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    // Timer for animation
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AdvancedRenderer::animate);
    timer->start(16); // Update every 16 milliseconds
}

void AdvancedRenderer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void AdvancedRenderer::paintGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->bind();

    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);

    QMatrix4x4 view;
    view.translate(0.0f, 0.0f, -3.0f);

    QMatrix4x4 model;
    model.rotate(rotationAngle, QVector3D(1.0f, 0.3f, 0.5f));

    QMatrix4x4 mvpMatrix = projection * view * model;
    shaderProgram->setUniformValue("mvp_matrix", mvpMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    shaderProgram->release();
}

void AdvancedRenderer::animate() {
    rotationAngle += 0.5f;
    update(); // Request redrawing
}
