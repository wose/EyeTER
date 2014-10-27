#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>

#include <QtWidgets>

#include "ChartWidget.h"

namespace EyeTER {
    namespace ui {

ChartWidget::ChartWidget(QWidget* parent) :
    QWidget(parent),
    lowerBound_(0),
    upperBound_(256),
    cursorX_(0),
    cursorY_(0),
    movingUpperBound_(false),
    movingLowerBound_(false),
    scalingX_(1.0),
    scalingY_(1.0)
{
    setMouseTracking(true);
    srand (time(NULL));

    std::vector<long> dataSet;
    for(int idx = 0; idx < 256; ++idx)
        dataSet.push_back(rand() % 1000);

    dataSets_.push_back(dataSet);
}

void ChartWidget::mouseMoveEvent(QMouseEvent* event)
{
    cursorX_ = std::max(std::min(event->x(), width() - margin),
                        static_cast<int>(margin));
    cursorY_ = std::max(std::min(event->y(), height() - margin),
                        static_cast<int>(margin));

    if(movingLowerBound_)
        lowerBound_ = (cursorX_ - margin) / scalingX_;
    if(movingUpperBound_)
        upperBound_ = (cursorX_ - margin) / scalingX_;

    update();
}

void ChartWidget::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        if(std::abs(cursorX_ - margin - lowerBound_ * scalingX_) <
           std::abs(cursorX_ - margin - upperBound_ * scalingX_)) {
            movingLowerBound_ = true;
            lowerBound_ = (cursorX_ - margin) / scalingX_;
        } else {
            movingUpperBound_ = true;
            upperBound_ = (cursorX_ - margin) / scalingX_;
        }
        update();
    }
}

void ChartWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        movingLowerBound_ = false;
        movingUpperBound_ = false;
    }
}

void ChartWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.fillRect(margin, margin, width() - 2 * margin, height() - 2 * margin,
                     Qt::white);

    drawDataSets(painter);
    drawLegend(painter);

    if(!movingLowerBound_ && !movingUpperBound_)
        drawCursor(painter);
}

void ChartWidget::drawCursor(QPainter& painter)
{
    painter.resetTransform();
    QPen pen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(pen);

    painter.drawLine(margin, cursorY_, width() - margin, cursorY_);
    painter.drawLine(cursorX_, margin, cursorX_, height() - margin);
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
            QPointF(margin + tick * tickPitch, height() - margin + tickLength));
    }

    tickPitch = static_cast<float>(height() - 2 * margin) / ticks;

    for(int tick = 0; tick <= ticks; ++tick) {
        painter.drawLine(QPointF(margin, height() - margin - tick * tickPitch),
            QPointF(margin - tickLength, height() - margin - tick * tickPitch));
    }
}

void ChartWidget::drawDataSets(QPainter& painter)
{
    auto dataSet = dataSets_[0];
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.translate(margin, height() - margin);

    auto minmax = std::minmax_element(dataSet.begin(), dataSet.end());

    scalingX_ = static_cast<float>(width() - 2 * margin) / 256;
    scalingY_ = static_cast<float>(height() - 2 * margin) /
        (*minmax.second - *minmax.first);

    QPainterPath outOfROI, inROI;
    for(int idx = 0; idx < lowerBound_; ++idx) {
        outOfROI.addRect(scalingX_ * idx,
                         -(dataSet[idx] - *minmax.first) * scalingY_,
                         scalingX_, (dataSet[idx] - *minmax.first) * scalingY_);
    }

    for(int idx = upperBound_; idx < dataSet.size(); ++idx) {
        outOfROI.addRect(scalingX_ * idx,
                         -(dataSet[idx] - *minmax.first) * scalingY_,
                         scalingX_, (dataSet[idx] - *minmax.first) * scalingY_);

    }

    for(int idx = lowerBound_; idx < upperBound_; ++idx) {
        inROI.addRect(scalingX_ * idx,
                      -(dataSet[idx] - *minmax.first) * scalingY_,
                      scalingX_, (dataSet[idx] - *minmax.first) * scalingY_);
    }

    painter.fillPath(outOfROI, Qt::darkGray);
    painter.fillPath(inROI, Qt::darkBlue);

    // draw user bounds
    QPen pen(Qt::green, 1);
    painter.setPen(pen);

    painter.drawLine(lowerBound_ * scalingX_, 0,
                     lowerBound_ * scalingX_, -height() + 2*margin);

    QPainterPath lowerLabel;
    lowerLabel.moveTo(lowerBound_ * scalingX_, -height() + 2 * margin);
    lowerLabel.lineTo(lowerBound_ * scalingX_ - 4, -height() + 2 * margin - 4);
    lowerLabel.lineTo(lowerBound_ * scalingX_ + 4, -height() + 2 * margin - 4);
    painter.fillPath(lowerLabel, Qt::green);

    painter.drawText(lowerBound_ * scalingX_ - 15, -height() + 2 * margin - 14,
                     30, 10,
                     Qt::AlignCenter, QString::number(lowerBound_));

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(upperBound_ * scalingX_, 0,
                     upperBound_ * scalingX_, -height() + 2*margin);

    QPainterPath upperLabel;
    upperLabel.moveTo(upperBound_ * scalingX_, -height() + 2 * margin);
    upperLabel.lineTo(upperBound_ * scalingX_ - 4, -height() + 2 * margin - 4);
    upperLabel.lineTo(upperBound_ * scalingX_ + 4, -height() + 2 * margin - 4);
    painter.fillPath(upperLabel, Qt::red);

    painter.drawText(upperBound_ * scalingX_ - 15, -height() + 2 * margin - 14,
                     30, 10,
                     Qt::AlignCenter, QString::number(upperBound_));

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
