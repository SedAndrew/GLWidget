#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QMouseEvent>
#include <QFileInfo>
#include <QtMath>
#include "glwidget.h"
#include "group3d.h"
#include <objectengine3d.h>
#include "camera3d.h"
#include "skybox.h"
#include "material.h"

GLwidget::GLwidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    m_camera = new Camera3D;
    m_camera->translate(QVector3D(0.0f, 0.0f, -10.0f));
    m_fbHeight = 1024;
    m_fbWidth = 1024;
    m_projectionLightMatrix.setToIdentity();
    m_projectionLightMatrix.ortho(-40, 40, -40, 40, -40, 40); // ортогональная

    m_lightRotateX = 30;
    m_lightRotateY = 40;

    m_shadowLightMatrix.setToIdentity();
    m_shadowLightMatrix.rotate(m_lightRotateX, 1.0, 0.0, 0.0); // 1-угол поворота, 2-ось
    m_shadowLightMatrix.rotate(m_lightRotateY, 0.0, 1.0, 0.0);

    m_lightMatrix.setToIdentity();
    m_lightMatrix.rotate(-m_lightRotateY, 0.0, 1.0, 0.0);
    m_lightMatrix.rotate(-m_lightRotateX, 1.0, 0.0, 0.0);
}

GLwidget::~GLwidget()
{
    delete m_camera;

    for (int i = 0; i < m_objects.size(); i++) {
        delete m_objects[i];
    }
    for (int i = 0; i < m_groups.size(); i++) {
        delete m_groups[i];
    }
}

void GLwidget::initializeGL()
{
    //initializeOpenGLFunctions();
    glClearColor(0.02f, 0.03f, 0.1f, 1.0f);

    glEnable(GL_DEPTH_TEST); //буффер глубины
    glEnable(GL_CULL_FACE); //отсечение задних граней

    initShaders();

    float step = 2.0f;

    /*
    m_groups.append(new Group3D);
    initCristal(0.65f, 2.6f);
//    initCristal(0.40f, 2.0f);
//   initCube(1.0f);
    m_groups[m_groups.size() - 1]->addObject(m_objects[m_objects.size() - 1]);
    m_transformObjects.append(m_groups[0]);
    */

    m_groups.append(new Group3D);
    for (float x = -step; x <= step; x += step) {
        for (float y = -step; y <= step; y += step) {
            for (float z = -step; z <= step; z += step) {
                initCube(1.0f);
                m_objects[m_objects.size() - 1]->translate(QVector3D(x, y, z));
                m_groups[m_groups.size() - 1]->addObject(m_objects[m_objects.size() - 1]);
            }
        }
    }
    m_groups[0]->translate(QVector3D(-8.0f, 0.0f, 0.0f));

    m_groups.append(new Group3D);
    for (float x = -step; x <= step; x += step) {
        for (float y = -step; y <= step; y += step) {
            for (float z = -step; z <= step; z += step) {
//                initCube(1.0f);
                initCristal(0.65f, 2.6f);
                m_objects[m_objects.size() - 1]->translate(QVector3D(x, y, z));
                m_groups[m_groups.size() - 1]->addObject(m_objects[m_objects.size() - 1]);
            }
        }
    }
    m_groups[1]->translate(QVector3D(8.0f, 0.0f, 0.0f));

    m_groups.append(new Group3D);
    m_groups[2]->addObject(m_groups[0]);
    m_groups[2]->addObject(m_groups[1]);

    m_transformObjects.append(m_groups[2]);

    m_objects.append(new ObjectEngine3D);
    m_objects[m_objects.size() - 1]->loadObjectFromFile(":/BB8 New/bb9.obj"); //:/mtl_monkey.obj");
    m_objects[m_objects.size() - 1]->translate(QVector3D(0.0f, 0.0f, 0.0f));
    m_transformObjects.append(m_objects[m_objects.size() - 1]);

    //m_groups[0]->addObject(m_camera);

    m_skybox = new SkyBox(100, QImage(":/skybox7.png"));

    m_depthBuffer = new QOpenGLFramebufferObject(m_fbWidth, m_fbHeight, QOpenGLFramebufferObject::Depth);

    m_timer.start(30, this);
}

void GLwidget::resizeGL(int w, int h)
{
    float aspect = w / (h ? (float)h : 1);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 1000.0f);
}

