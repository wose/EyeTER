#ifndef _EYETER_EDITOR_H_
#define _EYETER_EDITOR_H_

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

namespace EyeTER {
    namespace ui {

class EditorMarginArea;;
class Highlighter;

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);

    void editorMarginAreaPaintEvent(QPaintEvent *event);
    int editorMarginAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateEditorMarginAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateEditorMarginArea(const QRect &, int);

private:
    QWidget* editorMarginArea;
    Highlighter* highlighter_;
};

}
}
#endif
