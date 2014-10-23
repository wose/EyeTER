#ifndef _EYETER_CHART_WIDGET_H_
#define _EYETER_CHART_WIDGET_H_

#include <QWidget>
#include <vector>

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
    void paintEvent(QPaintEvent* event);

 private:
    void drawDataSets(QPainter& painter);
    void drawLegend(QPainter& painter);

    std::vector<std::vector<long>> dataSets_;
    int lowerBound_;
    int upperBound_;
    static const int margin = 5;
};

}
}

#endif
