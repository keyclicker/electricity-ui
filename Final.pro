QT += core widgets gui

CONFIG += c++14
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include/
DEPENDPATH += include/


HEADERS +=  include/Canvas.h \
            include/Capacitor.hpp \
            include/ComputeCycles.hpp \
            include/Counter.hpp \
            include/Debug.hpp \
            include/Dimension.hpp \
            include/EObject.hpp \
            include/EObjectType.hpp \
            include/GObject.h \
            include/Graph.hpp \
            include/Inductor.hpp \
            include/Line.hpp \
            include/MainWindow.h \
            include/Resistor.hpp \
            include/Rib.hpp \
            include/Scheme.hpp \
            include/Solver.hpp \
            include/SourceOfCurrent.hpp \
            include/SourceOfElectricity.hpp \
            include/static.hpp \
            include/Switcher.hpp \
            include/TestSuite.hpp \
    include/Point.hpp \
    include/inputwindow.h \
    include/Bulb.hpp \
    include/Voltmeter.hpp \
    include/Ammeter.hpp \
    include/Meter.hpp

SOURCES += main.cpp \
           source/Canvas.cpp \
           source/Capacitor.cpp \
           source/ComputeCycles.cpp \
           source/Debug.cpp \
           source/EObject.cpp \
           source/GObject.cpp \
           source/Graph.cpp \
           source/Inductor.cpp \
           source/Line.cpp \
           source/MainWindow.cpp \
           source/Point.cpp \
           source/Resistor.cpp \
           source/Rib.cpp \
           source/Scheme.cpp \
           source/Solver.cpp \
           source/SourceOfCurrent.cpp \
           source/SourceOfElectricity.cpp \
           source/Switcher.cpp \
           source/TestSuite.cpp \
    source/inputwindow.cpp \
    source/Bulb.cpp \
    source/Ammeter.cpp \
    source/Voltmeter.cpp \
    source/Meter.cpp

OTHER_FILES += include/Counter.inl\

include(deps.pri)

#to do compilation faster
CONFIG += precompile_header
PRECOMPILED_HEADER = include/static.hpp

FORMS += \
    forms/mainwindow.ui

RESOURCES += \
    resource.qrc
