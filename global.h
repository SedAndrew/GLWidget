#ifndef GLOBAL_H
#define GLOBAL_H

enum Type
{
    Directional,
    Point,
    Spot
};


extern bool f_transparency;
extern bool f_spotlights;

extern int m_transparencyPower;

extern Type m_typeLight;

#endif // GLOBAL_H
