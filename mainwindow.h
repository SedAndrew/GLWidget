#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

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
