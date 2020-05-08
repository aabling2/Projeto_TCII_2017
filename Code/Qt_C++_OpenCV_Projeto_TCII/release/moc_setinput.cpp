/****************************************************************************
** Meta object code from reading C++ file 'setinput.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../setinput.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setinput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SetInput_t {
    QByteArrayData data[8];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetInput_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetInput_t qt_meta_stringdata_SetInput = {
    {
QT_MOC_LITERAL(0, 0, 8), // "SetInput"
QT_MOC_LITERAL(1, 9, 19), // "on_bot_cam1_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "on_bot_cam2_clicked"
QT_MOC_LITERAL(4, 50, 19), // "on_bot_vid1_clicked"
QT_MOC_LITERAL(5, 70, 19), // "on_bot_vid2_clicked"
QT_MOC_LITERAL(6, 90, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 112, 21) // "on_buttonBox_rejected"

    },
    "SetInput\0on_bot_cam1_clicked\0\0"
    "on_bot_cam2_clicked\0on_bot_vid1_clicked\0"
    "on_bot_vid2_clicked\0on_pushButton_clicked\0"
    "on_buttonBox_rejected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetInput[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SetInput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetInput *_t = static_cast<SetInput *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_bot_cam1_clicked(); break;
        case 1: _t->on_bot_cam2_clicked(); break;
        case 2: _t->on_bot_vid1_clicked(); break;
        case 3: _t->on_bot_vid2_clicked(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_buttonBox_rejected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SetInput::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetInput.data,
      qt_meta_data_SetInput,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SetInput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetInput::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SetInput.stringdata0))
        return static_cast<void*>(const_cast< SetInput*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetInput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