void GLwidget::paintGL()
{
    // во фрейм буффер
    m_depthBuffer->bind();
    context()->functions()->glViewport(0, 0, m_fbWidth, m_fbHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_programDepth.bind();
    m_programDepth.setUniformValue("u_projectionLightMatrix", m_projectionLightMatrix);
    m_programDepth.setUniformValue("u_shadowLightMatrix", m_shadowLightMatrix);

    for (int i = 0; i < m_transformObjects.size(); i++){
        m_transformObjects[i]->draw(&m_programDepth, context()->functions());
    }
    m_programDepth.release();
    m_depthBuffer->release();

    GLuint texture = m_depthBuffer->texture();

    context()->functions()->glActiveTexture(GL_TEXTURE4);
    context()->functions()->glBindTexture(GL_TEXTURE_2D, texture);

    // на экран
    context()->functions()->glViewport(0, 0, QWidget::width(), QWidget::height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 1. буффер цвета; 2. буффер глубины

    m_programSkybox.bind();
    m_programSkybox.setUniformValue("u_projectionMatrix", m_projectionMatrix);

    m_camera->draw(&m_programSkybox);
    m_skybox->draw(&m_programSkybox, context()->functions());
    m_programSkybox.release();

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_program.setUniformValue("u_lightPosition", QVector4D(4.0, 4.0, 4.0, 1.0));
    m_program.setUniformValue("u_lightPower", 1.4f);

    m_camera->draw(&m_program);
    for (int i = 0; i < m_transformObjects.size(); i++){
        m_transformObjects[i]->draw(&m_program, context()->functions());
    }
    m_program.release();
}

void GLwidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton){
        m_mousePosition = QVector2D(event->localPos());
    }
    event->accept(); // пожтверждение срабатывания event
}

void GLwidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) return;

    // вектор направления diff
    QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());

    float angle = diff.length() / 2.0;
    // вектор вокруг которого будет совершаться поворот
    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

    m_camera->rotate(QQuaternion::fromAxisAndAngle(axis, angle));

    update();
}

void GLwidget::wheelEvent(QWheelEvent *event)
{
    if ( event->delta() > 0) {
        m_camera->translate(QVector3D(0.0f, 0.0f, 0.25f));
    }
    else if (event->delta() < 0) {
        m_camera->translate(QVector3D(0.0f, 0.0f, -0.25f));
    }
    update();
}

void GLwidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    for (int i = 0; i < m_objects.size()-1; i++){
        if ( i%2 == 0 ) {
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qSin(angleObject)));
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, qCos(angleObject)));
        } else {
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, qSin(angleObject)));
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qCos(angleObject)));
        }
    }

    m_groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, qSin(angleGroup1)));
    m_groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, -qSin(angleGroup1)));

    m_groups[1]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qCos(angleGroup2)));
    m_groups[1]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, -qCos(angleGroup2)));

    m_groups[2]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qSin(angleMain)));
    m_groups[2]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, qCos(angleMain)));

    angleObject += M_PI / 180.0f;
    angleGroup1 += M_PI / 360.0f;
    angleGroup2+= M_PI / 360.0f;
    angleMain += M_PI / 720.0f;

    update();
}

void GLwidget::keyPressEvent(QKeyEvent *event)
{

    switch (event->key()) {
    case Qt::Key_Left:
        m_groups[0]->delObject(m_camera);
        m_groups[1]->addObject(m_camera);
        break;
    case Qt::Key_Right:
        m_groups[1]->delObject(m_camera);
        m_groups[0]->addObject(m_camera);
        break;
    case Qt::Key_Down:
        m_groups[0]->delObject(m_camera);
        m_groups[1]->delObject(m_camera);
        break;
    case Qt::Key_Up:
        m_groups[0]->delObject(m_camera);
        m_groups[1]->delObject(m_camera);
        QMatrix4x4 tmp; // центровка
        tmp.setToIdentity();
        m_camera->setGlobalTransform(tmp);
        break;
    }
    update();
}

