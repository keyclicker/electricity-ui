QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += include/
DEPENDPATH += include/


HEADERS += include/EObjectType.hpp\
           include/EObject.hpp\
           include/Dimension.hpp\
           include/Resistor.hpp\
           include/Inductor.hpp\
           include/Capacitor.hpp\
           include/SourceOfElectricity.hpp\
           include/SourceOfCurrent.hpp \
           include/Switcher.hpp \
           include/static.hpp

SOURCES += source/EObject.cpp\
           source/Resistor.cpp\
           source/Inductor.cpp\
           source/Capacitor.cpp\
           source/SourceOfElectricity.cpp\
           source/SourceOfCurrent.cpp \
           source/Switcher.cpp

INCLUDEPATH += E:/Eigen/
DEPENDPATH += E:/Eigen/

INCLUDEPATH += E:\boost\boost_1_65_1\include\
DEPENDPATH += E:\boost\boost_1_65_1\include\

LIBS += -LE:\boost\boost_1_65_1\lib\ -lboost_unit_test_framework-mgw61-mt-d-1_65_1 \
                                     -lboost_test_exec_monitor-mgw61-mt-d-1_65_1 \
                                     -lboost_prg_exec_monitor-mgw61-mt-d-1_65_1

SOURCES += test/TestEObject.cpp

CONFIG += precompile_header
PRECOMPILED_HEADER = include/static.hpp
HEADERS += static.hpp


