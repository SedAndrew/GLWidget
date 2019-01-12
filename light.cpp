#include "light.h"
#include <QtMath>

Light::Light(const Type &type) :
    m_ambienceColor(1.0f, 1.0f, 1.0f),
    m_diffuseColor(1.0f, 1.0f, 1.0f),
    m_specularColor(1.0f, 1.0f, 1.0f),
    m_positon(0.0f, 0.0f, -10.0f, 1.0f),
    m_direction(0.0f, 0.0f, -1.0f, 0.0f),
    m_cutoff(M_PI_2),
    m_type(type)
{
    m_litghtMatrix.setToIdentity();
    m_litghtMatrix.lookAt(m_positon.toVector3D(),
                          (m_positon + m_direction).toVector3D(),
                          QVector3D(m_direction.x(), m_direction.z(), -m_direction.y()));
}

void Light::setAmbienceColor(const QVector3D &ambienceColor)
{
    m_ambienceColor = ambienceColor;
}

const QVector3D &Light::getAmbienceColor() const
{
    return m_ambienceColor;
}

void Light::setDiffuseColor(const QVector3D &diffuseColor)
{
    m_diffuseColor = diffuseColor;
}

const QVector3D &Light::getDiffuseColor() const
{
    return m_diffuseColor;
}

void Light::setSpecularColor(const QVector3D &specularColor)
{
    m_specularColor = specularColor;
}

const QVector3D &Light::getSpecularColor() const
{
    return m_specularColor;
}

void Light::setPosition(const QVector4D &position)
{
    m_positon = position;
    m_litghtMatrix.setToIdentity();
    m_litghtMatrix.lookAt(m_positon.toVector3D(),
                          (m_positon + m_direction).toVector3D(),
                          QVector3D(m_direction.x(), m_direction.z(), -m_direction.y()));
}

const QVector4D &Light::getPosition() const
{
    return m_positon;
}

void Light::setDirection(const QVector4D &direction)
{
    m_direction = direction.normalized();
    m_litghtMatrix.setToIdentity();
    m_litghtMatrix.lookAt(m_positon.toVector3D(),
                          (m_positon + m_direction).toVector3D(),
                          QVector3D(m_direction.x(), m_direction.z(), -m_direction.y()));
}

const QVector4D &Light::getDirection() const
{
    return m_direction;
}

void Light::setCutoff(const float &cutoff)
{
    m_cutoff = cutoff;
}

const float &Light::getCutoff() const
{
    return m_cutoff;
}

void Light::setType(const Type &type)
{
    m_type = type;
}

const Type &Light::getType() const
{
    return m_type;
}

const QMatrix4x4 &Light::getLightMatrix() const
{
    return m_litghtMatrix;
}


