/*
Класс подразумевает объект, который можно трансформировать тем или иным способом:
вращать, перемещать либо масштабировать
*/

#ifndef TRANSFORMATIONAL_H
#define TRANSFORMATIONAL_H

class QQuaternion;
class QVector3D;
class QMatrix4x4;
class QOpenGLShaderProgram;
class QOpenGLFunctions;


//абстрактный класс (т.к. использваться будет как интерфейс для других классов,
//которые будут от него унаследованны )
class Transformational
{
public:
    virtual ~Transformational(){}
    virtual void rotate(const QQuaternion &r) = 0; // метод вращение
    virtual void translate(const QVector3D &t) = 0; // метод перемещения
    virtual void scale(const float &s) = 0; // масштабирование
    /* setGlobalTransform - метод применения к текущей локальной системе координат преобразования
    текущей системы координат в пределах глобальной системы координат.
    Метод будет задавть позицию и поворот этой локальной системы координат в пределах родительской для нее
    глобальной системы координт.
    */
    virtual void setGlobalTransform(const QMatrix4x4 &g) = 0;
    virtual void draw(QOpenGLShaderProgram *program, QOpenGLFunctions * functions) = 0;
};

#endif // TRANSFORMATIONAL_H
