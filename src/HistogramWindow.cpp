#include <QtWidgets>

#include "ChartWidget.h"
#include "HistogramWindow.h"

namespace EyeTER {
    namespace ui {

HistogramWindow::HistogramWindow(QWidget* parent) :
    QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    chartWidget_ = new ChartWidget(this);

    mainLayout->addWidget(chartWidget_);

    setLayout(mainLayout);
    setWindowTitle(tr("Histogram Window"));
}

}
}
