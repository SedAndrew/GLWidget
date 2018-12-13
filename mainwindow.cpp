#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widgetGL->setFocus();

    setCurrentFileName(QString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::load(const QString &f)
{
/*    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    setCurrentFileName(f);
    return true;*/
}

void MainWindow::setCurrentFileName(const QString &fileName)
{
   /* this->fileName = fileName;

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.objects";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*]").arg(shownName));
    setWindowModified(false);*/
}

void MainWindow::on_actionOpen_file_triggered()
{
    /*  QString fn = QFileDialog::getOpenFileName(this, tr("Открыть файл..."),QString(), tr("Objects (*.objects);;Все файлы (*)"));
       if (!fn.isEmpty())
           load(fn);

       getFile();*/
}

void MainWindow::getFile()
{
}


