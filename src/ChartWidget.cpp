#include <QtWidgets>
//#include <QPen>

#include "ChartWidget.h"

namespace EyeTER {
    namespace ui {

ChartWidget::ChartWidget(QWidget* parent) :
    QWidget(parent)
{
}

void ChartWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    drawLegend(painter);
}

void ChartWidget::drawLegend(QPainter& painter)
{
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
