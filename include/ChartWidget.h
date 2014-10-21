#ifndef _EYETER_CHART_WIDGET_H_
#define _EYETER_CHART_WIDGET_H_

#include <QWidget>

namespace EyeTER {
    namespace ui {

class ChartWidget : public QWidget
{
    Q_OBJECT

 public:
    ChartWidget(QWidget* parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

 protected:
    void paintEvent(QPaintEvent* event);
};

}
}

#endif
