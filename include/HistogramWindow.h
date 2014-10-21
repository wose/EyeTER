#ifndef _EYETER_HISTOGRAM_WINDOW_H_
#define _EYETER_HISTOGRAM_WINDOW_H_

#include <QWidget>

namespace EyeTER {
    namespace ui {

class ChartWidget;

class HistogramWindow : public QWidget
{
    Q_OBJECT

 public:
    HistogramWindow(QWidget* parent = 0);

 private:
    ChartWidget* chartWidget_;
};

}
}
#endif
