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

    QStringList completeList;
    completeList << "foobar" << "mooo" << "mookooh" << "mooooo";
    completer_ = new QCompleter(completeList, this);
    setCompleter(completer_);

    updateEditorMarginAreaWidth(0);
    highlightCurrentLine();
}

void Editor::setCompleter(QCompleter *completer)
{
    if (completer_)
        QObject::disconnect(completer_, 0, this, 0);

    completer_ = completer;

    if (!completer_)
        return;

    completer_->setWidget(this);
    completer_->setCompletionMode(QCompleter::PopupCompletion);
    completer_->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(completer_, SIGNAL(activated(const QString&)), this,
                     SLOT(insertCompletion(const QString&)));
}

QCompleter* Editor::getCompleter() const
{
    return completer_;
}

void Editor::insertCompletion(const QString& completion)
{
    if(completer_->widget() != this)
        return;

    QTextCursor tCursor = textCursor();
    tCursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
    tCursor.insertText(completion);
    setTextCursor(tCursor);
}

QString Editor::textUnderCursor() const
{
    QTextCursor tCursor = textCursor();
    tCursor.select(QTextCursor::WordUnderCursor);
    return tCursor.selectedText();
}

void Editor::focusInEvent(QFocusEvent *event)
{
    if(completer_)
        completer_->setWidget(this);

    QPlainTextEdit::focusInEvent(event);
}

 void Editor::keyPressEvent(QKeyEvent *event)
 {
     if(completer_ && completer_->popup()->isVisible()) {
        switch (event->key()) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                event->ignore();
                return;
            default:
                break;
        }
     }

     bool isShortcut = ((event->modifiers() & Qt::ControlModifier) &&
                        event->key() == Qt::Key_E);
     if(!completer_ || !isShortcut)
         QPlainTextEdit::keyPressEvent(event);

     const bool ctrlOrShift = event->modifiers() &
         (Qt::ControlModifier | Qt::ShiftModifier);
     if(!completer_ || (ctrlOrShift && event->text().isEmpty()))
         return;

     static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
     bool hasModifier = (event->modifiers() != Qt::NoModifier) && !ctrlOrShift;
     QString completionPrefix = textUnderCursor();

     if(!isShortcut && (hasModifier || event->text().isEmpty() ||
                        completionPrefix.length() < 3 ||
                        eow.contains(event->text().right(1)))) {
         completer_->popup()->hide();
         return;
     }

     if(completionPrefix != completer_->completionPrefix()) {
         completer_->setCompletionPrefix(completionPrefix);
         completer_->popup()->setCurrentIndex(
             completer_->completionModel()->index(0, 0));
     }
     QRect cr = cursorRect();
     cr.setWidth(completer_->popup()->sizeHintForColumn(0)
                 + completer_->popup()->verticalScrollBar()->sizeHint().width());
     completer_->complete(cr);
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
