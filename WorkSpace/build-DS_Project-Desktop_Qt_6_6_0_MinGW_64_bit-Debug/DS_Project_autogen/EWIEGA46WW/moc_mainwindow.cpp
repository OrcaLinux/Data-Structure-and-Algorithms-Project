/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../DS_Project/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "openNewTabHandler",
    "",
    "on_actionCut_triggered",
    "on_actionExit_triggered",
    "on_actionCopy_triggered",
    "on_actionPast_triggered",
    "on_actionUndo_triggered",
    "on_actionRedo_triggered",
    "on_actionAbout_Qt_triggered",
    "quitApp",
    "createNewTab",
    "closeTab",
    "index",
    "handleFormatTheFileRequest",
    "QTextEdit*",
    "textEdit",
    "eventFilter",
    "obj",
    "QEvent*",
    "event",
    "extensionLabel",
    "expectedExtension",
    "saveDialogBox",
    "std::vector<QString>",
    "expectedExtensions",
    "fileName",
    "compressFile",
    "decompressFile",
    "filePath",
    "searchButtonClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[62];
    char stringdata0[11];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[24];
    char stringdata5[24];
    char stringdata6[24];
    char stringdata7[24];
    char stringdata8[24];
    char stringdata9[28];
    char stringdata10[8];
    char stringdata11[13];
    char stringdata12[9];
    char stringdata13[6];
    char stringdata14[27];
    char stringdata15[11];
    char stringdata16[9];
    char stringdata17[12];
    char stringdata18[4];
    char stringdata19[8];
    char stringdata20[6];
    char stringdata21[15];
    char stringdata22[18];
    char stringdata23[14];
    char stringdata24[21];
    char stringdata25[19];
    char stringdata26[9];
    char stringdata27[13];
    char stringdata28[15];
    char stringdata29[9];
    char stringdata30[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 17),  // "openNewTabHandler"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 22),  // "on_actionCut_triggered"
        QT_MOC_LITERAL(53, 23),  // "on_actionExit_triggered"
        QT_MOC_LITERAL(77, 23),  // "on_actionCopy_triggered"
        QT_MOC_LITERAL(101, 23),  // "on_actionPast_triggered"
        QT_MOC_LITERAL(125, 23),  // "on_actionUndo_triggered"
        QT_MOC_LITERAL(149, 23),  // "on_actionRedo_triggered"
        QT_MOC_LITERAL(173, 27),  // "on_actionAbout_Qt_triggered"
        QT_MOC_LITERAL(201, 7),  // "quitApp"
        QT_MOC_LITERAL(209, 12),  // "createNewTab"
        QT_MOC_LITERAL(222, 8),  // "closeTab"
        QT_MOC_LITERAL(231, 5),  // "index"
        QT_MOC_LITERAL(237, 26),  // "handleFormatTheFileRequest"
        QT_MOC_LITERAL(264, 10),  // "QTextEdit*"
        QT_MOC_LITERAL(275, 8),  // "textEdit"
        QT_MOC_LITERAL(284, 11),  // "eventFilter"
        QT_MOC_LITERAL(296, 3),  // "obj"
        QT_MOC_LITERAL(300, 7),  // "QEvent*"
        QT_MOC_LITERAL(308, 5),  // "event"
        QT_MOC_LITERAL(314, 14),  // "extensionLabel"
        QT_MOC_LITERAL(329, 17),  // "expectedExtension"
        QT_MOC_LITERAL(347, 13),  // "saveDialogBox"
        QT_MOC_LITERAL(361, 20),  // "std::vector<QString>"
        QT_MOC_LITERAL(382, 18),  // "expectedExtensions"
        QT_MOC_LITERAL(401, 8),  // "fileName"
        QT_MOC_LITERAL(410, 12),  // "compressFile"
        QT_MOC_LITERAL(423, 14),  // "decompressFile"
        QT_MOC_LITERAL(438, 8),  // "filePath"
        QT_MOC_LITERAL(447, 19)   // "searchButtonClicked"
    },
    "MainWindow",
    "openNewTabHandler",
    "",
    "on_actionCut_triggered",
    "on_actionExit_triggered",
    "on_actionCopy_triggered",
    "on_actionPast_triggered",
    "on_actionUndo_triggered",
    "on_actionRedo_triggered",
    "on_actionAbout_Qt_triggered",
    "quitApp",
    "createNewTab",
    "closeTab",
    "index",
    "handleFormatTheFileRequest",
    "QTextEdit*",
    "textEdit",
    "eventFilter",
    "obj",
    "QEvent*",
    "event",
    "extensionLabel",
    "expectedExtension",
    "saveDialogBox",
    "std::vector<QString>",
    "expectedExtensions",
    "fileName",
    "compressFile",
    "decompressFile",
    "filePath",
    "searchButtonClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  134,    2, 0x08,    1 /* Private */,
       3,    0,  135,    2, 0x08,    2 /* Private */,
       4,    0,  136,    2, 0x08,    3 /* Private */,
       5,    0,  137,    2, 0x08,    4 /* Private */,
       6,    0,  138,    2, 0x08,    5 /* Private */,
       7,    0,  139,    2, 0x08,    6 /* Private */,
       8,    0,  140,    2, 0x08,    7 /* Private */,
       9,    0,  141,    2, 0x08,    8 /* Private */,
      10,    0,  142,    2, 0x08,    9 /* Private */,
      11,    0,  143,    2, 0x08,   10 /* Private */,
      12,    1,  144,    2, 0x08,   11 /* Private */,
      14,    1,  147,    2, 0x08,   13 /* Private */,
      17,    2,  150,    2, 0x08,   15 /* Private */,
      21,    1,  155,    2, 0x08,   18 /* Private */,
      23,    1,  158,    2, 0x08,   20 /* Private */,
      23,    1,  161,    2, 0x08,   22 /* Private */,
      14,    2,  164,    2, 0x08,   24 /* Private */,
      27,    2,  169,    2, 0x08,   27 /* Private */,
      28,    1,  174,    2, 0x08,   30 /* Private */,
      30,    1,  177,    2, 0x08,   32 /* Private */,

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
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 19,   18,   20,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, 0x80000000 | 24,   25,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 15,   26,   16,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 15,   26,   16,
    QMetaType::QString, QMetaType::QString,   29,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'openNewTabHandler'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionCut_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionExit_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionCopy_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionPast_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionUndo_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionRedo_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionAbout_Qt_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitApp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createNewTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleFormatTheFileRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTextEdit *, std::false_type>,
        // method 'eventFilter'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QEvent *, std::false_type>,
        // method 'extensionLabel'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'saveDialogBox'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'saveDialogBox'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<QString> &, std::false_type>,
        // method 'handleFormatTheFileRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTextEdit *, std::false_type>,
        // method 'compressFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTextEdit *, std::false_type>,
        // method 'decompressFile'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'searchButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTextEdit *, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openNewTabHandler(); break;
        case 1: _t->on_actionCut_triggered(); break;
        case 2: _t->on_actionExit_triggered(); break;
        case 3: _t->on_actionCopy_triggered(); break;
        case 4: _t->on_actionPast_triggered(); break;
        case 5: _t->on_actionUndo_triggered(); break;
        case 6: _t->on_actionRedo_triggered(); break;
        case 7: _t->on_actionAbout_Qt_triggered(); break;
        case 8: _t->quitApp(); break;
        case 9: _t->createNewTab(); break;
        case 10: _t->closeTab((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->handleFormatTheFileRequest((*reinterpret_cast< std::add_pointer_t<QTextEdit*>>(_a[1]))); break;
        case 12: { bool _r = _t->eventFilter((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QEvent*>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { QString _r = _t->extensionLabel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { QString _r = _t->saveDialogBox((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 15: { QString _r = _t->saveDialogBox((*reinterpret_cast< std::add_pointer_t<std::vector<QString>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->handleFormatTheFileRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTextEdit*>>(_a[2]))); break;
        case 17: _t->compressFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTextEdit*>>(_a[2]))); break;
        case 18: { QString _r = _t->decompressFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->searchButtonClicked((*reinterpret_cast< std::add_pointer_t<QTextEdit*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTextEdit* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTextEdit* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTextEdit* >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTextEdit* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
