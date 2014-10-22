#include <vector>
#include <stdlib.h>
#include <time.h>

#include <QtWidgets>

#include "ChartWidget.h"

namespace EyeTER {
    namespace ui {

ChartWidget::ChartWidget(QWidget* parent) :
    QWidget(parent)
{
    srand (time(NULL));

    std::vector<long> dataSet;
    for(int idx = 0; idx < 256; ++idx)
        dataSet.push_back(rand() % 1000);

    dataSets_.push_back(dataSet);
}

void ChartWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    drawDataSets(painter);
    drawLegend(painter);
}

void ChartWidget::drawLegend(QPainter& painter)
{
    painter.resetTransform();
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);

    painter.setPen(pen);
    painter.drawLine(margin, margin, margin, height() - margin);
    painter.drawLine(margin, height() - margin,
                     width() - margin, height() - margin);

    static const int ticks = 10;
    float tickPitch = ((width() - 2 * margin) / ticks);

    for(int tick = 0; tick <= ticks; ++tick) {
        painter.drawLine(QPointF(margin + tick * tickPitch, height() - margin),
                         QPointF(margin + tick * tickPitch, height() - margin / 2));
    }

    tickPitch = ((height() - 2 * margin) / ticks);

    for(int tick = 0; tick <= ticks; ++tick) {
        painter.drawLine(QPointF(margin, height() - margin - tick * tickPitch),
                         QPointF(margin / 2, height() - margin - tick * tickPitch));
    }
}

void ChartWidget::drawDataSets(QPainter& painter)
{
    auto dataSet = dataSets_[0];
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.translate(margin, height() - margin);
    //    painter.scale((width() - 2 * margin) / 256.0, 1.0);

    int counter = 0;
    float scalingX = (float)(width() - 2 * margin) / 256;
    float scalingY = (float)(height() - 2 * margin) / 1000;

    QPainterPath path;
    path.moveTo(0, 0);

    for(auto value : dataSet) {
        path.lineTo(counter * scalingX, -value * scalingY);
        ++counter;
    }
    path.lineTo(counter * scalingX, 0);

    //    painter.drawPath(path);
    painter.fillPath(path, Qt::blue);
}

QSize ChartWidget::minimumSizeHint() const
{
    return QSize(300, 100);
}

QSize ChartWidget::sizeHint() const
{
    return QSize(300, 100);
}

}
}
