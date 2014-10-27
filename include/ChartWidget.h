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
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

 private:
    void drawDataSets(QPainter& painter);
    void drawLegend(QPainter& painter);
    void drawCursor(QPainter& painter);

    std::vector<std::vector<long>> dataSets_;
    int lowerBound_;
    int upperBound_;
    int cursorX_;
    int cursorY_;

    float scalingX_;
    float scalingY_;

    bool movingLowerBound_;
    bool movingUpperBound_;

    static const int margin = 15;
    static const int tickLength = 5;
};

}
}

#endif
