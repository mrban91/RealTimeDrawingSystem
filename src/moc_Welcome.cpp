/****************************************************************************
** Meta object code from reading C++ file 'Welcome.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Welcome.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Welcome.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Welcome_t {
    QByteArrayData data[20];
    char stringdata[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Welcome_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Welcome_t qt_meta_stringdata_Welcome = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Welcome"
QT_MOC_LITERAL(1, 8, 12), // "startDrawing"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 14), // "changedROIHand"
QT_MOC_LITERAL(4, 37, 17), // "changedDifference"
QT_MOC_LITERAL(5, 55, 12), // "changedVideo"
QT_MOC_LITERAL(6, 68, 17), // "changedImageClean"
QT_MOC_LITERAL(7, 86, 13), // "cameraOptions"
QT_MOC_LITERAL(8, 100, 8), // "loadFile"
QT_MOC_LITERAL(9, 109, 9), // "playVideo"
QT_MOC_LITERAL(10, 119, 17), // "defaultParameters"
QT_MOC_LITERAL(11, 137, 10), // "enableMenu"
QT_MOC_LITERAL(12, 148, 11), // "restoreMenu"
QT_MOC_LITERAL(13, 160, 12), // "changeDevice"
QT_MOC_LITERAL(14, 173, 12), // "valueChanged"
QT_MOC_LITERAL(15, 186, 12), // "videoPreview"
QT_MOC_LITERAL(16, 199, 10), // "finishDraw"
QT_MOC_LITERAL(17, 210, 14), // "bilinearFilter"
QT_MOC_LITERAL(18, 225, 4), // "save"
QT_MOC_LITERAL(19, 230, 11) // "exitProgram"

    },
    "Welcome\0startDrawing\0\0changedROIHand\0"
    "changedDifference\0changedVideo\0"
    "changedImageClean\0cameraOptions\0"
    "loadFile\0playVideo\0defaultParameters\0"
    "enableMenu\0restoreMenu\0changeDevice\0"
    "valueChanged\0videoPreview\0finishDraw\0"
    "bilinearFilter\0save\0exitProgram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Welcome[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x0a /* Public */,
       4,    0,  106,    2, 0x0a /* Public */,
       5,    0,  107,    2, 0x0a /* Public */,
       6,    0,  108,    2, 0x0a /* Public */,
       7,    0,  109,    2, 0x0a /* Public */,
       8,    0,  110,    2, 0x0a /* Public */,
       9,    0,  111,    2, 0x0a /* Public */,
      10,    0,  112,    2, 0x0a /* Public */,
      11,    0,  113,    2, 0x0a /* Public */,
      12,    0,  114,    2, 0x0a /* Public */,
      13,    0,  115,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    0,  117,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    0,  119,    2, 0x0a /* Public */,
      18,    0,  120,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Welcome::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Welcome *_t = static_cast<Welcome *>(_o);
        switch (_id) {
        case 0: _t->startDrawing(); break;
        case 1: _t->changedROIHand(); break;
        case 2: _t->changedDifference(); break;
        case 3: _t->changedVideo(); break;
        case 4: _t->changedImageClean(); break;
        case 5: _t->cameraOptions(); break;
        case 6: _t->loadFile(); break;
        case 7: _t->playVideo(); break;
        case 8: _t->defaultParameters(); break;
        case 9: _t->enableMenu(); break;
        case 10: _t->restoreMenu(); break;
        case 11: _t->changeDevice(); break;
        case 12: _t->valueChanged(); break;
        case 13: _t->videoPreview(); break;
        case 14: _t->finishDraw(); break;
        case 15: _t->bilinearFilter(); break;
        case 16: _t->save(); break;
        case 17: _t->exitProgram(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Welcome::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Welcome.data,
      qt_meta_data_Welcome,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Welcome::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Welcome::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Welcome.stringdata))
        return static_cast<void*>(const_cast< Welcome*>(this));
    return QDialog::qt_metacast(_clname);
}

int Welcome::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
