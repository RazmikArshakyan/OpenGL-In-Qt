#ifndef ADVANCED_RENDERER_H
#define ADVANCED_RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QTimer>

class AdvancedRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    AdvancedRenderer(QWidget *parent = nullptr);
    ~AdvancedRenderer() override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private slots:
    void animate();

private:
    QOpenGLShader *vertexShader;
    QOpenGLShader *fragmentShader;
    QOpenGLShaderProgram *shaderProgram;
    GLuint VBO;
    QTimer *timer;
    float rotationAngle = 0.0f;
};

#endif // ADVANCED_RENDERER_H
