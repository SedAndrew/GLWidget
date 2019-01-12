/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[13];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "setNewLight"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "Type&"
QT_MOC_LITERAL(4, 30, 4), // "type"
QT_MOC_LITERAL(5, 35, 28), // "on_actionOpen_file_triggered"
QT_MOC_LITERAL(6, 64, 32), // "on_checkBox_transparency_clicked"
QT_MOC_LITERAL(7, 97, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(8, 130, 5), // "value"
QT_MOC_LITERAL(9, 136, 25), // "on_checkBox_light_clicked"
QT_MOC_LITERAL(10, 162, 34), // "on_checkBox_directionLight_cl..."
QT_MOC_LITERAL(11, 197, 30), // "on_checkBox_pointLight_clicked"
QT_MOC_LITERAL(12, 228, 29) // "on_checkBox_spotLight_clicked"

    },
    "MainWindow\0setNewLight\0\0Type&\0type\0"
    "on_actionOpen_file_triggered\0"
    "on_checkBox_transparency_clicked\0"
    "on_horizontalSlider_valueChanged\0value\0"
    "on_checkBox_light_clicked\0"
    "on_checkBox_directionLight_clicked\0"
    "on_checkBox_pointLight_clicked\0"
    "on_checkBox_spotLight_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setNewLight((*reinterpret_cast< Type(*)>(_a[1]))); break;
        case 1: _t->on_actionOpen_file_triggered(); break;
        case 2: _t->on_checkBox_transparency_clicked(); break;
        case 3: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_checkBox_light_clicked(); break;
        case 5: _t->on_checkBox_directionLight_clicked(); break;
        case 6: _t->on_checkBox_pointLight_clicked(); break;
        case 7: _t->on_checkBox_spotLight_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(Type & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::setNewLight)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::setNewLight(Type & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
