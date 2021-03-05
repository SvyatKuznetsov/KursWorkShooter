/****************************************************************************
** Meta object code from reading C++ file 'littleEnemy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../littleEnemy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'littleEnemy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_littleEnemy_t {
    QByteArrayData data[5];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_littleEnemy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_littleEnemy_t qt_meta_stringdata_littleEnemy = {
    {
QT_MOC_LITERAL(0, 0, 11), // "littleEnemy"
QT_MOC_LITERAL(1, 12, 19), // "signalCheckGameOver"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 14), // "signalCheckWin"
QT_MOC_LITERAL(4, 48, 13) // "slotGameTimer"

    },
    "littleEnemy\0signalCheckGameOver\0\0"
    "signalCheckWin\0slotGameTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_littleEnemy[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void littleEnemy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<littleEnemy *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalCheckGameOver(); break;
        case 1: _t->signalCheckWin(); break;
        case 2: _t->slotGameTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (littleEnemy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&littleEnemy::signalCheckGameOver)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (littleEnemy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&littleEnemy::signalCheckWin)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject littleEnemy::staticMetaObject = { {
    &enemy::staticMetaObject,
    qt_meta_stringdata_littleEnemy.data,
    qt_meta_data_littleEnemy,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *littleEnemy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *littleEnemy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_littleEnemy.stringdata0))
        return static_cast<void*>(this);
    return enemy::qt_metacast(_clname);
}

int littleEnemy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = enemy::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void littleEnemy::signalCheckGameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void littleEnemy::signalCheckWin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
