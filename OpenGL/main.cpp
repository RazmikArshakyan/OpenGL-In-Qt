#include "AdvancedRenderer.h"

#include <QApplication>
#include <QOpenGLWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdvancedRenderer w;
    w.show();
    return a.exec();
}
