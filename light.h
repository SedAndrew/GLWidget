#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include "global.h"

class Light
{
public:
//    enum Type
//    {
//        Directional,
//        Point,
//        Spot
//    };

    Light(const Type &type = Directional);

    void setAmbienceColor(const QVector3D &ambienceColor);
    const QVector3D &getAmbienceColor() const;
    void setDiffuseColor(const QVector3D &diffuseColor);
    const QVector3D &getDiffuseColor() const;
    void setSpecularColor(const QVector3D &specularColor);
    const QVector3D &getSpecularColor() const;
    void setPosition(const QVector4D &position);
    const QVector4D &getPosition() const;
    void setDirection(const QVector4D &direction);
    const QVector4D &getDirection() const;
    void setCutoff(const float &cutoff);
    const float &getCutoff() const;
    void setType(const Type &type);
    const Type &getType() const;
    const QMatrix4x4 &getLightMatrix() const;

private:
    QVector3D m_ambienceColor;
    QVector3D m_diffuseColor;
    QVector3D m_specularColor;
    QVector4D m_positon;
    QVector4D m_direction;
    float m_cutoff; // половина угла в вершине конуса
    Type m_type;
    QMatrix4x4 m_litghtMatrix;
};

#endif // LIGHT_H
