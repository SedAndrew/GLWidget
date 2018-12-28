#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QBasicTimer>
#include <QKeyEvent>

class ObjectEngine3D;
class Transformational;
class Group3D;
class Camera3D;
class SkyBox;
class QOpenGLFramebufferObject;

class GLwidget : public QOpenGLWidget//, protected QOpenGLFunctions_4_5_Core
{
public:
    GLwidget(QWidget *parent = 0);
    ~GLwidget();

    int width, height;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void initShaders();
    void initCube(float width);
    void initCristal(float underside, float height);

    void addObject(ObjectEngine3D *object);

    QVector3D average_sum_3_vectors(QVector3D v1, QVector3D v2, QVector3D v3);
    QVector3D average_sum_4_vectors(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4);
    QVector3D average_sum_6_vectors(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4, QVector3D v5, QVector3D v6);

private:
    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_projectionLightMatrix;
    QMatrix4x4 m_lightMatrix; // для основного шейдера
    QMatrix4x4 m_shadowLightMatrix; // для теней

    float m_lightRotateX;
    float m_lightRotateY;

    QOpenGLShaderProgram m_program;
    QOpenGLShaderProgram m_programSkybox;
    QOpenGLShaderProgram m_programDepth;

    QVector2D m_mousePosition;
    //QQuaternion m_rotations;
    /* QQuaternion содержит информацию о векторе, вокруг которого
    осуществляется поворот, и об углах, на которых поворот будет осуществляться
    */

    QVector<ObjectEngine3D *> m_objects;
    QVector<Group3D *> m_groups;
    QVector<Transformational *> m_transformObjects;


    QBasicTimer m_timer;

    float angleObject;
    float angleGroup1;
    float angleGroup2;
    float angleMain;

    Camera3D *m_camera;
    SkyBox *m_skybox;

    QOpenGLFramebufferObject *m_depthBuffer;
    quint32 m_fbHeight;
    quint32 m_fbWidth;

};

#endif // GLWIDGET_H
