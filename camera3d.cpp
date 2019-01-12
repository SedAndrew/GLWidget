#include "camera3d.h"
#include <QOpenGLShaderProgram>

Camera3D::Camera3D()
{
    m_scale = 1.0f;
    m_globalTransform.setToIdentity();
}

void Camera3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    if (functions != 0) return;

    program->setUniformValue("u_viewMatrix", m_viewMatrix);
}

void Camera3D::rotate(const QQuaternion &r)
{
    m_routate = r * m_routate;    

    updateViewMatrix();
}

void Camera3D::rotateX(const QQuaternion &r)
{
    m_routateX = r * m_routateX;
    m_routate = m_routateX * m_routateY;

    updateViewMatrix();
}

void Camera3D::rotateY(const QQuaternion &r)
{
    m_routateY = r * m_routateY;
    m_routate = m_routateX * m_routateY;

    updateViewMatrix();
}

void Camera3D::translate(const QVector3D &t)
{
    m_translate += t;
    updateViewMatrix();
}

void Camera3D::scale(const float &s)
{
    m_scale *= s;

    m_viewMatrix.setToIdentity();
    m_viewMatrix.translate(m_translate);
    m_viewMatrix.rotate(m_routate);
    m_viewMatrix.scale(m_scale);
    m_viewMatrix = m_viewMatrix * m_globalTransform.inverted();
}

void Camera3D::setGlobalTransform(const QMatrix4x4 &g)
{
    m_globalTransform = g;
    updateViewMatrix();
}

const QMatrix4x4 &Camera3D::getViewMatrix() const
{
    return m_viewMatrix;
}

void Camera3D::updateViewMatrix()
{
    // загружаем матрицу проекции в шейдер, а также модельно видовую матрицу
    m_viewMatrix.setToIdentity();
    m_viewMatrix.translate(m_translate);
    m_viewMatrix.rotate(m_routate);
    m_viewMatrix.scale(m_scale);
    m_viewMatrix = m_viewMatrix * m_globalTransform.inverted();
}
