#ifndef _EYETER_EDITOR_MARGIN_AREA_H_
#define _EYETER_EDITOR_MARGIN_AREA_H_

#include <QObject>

class QSize;

namespace EyeTER {
    namespace ui {

class Editor;

class EditorMarginArea : public QWidget
{
    Q_OBJECT
 public:
    EditorMarginArea(Editor *editor) : QWidget(editor) {
        editor_ = editor;
    }

    QSize sizeHint() const {
        return QSize(editor_->editorMarginAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        editor_->editorMarginAreaPaintEvent(event);
    }

private:
    Editor *editor_;
};

}
}
#endif
