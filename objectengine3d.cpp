#include "objectengine3d.h"
#include <QFile>
#include <QFileInfo>

ObjectEngine3D::ObjectEngine3D()
{

}

void ObjectEngine3D::loadObjectFromFile(const QString &filename)
{
    QFile objFile(filename);
    if (!objFile.exists()) {
        qDebug() << "File not found";
        return;
    }

    objFile.open(QIODevice::ReadOnly);
    QTextStream input(&objFile);

    QVector<QVector3D > coords;
    QVector<QVector2D > texCoords;
    QVector<QVector3D > normals;

    QVector<VertexData > vertexes;
    QVector<GLuint > indexes;
    SimpleObject3D *object = 0;
    QString mtlName;

    while (!input.atEnd()) {
        QString str = input.readLine();
        QStringList list = str.split(" ");
        if (list[0] == "#") {
            qDebug() << "This is comment: " << str;
            continue;
        } else if (list[0] == "mtllib") {
            QFileInfo info(filename);
            m_materialLibrary.loadMaterialsFromFile(QString("%1/%2").arg(info.absolutePath()).arg(list[1]));
            qDebug() << "File with materils: " << str;
        } else if (list[0] == "v") {     // вершинные координаты
            coords.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        } else if (list[0] == "vt") {    // текстурные координаты
            texCoords.append(QVector2D(list[1].toFloat(), list[2].toFloat()));
            continue;
        } else if (list[0] == "vn") {    // координаты нормали
            normals.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        } else if (list[0] == "f") {     // полигоны
            for (int i = 1; i <= 3; i++) {
                QStringList vert = list[i].split("/"); // индексы
                vertexes.append(VertexData(coords[vert[0].toLong() - 1], texCoords[vert[1].toLong() - 1], normals[vert[2].toLong() - 1]));
                indexes.append(indexes.size());
            }
            continue;
        } else if (list[0] == "usemtl") {
            if (object) {
                calculateTBN(vertexes);
                object->init(vertexes, indexes, m_materialLibrary.getMaterial(mtlName)); //QImage(list[1]));
            }
            mtlName = list[1];
            addObject(object);
            object = new SimpleObject3D;
            vertexes.clear();
            indexes.clear();
        }
    }
    if (object) {
        calculateTBN(vertexes);
        object->init(vertexes, indexes, m_materialLibrary.getMaterial(mtlName)); //QImage(list[1]));
    }
/*
    if (object) {
//        calculateTBN(vertexes);
        object->init(vertexes, indexes, QImage(mtlName));
    }
    */
    addObject(object);
    objFile.close();
}

void ObjectEngine3D::addObject(SimpleObject3D *object)
{
    if (!object) return;

    for (int i = 0; i < m_objects.size(); i++)
        if (m_objects[i] == object)
            return;

    m_objects.append(object);
}

SimpleObject3D *ObjectEngine3D::getObject(quint32 index)
{
    if (index < (quint32)m_objects.size())
        return m_objects[index];
    else
        return 0;

}

void ObjectEngine3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    for (int i = 0; i < m_objects.size(); i++)
        m_objects[i]->draw(program, functions);
}

void ObjectEngine3D::rotate(const QQuaternion &r)
{
    for (int i = 0; i < m_objects.size(); i++)
        m_objects[i]->rotate(r);
}

void ObjectEngine3D::translate(const QVector3D &t)
{
    for (int i = 0; i < m_objects.size(); i++)
        m_objects[i]->translate(t);
}

void ObjectEngine3D::scale(const float &s)
{
    for (int i = 0; i < m_objects.size(); i++)
        m_objects[i]->scale(s);
}

void ObjectEngine3D::setGlobalTransform(const QMatrix4x4 &g)
{
    for (int i = 0; i < m_objects.size(); i++)
        m_objects[i]->setGlobalTransform(g);
}

void ObjectEngine3D::calculateTBN(QVector<VertexData> &vertData)
{
    for (int i = 0; i < vertData.size(); i += 3) {
        QVector3D &v1 = vertData[i].position;
        QVector3D &v2 = vertData[i+1].position;
        QVector3D &v3 = vertData[i+2].position;

        QVector2D &uv1 = vertData[i].textCoord;
        QVector2D &uv2 = vertData[i+1].textCoord;
        QVector2D &uv3 = vertData[i+2].textCoord;

        // deltaPos1 = deltaUV1.x * T + deltaUV1.y * B;
        // deltaPos2 = deltaUV2.x * T + deltaUV2.y * B;

        QVector3D deltaPos1 = v2 - v1;
        QVector3D deltaPos2 = v3 - v1;


        QVector2D deltaUV1 = uv2 - uv1;
        QVector2D deltaUV2 = uv3 - uv1;

        float r = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());
        QVector3D tangent = (deltaPos1 * deltaUV2.y() - deltaPos2 * deltaUV1.y()) * r;
        QVector3D bitangent = (deltaPos2 * deltaUV1.x() - deltaPos1 * deltaUV2.x()) * r;

        vertData[i].tangent = tangent;
        vertData[i+1].tangent = tangent;
        vertData[i+2].tangent = tangent;

        vertData[i].bitangent = bitangent;
        vertData[i+1].bitangent = bitangent;
        vertData[i+2].bitangent = bitangent;
    }
}
