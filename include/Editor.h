#ifndef _EYETER_EDITOR_H_
#define _EYETER_EDITOR_H_

#include <QPlainTextEdit>
#include <QObject>

class QCompleter;
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

    void setCompleter(QCompleter* completer);
    QCompleter* getCompleter() const;

 protected:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void resizeEvent(QResizeEvent *event);

 private slots:
    void insertCompletion(const QString& completion);
    void updateEditorMarginAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateEditorMarginArea(const QRect &, int);

 private:
    QString textUnderCursor() const;
    QWidget* editorMarginArea;
    Highlighter* highlighter_;
    QCompleter* completer_;
};

}
}
#endif
