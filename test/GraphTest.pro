QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include/
DEPENDPATH += include/


HEADERS += include/EObjectType.hpp\
           include/EObject.hpp\
           include/Dimension.hpp\
           include/Resistor.hpp\
           include/Inductor.hpp\
           include/Capacitor.hpp\
           include/SourceOfElectricity.hpp\
           include/SourceOfCurrent.hpp\
           include/Rib.hpp\
           include/static.hpp\
           include/Switcher.hpp\
           include/Graph.hpp\
           include/Debug.hpp

SOURCES += source/EObject.cpp\
           source/Resistor.cpp\
           source/Inductor.cpp\
           source/Capacitor.cpp\
           source/SourceOfElectricity.cpp\
           source/SourceOfCurrent.cpp\
           source/Rib.cpp\
           source/Switcher.cpp\
           source/Graph.cpp\
           source/Debug.cpp

SOURCES += test/TestGraph.cpp

INCLUDEPATH += E:\Eigen\
DEPENDPATH += E:\Eigen\

INCLUDEPATH += E:\boost\boost_1_65_1\include\
DEPENDPATH += E:\boost\boost_1_65_1\include\

LIBS += -LE:\boost\boost_1_65_1\lib\ -lboost_unit_test_framework-mgw61-mt-d-1_65_1 \
                                     #-lboost_test_exec_monitor-mgw61-mt-d-1_65_1 \
                                     #-lboost_prg_exec_monitor-mgw61-mt-d-1_65_1

CONFIG += precompile_header
PRECOMPILED_HEADER = include/static.hpp
HEADERS += static.hpp
