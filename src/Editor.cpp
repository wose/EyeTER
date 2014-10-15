#include <QtWidgets>

#include "Editor.h"
#include "EditorMarginArea.h"
#include "Highlighter.h"

namespace EyeTER {
    namespace ui {

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    editorMarginArea = new EditorMarginArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateEditorMarginAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateEditorMarginArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    setFont(font);

    highlighter_ = new Highlighter(document());

    updateEditorMarginAreaWidth(0);
    highlightCurrentLine();
}

int Editor::editorMarginAreaWidth()
{
    int digits = 1;
    int max = qMax(1000, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void Editor::updateEditorMarginAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(editorMarginAreaWidth(), 0, 0, 0);
}

void Editor::updateEditorMarginArea(const QRect &rect, int dy)
{
    if (dy)
        editorMarginArea->scroll(0, dy);
    else
        editorMarginArea->update(0, rect.y(), editorMarginArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateEditorMarginAreaWidth(0);
}

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    editorMarginArea->setGeometry(QRect(cr.left(), cr.top(), editorMarginAreaWidth(), cr.height()));
}

void Editor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::lightGray).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void Editor::editorMarginAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(editorMarginArea);
    painter.fillRect(event->rect(), QColor(240, 240, 240));


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::darkCyan);
            painter.drawText(0, top, editorMarginArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

}
}
