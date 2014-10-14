#ifndef _EYETER_PROGRAM_EDITOR_WIDGET_H_
#define _EYETER_PROGRAM_EDITOR_WIDGET_H_

#include <QWidget>

class QToolButton;
class QComboBox;

namespace EyeTER {
    namespace ui {

class Editor;

class ProgramEditorWidget : public QWidget
{
    Q_OBJECT

 public:
    ProgramEditorWidget(QWidget* parent = 0);
    void setProgram();

 private slots:
    void onNewTab();
    void onProcedureChanged(int idx);
    void onEditProcedure();
    void onNewProcedure();

 private:
    Editor* createEditor();
 private:
    QTabWidget* tabWidget;
    QComboBox* procedureCBox;
    QToolButton* newTabBtn;
    QToolButton* editProcedureBtn;
    QToolButton* newProcedureBtn;
};

}
}
#endif
