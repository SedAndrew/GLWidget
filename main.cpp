#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // устанавливаем формат
    QSurfaceFormat format;
    format.setSamples(16); // 16 samples при отрисовки (убираем зернистость)
    format.setDepthBufferSize(24);  // установка размера буфера глубины (обычно для андройда) ликвидация
                                    // возможной некоректной отрисовки задней части поверх передней
    QSurfaceFormat::setDefaultFormat(format); // установка default формата для opengl

    MainWindow w;
    w.show();

    return a.exec();
}
