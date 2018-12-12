#include "glwidget.h"

GLwidget::GLwidget(QWidget *parent) :
    QOpenGLWidget(parent), m_texture(0), m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}

GLwidget::~GLwidget()
{

}
void GLwidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST); //буффер глубины
    glEnable(GL_CULL_FACE); //отсечение задних граней

    initShaders();
    initCube(1.1f);
}

void GLwidget::resizeGL(int w, int h)
{
    float aspect = w / (h ? (float)h : 1);
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 1000.0f);
}

void GLwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0, 0.0, -5.0);
    modelViewMatrix.rotate(30, 1.0, 0.0, 0.0);
    modelViewMatrix.rotate(30, 0.0, 1.0, 0.0);

    m_texture->bind(0);

    m_program.bind();
    m_program.setUniformValue("qt_ModelViewProjectionMatrix", m_projectionMatrix * modelViewMatrix);
    m_program.setUniformValue("qt_TexCoord0", 0);

    m_arrayBuffer.bind();

    int offset = 0;

    int vertLoc = m_program.attributeLocation("qt_Vertex");

    m_program.enableAttributeArray(vertLoc);
    m_program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int textLoc =  m_program.attributeLocation("qt_MultiTexCoord0");
    m_program.enableAttributeArray(textLoc);
    m_program.setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    m_indexBuffer.bind();

    // Отрисовка
    // тип примитовов отрисовки, количестов элементов для отрисовки, тип, массив на индексы
    glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
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

    m_rotations = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotations;
    //m_camera->rotate(QQuaternion::fromAxisAndAngle(axis, angle));

    update();
}

void GLwidget::wheelEvent(QWheelEvent *event)
{/*
    if ( event->delta() > 0) {
        m_camera->translate(QVector3D(0.0f, 0.0f, 0.25f));
    }
    else if (event->delta() < 0) {
        m_camera->translate(QVector3D(0.0f, 0.0f, -0.25f));
    }
    update();*/
}

void GLwidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
}

void GLwidget::keyPressEvent(QKeyEvent *event)
{
}

void GLwidget::initShaders()
{
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
        close();

    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh")) // (пиксельный) фрагментный шейдер
        close();

    if(!m_program.link()) // объединение шейдеров
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

/*
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
*/
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

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData)); // 1. 2. количество в байтах
    m_arrayBuffer.release(); // освобождение буффера на время пока не понадобится

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage(":/cube5.png").mirrored()); // отраженная по вертикале текстура

    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);

    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

    m_texture->setWrapMode(QOpenGLTexture::Repeat);
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
