#include <QtWidgets>

#include "GraphicWindow.h"
#include "OpenGLWidget.h"

namespace EyeTER {
    namespace ui {

GraphicWindow::GraphicWindow(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;

    openGLWidget_ = new OpenGLWidget(this, nullptr);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(openGLWidget_);

    setLayout(mainLayout);

    setWindowTitle(tr("Graphic Window"));
}

}
}