void GLwidget::initShaders()
{
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
        close();

    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
        close();

    if(!m_program.link())
        close();

    if(!m_programSkybox.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/skybox.vsh"))
        close();

    if(!m_programSkybox.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/skybox.fsh"))
        close();

    if(!m_programSkybox.link())
        close();

    if(!m_programDepth.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/depth.vsh"))
        close();

    if(!m_programDepth.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/depth.fsh"))
        close();

    if(!m_programDepth.link())
        close();
}

void GLwidget::initCube(float width)
{
    float width_diw_2 = width / 2.0f;
    QVector<VertexData > vertexes;
    QVector<QVector3D> normal;
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), normal[0]/*QVector3D(0.0, 0.0, 1.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2), QVector2D(0.0, 0.0), normal[1]/*QVector3D(0.0, 0.0, 1.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2), QVector2D(1.0, 1.0), normal[2]/*QVector3D(0.0, 0.0, 1.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2), QVector2D(1.0, 0.0), normal[3]/*QVector3D(0.0, 0.0, 1.0)*/));

    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), normal[2]/*QVector3D(1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2), QVector2D(0.0, 0.0), normal[3]/*QVector3D(1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2), QVector2D(1.0, 1.0), normal[4]/*QVector3D(1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), normal[5]/*QVector3D(1.0, 0.0, 0.0)*/));

    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), normal[2]/*QVector3D(0.0, 1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), normal[4]/*QVector3D(0.0, 1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2), QVector2D(1.0, 1.0), normal[0]/*QVector3D(0.0, 1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), normal[6]/*QVector3D(0.0, 1.0, 0.0)*/));

    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2), QVector2D(0.0, 1.0), normal[4]/*QVector3D(0.0, 0.0, -1.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), normal[5]/*QVector3D(0.0, 0.0, -1.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2), QVector2D(1.0, 1.0), normal[6]/*QVector3D(0.0, 0.0, -1.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), normal[7]/*QVector3D(0.0, 0.0, -1.0)*/));

    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), normal[0]/*QVector3D(-1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), normal[6]/*QVector3D(-1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2), QVector2D(1.0, 1.0), normal[1]/*QVector3D(-1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), normal[7]/*QVector3D(-1.0, 0.0, 0.0)*/));

    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2), QVector2D(0.0, 1.0), normal[1]/*QVector3D(0.0, -1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), normal[7]/*QVector3D(0.0, -1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2), QVector2D(1.0, 1.0), normal[3]/*QVector3D(0.0, -1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), normal[5]/*QVector3D(0.0, -1.0, 0.0)*/));

    // создаем массив индексов
    QVector<GLuint> indexes;
    for(int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    Material *newMtl = new Material;
    newMtl->setDiffuseMap(":/cube5.png");
    newMtl->setNormalMap(":/BB8 New/normal.jpg");
    newMtl->setShininess(96.0);
    newMtl->setDiffuseColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setAmbienceColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setSpecularColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setTransparency(1.0);

    ObjectEngine3D *newObj = new ObjectEngine3D;
    newObj->calculateTBN(vertexes);
    newObj->addObject(new SimpleObject3D(vertexes, indexes, newMtl));

    m_objects.append(newObj);
}

