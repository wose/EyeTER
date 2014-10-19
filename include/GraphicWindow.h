#ifndef _EYETER_GRAPHIC_WINDOW_H_
#define _EYETER_GRAPHIC_WINDOW_H_

#include <QWidget>

class QToolButton;

namespace EyeTER {
    namespace ui {

class OpenGLWidget;

class GraphicWindow : public QWidget
{
    Q_OBJECT

 public:
    GraphicWindow(QWidget* parent = 0);

 private slots:
    void onPointer();
    void onZoomIn();
    void onZoomOut();

 private:
    OpenGLWidget* openGLWidget_;

    QToolButton* pointerBtn_;
    QToolButton* zoomInBtn_;
    QToolButton* zoomOutBtn_;
};

}
}

#endif
