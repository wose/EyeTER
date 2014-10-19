#include <QtWidgets>

#include "GraphicWindow.h"
#include "OpenGLWidget.h"

namespace EyeTER {
    namespace ui {

GraphicWindow::GraphicWindow(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;

    pointerBtn_ = new QToolButton;
    pointerBtn_->setIcon(QIcon("res/icons/pointer.png"));
    connect(pointerBtn_, SIGNAL(clicked()), this, SLOT(onPointer()));
    topLayout->addWidget(pointerBtn_);
    topLayout->addSpacing(5);

    zoomInBtn_ = new QToolButton;
    zoomInBtn_->setIcon(QIcon("res/icons/zoom-in.png"));
    connect(zoomInBtn_, SIGNAL(clicked()), this, SLOT(onZoomIn()));
    topLayout->addWidget(zoomInBtn_);

    zoomOutBtn_ = new QToolButton;
    zoomOutBtn_->setIcon(QIcon("res/icons/zoom-out.png"));
    connect(zoomOutBtn_, SIGNAL(clicked()), this, SLOT(onZoomOut()));
    topLayout->addWidget(zoomOutBtn_);
    topLayout->addStretch();

    openGLWidget_ = new OpenGLWidget(this, nullptr);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(openGLWidget_);

    setLayout(mainLayout);

    setWindowTitle(tr("Graphic Window"));
}

void GraphicWindow::onPointer()
{
}

void GraphicWindow::onZoomIn()
{
}

void GraphicWindow::onZoomOut()
{
}

}
}
