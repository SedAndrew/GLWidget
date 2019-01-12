#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QFileDialog>

bool f_transparency;
bool f_spotlights;
int m_transparencyPower;
Type m_typeLight = Point;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widgetGL->setFocus();
    ui->widget_ss->setVisible(false);
    ui->widget_light->setVisible(false);
    ui->checkBox_spotLight->setChecked(true);

//    connect(this, SIGNAL(setNewLight(Type)), ui->widgetGL, SLOT(getNewTypeLight(Type)));
//    connect(this, MainWindow::setNewLight, Ui_MainWindow::widgetGL, Ui_MainWindow::widgetGL->getNewTypeLight);
//    connect(/*ui->checkBox_pointLight*/this, SIGNAL(setNewLight(Type)), ui->widgetGL, SLOT(setNewTypeLight(Type)));
//    connect(/*ui->checkBox_spotLight*/this, SIGNAL(setNewLight(Type)), ui->widgetGL, SLOT(setNewTypeLight(Type)));

    setCurrentFileName(QString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::load(const QString &f)
{
    Q_UNUSED (f)
/*    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    setCurrentFileName(f);
    return true;
*/
}

void MainWindow::setCurrentFileName(const QString &fileName)
{
    Q_UNUSED (fileName)
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

void MainWindow::on_checkBox_transparency_clicked()
{
    ::f_transparency = true;
}

void MainWindow::on_checkBox_light_clicked()
{
    if (!ui->checkBox_light->isChecked())
    {
        ui->checkBox_directionLight->setChecked(false);
        ui->checkBox_pointLight->setChecked(false);
        ui->checkBox_spotLight->setChecked(true);
        ::m_typeLight = Spot;
    }
    emit setNewLight(::m_typeLight);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ::m_transparencyPower = value;
}

void MainWindow::on_checkBox_directionLight_clicked()
{
    ui->checkBox_pointLight->setChecked(false);
    ui->checkBox_spotLight->setChecked(false);
    if (ui->checkBox_directionLight->isChecked())
        ::m_typeLight = Directional;
    else
        ::m_typeLight = Spot;
    //if (ui->checkBox_directionLight->isChecked())
    emit setNewLight(::m_typeLight);
}

void MainWindow::on_checkBox_pointLight_clicked()
{
    ui->checkBox_directionLight->setChecked(false);
    ui->checkBox_spotLight->setChecked(false);
    if (ui->checkBox_pointLight->isChecked())
        ::m_typeLight = Point;
    else
        ::m_typeLight = Spot;

    emit setNewLight(::m_typeLight);
}

void MainWindow::on_checkBox_spotLight_clicked()
{
    ui->checkBox_directionLight->setChecked(false);
    ui->checkBox_pointLight->setChecked(false);
    ::m_typeLight = Spot;
    emit setNewLight(::m_typeLight);
}

