#ifndef _EYETER_GRAPHIC_WINDOW_H_
#define _EYETER_GRAPHIC_WINDOW_H_

#include <QWidget>

namespace EyeTER {
    namespace ui {

class OpenGLWidget;

class GraphicWindow : public QWidget
{
    Q_OBJECT

 public:
    GraphicWindow(QWidget* parent = 0);

private:
    OpenGLWidget* openGLWidget_;
};

}
}

#endif