void GLwidget::initCristal(float underside, float height)
{
    float height_diw_2 = height / 2.0f;
    float hTriangle = sqrt(0.75f * underside * underside);
    QVector<VertexData > vertexes; // вершины
    QVector<QVector3D > normal; // нормаль вершины
    QVector<QVector<QVector3D > > face_n; // нормаль граней
    QVector<QVector3D> array_vectors; // массив векторов

    // верхняя пирамида
    /*//////////////////////////////////////////////////////////////////////////////////////////*/
    QVector3D vec1(-underside / 2.0f,   -height_diw_2,  hTriangle);
    QVector3D vec2( underside,          0.0f         ,  0.0f);
    QVector3D vec3(-underside / 2.0f,   height_diw_2 , -hTriangle);
    float alpha = 0.0f;

    for(int i = 0; i < 6; i++){
        vec1.setX(vec1.x() * cos(alpha) + vec1.z() * sin(alpha));
        vec1.setZ(-vec1.x() * sin(alpha) + vec1.z() * cos(alpha));

        vec2.setX(vec2.x() * cos(alpha) + vec2.z() * sin(alpha));
        vec2.setZ(-vec2.x() * sin(alpha) + vec2.z() * cos(alpha));

        vec3.setX(vec3.x() * cos(alpha) + vec3.z() * sin(alpha));
        vec3.setZ(-vec3.x() * sin(alpha) + vec3.z() * cos(alpha));

        array_vectors.append(vec1);
        array_vectors.append(vec2);
        array_vectors.append(vec3);

        alpha += M_PI / 3.0f;
    }


    face_n.reserve(12);
    for(int i = 0; i < 6; i++) {
        QVector<QVector3D> temp;
        temp.append(-QVector3D::normal(-array_vectors[0], array_vectors[1]));
        temp.append(-QVector3D::normal(-array_vectors[1], array_vectors[2]));
        temp.append( QVector3D::normal( array_vectors[0],-array_vectors[2]));
        face_n.push_back(temp);
        array_vectors.pop_front();
        array_vectors.pop_front();
        array_vectors.pop_front();
    }
    // нижняя пирамида
    /*//////////////////////////////////////////////////////////////////////////////////////*/

    QVector3D vec4(-underside / 2.0f,  height_diw_2,   hTriangle);
    QVector3D vec5( underside       ,  0.0f         ,  0.0f);
    QVector3D vec6(-underside / 2.0f, -height_diw_2 , -hTriangle);
    alpha = 0.0f;

    for(int i = 0; i < 6; i++){
        vec4.setX(vec4.x() * cos(alpha) + vec4.z() * sin(alpha));
        vec4.setZ(-vec4.x() * sin(alpha) + vec4.z() * cos(alpha));

        vec5.setX(vec5.x() * cos(alpha) + vec5.z() * sin(alpha));
        vec5.setZ(-vec5.x() * sin(alpha) + vec5.z() * cos(alpha));

        vec6.setX(vec6.x() * cos(alpha) + vec6.z() * sin(alpha));
        vec6.setZ(-vec6.x() * sin(alpha) + vec6.z() * cos(alpha));

        array_vectors.append(vec4);
        array_vectors.append(vec5);
        array_vectors.append(vec6);

        alpha += M_PI / 3.0f;
    }

    for(int i = 6; i < 12; i++) {
        QVector<QVector3D> temp;
        temp.append(-QVector3D::normal(-array_vectors[0], array_vectors[1]));
        temp.append(-QVector3D::normal(-array_vectors[1], array_vectors[2]));
        temp.append(-QVector3D::normal(array_vectors[0], -array_vectors[2]));
        face_n.push_back(temp);
        array_vectors.pop_front();
        array_vectors.pop_front();
        array_vectors.pop_front();
    }

    normal.append(QVector3D(average_sum_6_vectors(face_n[0][2], face_n[1][2], face_n[2][2], face_n[3][2], face_n[4][2], face_n[5][2])));
    normal.append(QVector3D(average_sum_4_vectors(face_n[0][0], face_n[5][1], face_n[6][1],  face_n[11][0])));
    normal.append(QVector3D(average_sum_4_vectors(face_n[1][0], face_n[0][1], face_n[7][1],  face_n[6][0])));
    normal.append(QVector3D(average_sum_4_vectors(face_n[2][0], face_n[1][1], face_n[8][1],  face_n[7][0])));
    normal.append(QVector3D(average_sum_4_vectors(face_n[3][0], face_n[2][1], face_n[9][1],  face_n[8][0])));
    normal.append(QVector3D(average_sum_4_vectors(face_n[4][0], face_n[3][1], face_n[10][1], face_n[9][0])));
    normal.append(QVector3D(average_sum_4_vectors(face_n[5][0], face_n[4][1], face_n[11][1], face_n[10][0])));
    normal.append(QVector3D(average_sum_6_vectors(face_n[6][2], face_n[7][2], face_n[8][2], face_n[9][2], face_n[10][2], face_n[11][2])));
/* Инициализая полигонов */

    QVector3D ver_val1(0.0f, height_diw_2, 0.0f);
    QVector3D ver_val2(-underside / 2.0f, 0.0f, hTriangle);
    QVector3D ver_val3(underside / 2.0f, 0.0f, hTriangle);
    alpha = 0.0f;
    for(int i = 0; i < 6; i++){
        QVector3D temp1 = ver_val2;
        temp1.setX(ver_val2.x() * qCos(alpha) + ver_val2.z() * qSin(alpha));
        temp1.setZ(-ver_val2.x() * qSin(alpha) + ver_val2.z() * qCos(alpha));

        QVector3D temp2 = ver_val3;
        temp2.setX(ver_val3.x() * qCos(alpha) + ver_val3.z() * qSin(alpha));
        temp2.setZ(-ver_val3.x() * qSin(alpha) + ver_val3.z() * qCos(alpha));

        vertexes.append(VertexData(ver_val1, QVector2D(0.5, 1.0), normal[0]));
        vertexes.append(VertexData(temp1, QVector2D(0.0, 0.0), normal[i + 1]));
        vertexes.append(VertexData(temp2, QVector2D(1.0, 0.0), normal[(i == 5) ? 1 : i + 2]));

        alpha += M_PI / 3.0f;
    }

    QVector3D ver_val4(0.0f, -height_diw_2, 0.0f);
    QVector3D ver_val5(underside / 2.0f, 0.0f, hTriangle);
    QVector3D ver_val6(-underside / 2.0f, 0.0f, hTriangle);
    alpha = 0.0f;
    for(int i = 0; i < 6; i++){
        QVector3D temp1 = ver_val5;
        temp1.setX(ver_val5.x() * qCos(alpha) + ver_val5.z() * qSin(alpha));
        temp1.setZ(-ver_val5.x() * qSin(alpha) + ver_val5.z() * qCos(alpha));

        QVector3D temp2 = ver_val6;
        temp2.setX(ver_val6.x() * qCos(alpha) + ver_val6.z() * qSin(alpha));
        temp2.setZ(-ver_val6.x() * qSin(alpha) + ver_val6.z() * qCos(alpha));

        vertexes.append(VertexData(ver_val4, QVector2D(0.5, 1.0), normal[7]));
        vertexes.append(VertexData(temp1, QVector2D(1.0, 0.0), normal[(i == 5) ? 1 : i + 2]));
        vertexes.append(VertexData(temp2, QVector2D(0.0, 0.0), normal[i + 1]));

        alpha += M_PI / 3.0f;
    }

    QVector<GLuint> indexes;
    for(int i = 0; i < 36; i += 3) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
    }

    Material *newMtl = new Material;
    newMtl->setDiffuseMap(":/sots.png");
