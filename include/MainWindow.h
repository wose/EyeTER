#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qsci/qsciscintilla.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeEditor();
    void initializeLexer();
    void initializeMargin();
    void initializeCaretLine();
    void initializeFont();

public slots:
    void about();
    void onTextChanged();
    void onOpen();

private:
    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QMenu* viewMenu;
    QMenu* helpMenu;

    QAction* openFileAct;
    QAction* exitAct;
    QAction* aboutAct;

    QsciScintilla *editor;
};

#endif // MAINWINDOW_H

