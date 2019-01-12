#ifndef LIGTHWIDGET_H
#define LIGTHWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include "global.h"

class LightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LightWidget(QWidget *parent = 0);

signals:
    setNewLight(Type type);

public slots:

};

#endif // LIGTHWIDGET_H
