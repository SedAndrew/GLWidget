#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "transformational.h"
#include <QQuaternion>
#include <QVector>
#include <QMatrix4x4>

class Camera3D : public Transformational
{
public:
    Camera3D();
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions * functions = 0);
    void rotate(const QQuaternion &r);
    void rotateX(const QQuaternion &r);
    void rotateY(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &g);

    const QMatrix4x4 &getViewMatrix() const;
    void updateViewMatrix();

private:
    QQuaternion m_routate;
    QVector3D m_translate;
    float m_scale;
    QMatrix4x4 m_globalTransform;

    QMatrix4x4 m_viewMatrix;

    QQuaternion m_routateX;
   QQuaternion m_routateY;
};

#endif // CAMERA3D_H
