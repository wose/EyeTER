#ifndef _EYETER_CHART_WIDGET_H_
#define _EYETER_CHART_WIDGET_H_

#include <QWidget>

class QPainter;

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
    static const int margin = 5;

    void paintEvent(QPaintEvent* event);
    void drawLegend(QPainter& painter);
};

}
}

#endif
