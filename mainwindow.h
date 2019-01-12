#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "global.h"
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_file_triggered();

    void on_checkBox_transparency_clicked();
    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_light_clicked();
    void on_checkBox_directionLight_clicked();
    void on_checkBox_pointLight_clicked();
    void on_checkBox_spotLight_clicked();

signals:
    void setNewLight(Type &type);

private:
    Ui::MainWindow *ui;

    QString fileName;

    bool load(const QString &f);
    void setCurrentFileName(const QString &fileName);
    bool fileSave();
    bool fileSaveAs();

    void setFile();
    void getFile();

//    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
