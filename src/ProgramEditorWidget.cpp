#include <QtWidgets>
#include <QDebug>
#include <Qsci/qsciscintilla.h>

#include "ProgramEditorWidget.h"

ProgramEditorWidget::ProgramEditorWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;

    newTabBtn = new QToolButton;
    newTabBtn->setIcon(QIcon("res/icons/new-tab.png"));
    editProcedureBtn = new QToolButton;
    editProcedureBtn->setIcon(QIcon("res/icons/edit-procedure.png"));
    newProcedureBtn = new QToolButton;
    newProcedureBtn->setIcon(QIcon("res/icons/new-procedure.png"));

    procedureCBox = new QComboBox;
    procedureCBox->addItem("foo 1");
    procedureCBox->addItem("foo 2");
    procedureCBox->addItem("foo 3");

    topLayout->addWidget(newTabBtn);
    topLayout->addWidget(procedureCBox);
    topLayout->addWidget(editProcedureBtn);
    topLayout->addWidget(newProcedureBtn);

    tabWidget = new QTabWidget;
    tabWidget->addTab(createEditor(), "main");

    connect(newTabBtn, SIGNAL(clicked()), this, SLOT(onNewTab()));
    connect(procedureCBox, SIGNAL(currentIndexChanged(int)), this,
            SLOT(onProcedureChanged(int)));
    connect(editProcedureBtn, SIGNAL(clicked()), this, SLOT(onEditProcedure()));
    connect(newProcedureBtn, SIGNAL(clicked()), this, SLOT(onNewProcedure()));

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void ProgramEditorWidget::onNewTab()
{
    qDebug() << "onNewTab()";

    if(tabWidget)
        tabWidget->setCurrentIndex(tabWidget->addTab(createEditor(), "moo"));
}

void ProgramEditorWidget::onProcedureChanged(int idx)
{
    qDebug() << "onProcedureChanged(" << idx << ")";
}

void ProgramEditorWidget::onEditProcedure()
{
    qDebug() << "onEditProcedure()";
}

void ProgramEditorWidget::onNewProcedure()
{
    qDebug() << "onNewProcedure()";
}

QsciScintilla* ProgramEditorWidget::createEditor()
{
    QsciScintilla* editor = new QsciScintilla(this);
    // setup font size etc...
    return editor;
}

void ProgramEditorWidget::setProgram()
{
}
