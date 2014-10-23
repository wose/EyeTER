#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <QtWidgets>

#include "ChartWidget.h"

namespace EyeTER {
    namespace ui {

ChartWidget::ChartWidget(QWidget* parent) :
    QWidget(parent),
    lowerBound_(20),
    upperBound_(200)
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

    painter.fillRect(margin, margin, width() - 2 * margin, height() - 2 * margin,
                     Qt::white);

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
    float tickPitch = static_cast<float>(width() - 2 * margin) / ticks;

    for(int tick = 0; tick <= ticks; ++tick) {
        painter.drawLine(QPointF(margin + tick * tickPitch, height() - margin),
            QPointF(margin + tick * tickPitch, height() - margin / 2));
    }

    tickPitch = static_cast<float>(height() - 2 * margin) / ticks;

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

    auto minmax = std::minmax_element(dataSet.begin(), dataSet.end());

    float scalingX = static_cast<float>(width() - 2 * margin) / 256;
    float scalingY = static_cast<float>(height() - 2 * margin) /
        (*minmax.second - *minmax.first);

    QPainterPath outOfROI, inROI;
    for(int idx = 0; idx < lowerBound_; ++idx) {
        outOfROI.addRect(scalingX * idx,
                         -(dataSet[idx] - *minmax.first) * scalingY,
                         scalingX, (dataSet[idx] - *minmax.first) * scalingY);
    }

    for(int idx = upperBound_; idx < dataSet.size(); ++idx) {
        outOfROI.addRect(scalingX * idx,
                         -(dataSet[idx] - *minmax.first) * scalingY,
                         scalingX, (dataSet[idx] - *minmax.first) * scalingY);

    }

    for(int idx = lowerBound_; idx < upperBound_; ++idx) {
        inROI.addRect(scalingX * idx, -(dataSet[idx] - *minmax.first) * scalingY,
                      scalingX, (dataSet[idx] - *minmax.first) * scalingY);
    }

    painter.fillPath(outOfROI, Qt::gray);
    painter.fillPath(inROI, Qt::black);

    // draw user bounds
    QPen pen(Qt::green, 1);
    painter.setPen(pen);

    painter.drawLine(lowerBound_ * scalingX, 0,
                     lowerBound_ * scalingX, -height() + 2*margin);

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(upperBound_ * scalingX, 0,
                     upperBound_ * scalingX, -height() + 2*margin);
}

QSize ChartWidget::minimumSizeHint() const
{
    return QSize(400, 300);
}

QSize ChartWidget::sizeHint() const
{
    return QSize(400, 300);
}

}
}
