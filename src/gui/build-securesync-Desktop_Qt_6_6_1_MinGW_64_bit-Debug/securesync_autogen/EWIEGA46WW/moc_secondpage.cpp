/****************************************************************************
** Meta object code from reading C++ file 'secondpage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../securesync/secondpage.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'secondpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSsecondPageENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSsecondPageENDCLASS = QtMocHelpers::stringData(
    "secondPage",
    "on_chooseDirectoryButton_clicked",
    "",
    "on_gitInitButton_clicked",
    "on_gitAddButton_clicked",
    "on_gitPullButton_clicked",
    "on_gitCommitButton_clicked",
    "updateFileList",
    "directoryPath"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSsecondPageENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[11];
    char stringdata1[33];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[24];
    char stringdata5[25];
    char stringdata6[27];
    char stringdata7[15];
    char stringdata8[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSsecondPageENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSsecondPageENDCLASS_t qt_meta_stringdata_CLASSsecondPageENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "secondPage"
        QT_MOC_LITERAL(11, 32),  // "on_chooseDirectoryButton_clicked"
        QT_MOC_LITERAL(44, 0),  // ""
        QT_MOC_LITERAL(45, 24),  // "on_gitInitButton_clicked"
        QT_MOC_LITERAL(70, 23),  // "on_gitAddButton_clicked"
        QT_MOC_LITERAL(94, 24),  // "on_gitPullButton_clicked"
        QT_MOC_LITERAL(119, 26),  // "on_gitCommitButton_clicked"
        QT_MOC_LITERAL(146, 14),  // "updateFileList"
        QT_MOC_LITERAL(161, 13)   // "directoryPath"
    },
    "secondPage",
    "on_chooseDirectoryButton_clicked",
    "",
    "on_gitInitButton_clicked",
    "on_gitAddButton_clicked",
    "on_gitPullButton_clicked",
    "on_gitCommitButton_clicked",
    "updateFileList",
    "directoryPath"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSsecondPageENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    1,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject secondPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSsecondPageENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSsecondPageENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSsecondPageENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<secondPage, std::true_type>,
        // method 'on_chooseDirectoryButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_gitInitButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_gitAddButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_gitPullButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_gitCommitButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateFileList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void secondPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<secondPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_chooseDirectoryButton_clicked(); break;
        case 1: _t->on_gitInitButton_clicked(); break;
        case 2: _t->on_gitAddButton_clicked(); break;
        case 3: _t->on_gitPullButton_clicked(); break;
        case 4: _t->on_gitCommitButton_clicked(); break;
        case 5: _t->updateFileList((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *secondPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *secondPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSsecondPageENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int secondPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
