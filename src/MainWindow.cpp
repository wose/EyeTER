#include <QtWidgets>
#include <QMenuBar>
#include <QFileDialog>

#include "MainWindow.h"

#include "Editor.h"
#include "GraphicWindow.h"
#include "HistogramWindow.h"
#include "ProgramEditorWidget.h"

namespace EyeTER {
    namespace ui {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("EyeTER");
    createActions();
    createMenus();

    ProgramEditorWidget* programEditor = new ProgramEditorWidget(this);
    //    editor = new QsciScintilla(this);
    setCentralWidget(programEditor);
    graphicWindow_ = new GraphicWindow;
    graphicWindow_->show();

    histogramWindow_ = new HistogramWindow;
    histogramWindow_->show();

    readSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About EyeTER"),
        tr("foobar baz"));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    writeSettings();

    graphicWindow_->close();
    histogramWindow_->close();
    event->accept();
}

void MainWindow::writeSettings()
{
    QSettings settings;

    settings.setValue("mainwindow/size", size());
    settings.setValue("mainwindow/pos", pos());
    settings.setValue("graphicwindow/size", graphicWindow_->size());
    settings.setValue("graphicwindow/pos", graphicWindow_->pos());
    settings.setValue("histogramwindow/size", histogramWindow_->size());
    settings.setValue("histogramwindow/pos", histogramWindow_->pos());
}

void MainWindow::readSettings()
{
    QSettings settings;

    resize(settings.value("mainwindow/size", QSize(400, 400)).toSize());
    move(settings.value("mainwindow/pos", QPoint(200, 200)).toPoint());
    graphicWindow_->resize(settings.value("graphicwindow/size", QSize(200, 200)).toSize());
    graphicWindow_->move(settings.value("graphicwindow/pos", QPoint(0, 0)).toPoint());
    histogramWindow_->resize(settings.value("histogramwindow/size", QSize(300, 100)).toSize());
    histogramWindow_->move(settings.value("histogramwindow/pos", QPoint(0, 0)).toPoint());
}

void MainWindow::createActions()
{
    openFileAct = new QAction(tr("&Open File"), this);
    openFileAct->setShortcut(QKeySequence::Open);
    connect(openFileAct, SIGNAL(triggered()), this, SLOT(onOpen()));

    exitAct = new QAction(tr("&Quit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    setMenuBar(new QMenuBar(this));
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::onOpen()
{
    QString filename =  QFileDialog::getOpenFileName(this, tr("Open .cpp file"),
                                                     QDir::currentPath(),
                                                    "CPP (*.cpp *.h *.cxx)");
    if (filename.isEmpty())
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    //    editor->setText(file.readAll());
    file.close();
}

void MainWindow::initializeEditor()
{
    //initializeFont();
    //initializeMargin();
    //initializeCaretLine();
    //initializeLexer();
}

void MainWindow::initializeFont()
{
    //QFont font("Courier", 12);
    //font.setFixedPitch(true);
    //editor->setFont(font);
}

void MainWindow::initializeMargin()
{
    //QFontMetrics fontmetrics = QFontMetrics(editor->font());
    //editor->setMarginsFont(editor->font());
    //editor->setMarginWidth(0, fontmetrics.width(QString::number(editor->lines())) + 6);
    //editor->setMarginLineNumbers(0, true);
    //editor->setMarginsBackgroundColor(QColor("#cccccc"));

    //connect(editor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void MainWindow::onTextChanged()
{
    //QFontMetrics fontmetrics = editor->fontMetrics();
    //editor->setMarginWidth(0, fontmetrics.width(QString::number(editor->lines())) + 6);
}

void MainWindow::initializeLexer()
{
    //QsciLexerCPP *lexer = new QsciLexerCPP();
    //lexer->setDefaultFont(editor->font());
    //lexer->setFoldComments(true);
    //editor->setLexer(lexer);
}

void MainWindow::initializeCaretLine()
{
    // Current line visible with special background color
    //    editor->setCaretLineVisible(true);
    // editor->setCaretLineBackgroundColor(QColor("#ffe4e4"));
}

}
}
