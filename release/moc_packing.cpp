/****************************************************************************
** Meta object code from reading C++ file 'packing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../packing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Packing_t {
    QByteArrayData data[13];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Packing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Packing_t qt_meta_stringdata_Packing = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Packing"
QT_MOC_LITERAL(1, 8, 13), // "loadcontainer"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "loadcom"
QT_MOC_LITERAL(4, 31, 9), // "addpacket"
QT_MOC_LITERAL(5, 41, 7), // "addinfo"
QT_MOC_LITERAL(6, 49, 5), // "name2"
QT_MOC_LITERAL(7, 55, 4), // "num1"
QT_MOC_LITERAL(8, 60, 1), // "l"
QT_MOC_LITERAL(9, 62, 1), // "w"
QT_MOC_LITERAL(10, 64, 1), // "h"
QT_MOC_LITERAL(11, 66, 11), // "exportexcel"
QT_MOC_LITERAL(12, 78, 11) // "empytytable"

    },
    "Packing\0loadcontainer\0\0loadcom\0addpacket\0"
    "addinfo\0name2\0num1\0l\0w\0h\0exportexcel\0"
    "empytytable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Packing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    5,   47,    2, 0x0a /* Public */,
      11,    0,   58,    2, 0x0a /* Public */,
      12,    0,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,    6,    7,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Packing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Packing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadcontainer(); break;
        case 1: _t->loadcom(); break;
        case 2: _t->addpacket(); break;
        case 3: _t->addinfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 4: _t->exportexcel(); break;
        case 5: _t->empytytable(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Packing::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Packing.data,
    qt_meta_data_Packing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Packing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Packing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Packing.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Packing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
