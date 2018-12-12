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

struct VertexData
{
    VertexData(){}
    VertexData(QVector3D p, QVector2D t, QVector3D n) :
        position(p), texCoord(t), normal(n){}

    QVector3D position; // позиция точки
    QVector2D texCoord; // текстурные координаты
    QVector3D normal;   // нормаль точки
};

class GLwidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
public:
    GLwidget(QWidget *parent = 0);
    ~GLwidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initCube(float width);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent *event);
    void wheelEvent     (QWheelEvent *event);
    void timerEvent     (QTimerEvent *event);
    void keyPressEvent  (QKeyEvent   *event);

    QVector3D average_sum_3_vectors(QVector3D v1, QVector3D v2, QVector3D v3);
    QVector3D average_sum_4_vectors(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4);
    QVector3D average_sum_6_vectors(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4, QVector3D v5, QVector3D v6);


private:
    QMatrix4x4 m_projectionMatrix;

    QOpenGLShaderProgram m_program;
    QOpenGLShaderProgram m_programSkybox;

    QOpenGLTexture *m_texture;

    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

    QVector2D m_mousePosition;

    QQuaternion m_rotations;

    QBasicTimer m_timer;
};

#endif // GLWIDGET_H
