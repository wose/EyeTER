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
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);

    painter.setPen(pen);
    painter.drawLine(10, 10, 10, height() - 10);
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
