#include <QtWidgets>
#include <QtOpenGL>

#include "OpenGLWidget.h"

namespace EyeTER {
    namespace ui {

OpenGLWidget::OpenGLWidget(QWidget* parent, QGLWidget* shareWidget)
    : QGLWidget(parent, shareWidget)
    , program_(0)
    , clearColor_(Qt::cyan)
{
}

OpenGLWidget::~OpenGLWidget()
{
}

QSize OpenGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize OpenGLWidget::sizeHint() const
{
    return QSize(200, 200);
}

void OpenGLWidget::setClearColor(const QColor &color)
{
    clearColor_ = color;
    updateGL();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
#ifdef GL_TEXTURE_2D
    glEnable(GL_TEXTURE_2D);
#endif

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

    QGLShader* vshader = new QGLShader(QGLShader::Vertex, this);
    const char* vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QGLShader* fshader = new QGLShader(QGLShader::Fragment, this);
    const char* fsrc =
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    program_ = new QGLShaderProgram(this);
    program_->addShader(vshader);
    program_->addShader(fshader);
    program_->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program_->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program_->link();

    program_->bind();
    program_->setUniformValue("texture", 0);

    texture_ = bindTexture(QPixmap("res/test_pattern.png"), GL_TEXTURE_2D);

    texCoords_.append(QVector2D(0, 1));
    texCoords_.append(QVector2D(1, 1));
    texCoords_.append(QVector2D(1, 0));
    texCoords_.append(QVector2D(0, 0));

    vertices_.append(QVector3D(768, 0, 0));
    vertices_.append(QVector3D(0, 0, 0));
    vertices_.append(QVector3D(0, 576, 0));
    vertices_.append(QVector3D(768, 576, 0));
}

void OpenGLWidget::paintGL()
{
    qglClearColor(clearColor_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 m;
    //    m.ortho(-1.0f, +1.0f, +1.0f, -1.0f, -10.0f, 10.0f);
    m.ortho(0.0f, 768.0f, 576.0f, 0.0f, -10.0f, 10.0f);


    program_->setUniformValue("matrix", m);
    program_->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program_->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program_->setAttributeArray
        (PROGRAM_VERTEX_ATTRIBUTE, vertices_.constData());
    program_->setAttributeArray
        (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords_.constData());

    glBindTexture(GL_TEXTURE_2D, texture_);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void OpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    lastPos_ = event->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos_.x();
    int dy = event->y() - lastPos_.y();

    lastPos_ = event->pos();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

}
}
