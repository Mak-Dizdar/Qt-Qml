/****************************************************************************
** Meta object code from reading C++ file 'sensorboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "sensorboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensorboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SensorBoard_t {
    QByteArrayData data[17];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SensorBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SensorBoard_t qt_meta_stringdata_SensorBoard = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SensorBoard"
QT_MOC_LITERAL(1, 12, 20), // "buttonSwitch1Changed"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "value"
QT_MOC_LITERAL(4, 40, 20), // "buttonSwitch2Changed"
QT_MOC_LITERAL(5, 61, 20), // "temperatureAvailable"
QT_MOC_LITERAL(6, 82, 16), // "cpuLoadAvailable"
QT_MOC_LITERAL(7, 99, 11), // "setGreenLED"
QT_MOC_LITERAL(8, 111, 6), // "active"
QT_MOC_LITERAL(9, 118, 12), // "setOrangeLED"
QT_MOC_LITERAL(10, 131, 9), // "setRedLED"
QT_MOC_LITERAL(11, 141, 8), // "setAlarm"
QT_MOC_LITERAL(12, 150, 11), // "alarmActive"
QT_MOC_LITERAL(13, 162, 20), // "setupSwitch1Notifier"
QT_MOC_LITERAL(14, 183, 20), // "setupSwitch2Notifier"
QT_MOC_LITERAL(15, 204, 24), // "switch1NotifierActivated"
QT_MOC_LITERAL(16, 229, 24) // "switch2NotifierActivated"

    },
    "SensorBoard\0buttonSwitch1Changed\0\0"
    "value\0buttonSwitch2Changed\0"
    "temperatureAvailable\0cpuLoadAvailable\0"
    "setGreenLED\0active\0setOrangeLED\0"
    "setRedLED\0setAlarm\0alarmActive\0"
    "setupSwitch1Notifier\0setupSwitch2Notifier\0"
    "switch1NotifierActivated\0"
    "switch2NotifierActivated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SensorBoard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       5,    1,   80,    2, 0x06 /* Public */,
       6,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   86,    2, 0x0a /* Public */,
       9,    1,   89,    2, 0x0a /* Public */,
      10,    1,   92,    2, 0x0a /* Public */,
      11,    1,   95,    2, 0x0a /* Public */,
      13,    0,   98,    2, 0x08 /* Private */,
      14,    0,   99,    2, 0x08 /* Private */,
      15,    0,  100,    2, 0x08 /* Private */,
      16,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SensorBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SensorBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonSwitch1Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->buttonSwitch2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->temperatureAvailable((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->cpuLoadAvailable((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setGreenLED((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setOrangeLED((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setRedLED((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setAlarm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setupSwitch1Notifier(); break;
        case 9: _t->setupSwitch2Notifier(); break;
        case 10: _t->switch1NotifierActivated(); break;
        case 11: _t->switch2NotifierActivated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SensorBoard::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorBoard::buttonSwitch1Changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SensorBoard::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorBoard::buttonSwitch2Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SensorBoard::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorBoard::temperatureAvailable)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SensorBoard::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorBoard::cpuLoadAvailable)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SensorBoard::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SensorBoard.data,
    qt_meta_data_SensorBoard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SensorBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SensorBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SensorBoard.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SensorBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SensorBoard::buttonSwitch1Changed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SensorBoard::buttonSwitch2Changed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SensorBoard::temperatureAvailable(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SensorBoard::cpuLoadAvailable(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
