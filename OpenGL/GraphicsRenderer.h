#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_1_0>

class GraphicsRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    GraphicsRenderer(QWidget *parent = nullptr);
protected:
    void initializeGL() override;
    void paintGL() override;
};


#endif
