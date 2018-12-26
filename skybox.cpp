#include "skybox.h"
#include "simpleobject3d.h"
#include "material.h"
//#include "material.h"

SkyBox::SkyBox(float width, const QImage &texture)
{
    float width_diw_2 = width / 2.0f;
    QVector<VertexData > vertexes;
    QVector<QVector3D> normal;
    {
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    normal.append(-average_sum_3_vectors(QVector3D(0.0, 0.0, -1.0), QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    }
    // Позади
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2),   QVector2D(1.0f,  2.0f/3.0f), normal[0]/*QVector3D(0.0, 0.0, 1.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2),  QVector2D(1.0f,  1.0f/3.0f), normal[1]/*QVector3D(0.0, 0.0, 1.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2),    QVector2D(0.75f, 2.0f/3.0f), normal[2]/*QVector3D(0.0, 0.0, 1.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2),   QVector2D(0.75f, 1.0f/3.0f), normal[3]/*QVector3D(0.0, 0.0, 1.0)*/));
    // Справа
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2),    QVector2D(0.75f, 2.0f/3.0f), normal[2]/*QVector3D(1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2),   QVector2D(0.75f, 1.0f/3.0f), normal[3]/*QVector3D(1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2),   QVector2D(0.5f,  2.0f/3.0f), normal[4]/*QVector3D(1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2),  QVector2D(0.5f,  1.0f/3.0f), normal[5]/*QVector3D(1.0, 0.0, 0.0)*/));
    // Над нами
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, width_diw_2),    QVector2D(0.5f,  1.0f     ), normal[2]/*QVector3D(0.0, 1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2),   QVector2D(0.5f,  2.0f/3.0f), normal[4]/*QVector3D(0.0, 1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2),   QVector2D(0.25f, 1.0f     ), normal[0]/*QVector3D(0.0, 1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2),  QVector2D(0.25f, 2.0f/3.0f), normal[6]/*QVector3D(0.0, 1.0, 0.0)*/));
    // Перед нами
    vertexes.append(VertexData(QVector3D(width_diw_2, width_diw_2, -width_diw_2),   QVector2D(0.5f,  2.0f/3.0f), normal[4]/*QVector3D(0.0, 0.0, -1.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2),  QVector2D(0.5f,  1.0f/3.0f), normal[5]/*QVector3D(0.0, 0.0, -1.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2),  QVector2D(0.25f, 2.0f/3.0f), normal[6]/*QVector3D(0.0, 0.0, -1.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(0.25f, 1.0f/3.0f), normal[7]/*QVector3D(0.0, 0.0, -1.0)*/));
    // Слева
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, width_diw_2),   QVector2D(0.0f,  2.0f/3.0f), normal[0]/*QVector3D(-1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, width_diw_2, -width_diw_2),  QVector2D(0.25f, 2.0f/3.0f), normal[6]/*QVector3D(-1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2),  QVector2D(0.0f,  1.0f/3.0f), normal[1]/*QVector3D(-1.0, 0.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(0.25f, 1.0f/3.0f), normal[7]/*QVector3D(-1.0, 0.0, 0.0)*/));
    // Под нами
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, width_diw_2),  QVector2D(0.25f, 0.0f     ), normal[1]/*QVector3D(0.0, -1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(-width_diw_2, -width_diw_2, -width_diw_2), QVector2D(0.25f, 1.0f/3.0f), normal[7]/*QVector3D(0.0, -1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, width_diw_2),   QVector2D(0.5f,  0.0f     ), normal[3]/*QVector3D(0.0, -1.0, 0.0)*/));
    vertexes.append(VertexData(QVector3D(width_diw_2, -width_diw_2, -width_diw_2),  QVector2D(0.5f,  1.0f/3.0f), normal[5]/*QVector3D(0.0, -1.0, 0.0)*/));

    QVector<GLuint> indexes;
    for(int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 2);
        indexes.append(i + 1);

        indexes.append(i + 2);
        indexes.append(i + 3);
        indexes.append(i + 1);
    }


    Material *newMtl = new Material;
    newMtl->setDiffuseMap(texture);
    newMtl->setShininess(96);
    newMtl->setDiffuseColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setAmbienceColor(QVector3D(1.0, 1.0, 1.0));
    newMtl->setSpecularColor(QVector3D(1.0, 1.0, 1.0));  
    newMtl->setTransparency(1.0);

    m_cube = new SimpleObject3D(vertexes, indexes, newMtl);

}

SkyBox::~SkyBox()
{
    delete m_cube;
}

void SkyBox::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    m_cube->draw(program, functions);
}

void SkyBox::rotate(const QQuaternion &r)
{
    (void)r;
}

void SkyBox::translate(const QVector3D &t)
{
    (void)t;
}

void SkyBox::scale(const float &s)
{
    (void)s;
}

void SkyBox::setGlobalTransform(const QMatrix4x4 &g)
{
    (void)&g;
}

QVector3D SkyBox::average_sum_3_vectors(QVector3D v1, QVector3D v2, QVector3D v3)
{
    float x = (v1.x() + v2.x() + v3.x()) ;
    float y = (v1.y() + v2.y() + v3.y()) ;
    float z = (v1.z() + v2.z() + v3.z()) ;
    return QVector3D(x * 0.33333f, y * 0.33333f, z * 0.33333f).normalized();
}