//    newMtl->setNormalMap(":/5406-normal.jpg");
    newMtl->setShininess(96);
    newMtl->setDiffuseColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setAmbienceColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setSpecularColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setTransparency(1.0);

    ObjectEngine3D *newObj = new ObjectEngine3D;
//    newObj->calculateTBN(vertexes);
    newObj->addObject(new SimpleObject3D(vertexes, indexes, newMtl));

    m_objects.append(newObj);
}

void GLwidget::addObject(ObjectEngine3D *object)
{
    if (!object) return;

    for (int i = 0; i < m_objects.size(); i++)
        if (m_objects[i] == object)
            return;

    m_objects.append(object);
}

QVector3D GLwidget::average_sum_3_vectors(QVector3D v1, QVector3D v2, QVector3D v3)
{
    float x = (v1.x() + v2.x() + v3.x()) ;
    float y = (v1.y() + v2.y() + v3.y()) ;
    float z = (v1.z() + v2.z() + v3.z()) ;
    return QVector3D(x * 0.33333f, y * 0.33333f, z * 0.33333f).normalized();
}

QVector3D GLwidget::average_sum_4_vectors(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4)
{
    float x = (v1.x() + v2.x() + v3.x() + v4.x()) ;
    float y = (v1.y() + v2.y() + v3.y() + v4.y()) ;
    float z = (v1.z() + v2.z() + v3.z() + v4.z()) ;
    return QVector3D(x * 0.25f, y * 0.25f, z * 0.25f).normalized();
}

QVector3D GLwidget::average_sum_6_vectors(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4, QVector3D v5, QVector3D v6)
{
    float x = (v1.x() + v2.x() + v3.x() + v4.x() + v5.x() + v6.x()) ;
    float y = (v1.y() + v2.y() + v3.y() + v4.y() + v5.y() + v6.y()) ;
    float z = (v1.z() + v2.z() + v3.z() + v4.z() + v5.z() + v6.z()) ;
    return QVector3D(x * 0.166666666f, y * 0.166666666f, z * 0.166666666f).normalized();
}
