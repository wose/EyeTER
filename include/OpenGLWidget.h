#ifndef _EYETER_OPENGL_WIDGET_H_
#define _EYETER_OPENGL_WIDGET_H_

#include <QGLWidget>
#include <QtGui/QOpenGLFunctions>

class QGLShaderProgram;

namespace EyeTER {
    namespace ui {

class OpenGLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

 public:
    explicit OpenGLWidget(QWidget* parent = 0, QGLWidget* shareWidget = 0);
    ~OpenGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setClearColor(const QColor &color);

 signals:
    void clicked();

 protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

 private:
    QColor clearColor_;
    QPoint lastPos_;

    GLuint texture_;
    QVector<QVector3D> vertices_;
    QVector<QVector2D> texCoords_;
    QGLShaderProgram* program_;
};

}
}

#endif
