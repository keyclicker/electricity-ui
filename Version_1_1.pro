QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include/
DEPENDPATH += include/

HEADERS += include/SourceOfElectricity.hpp\
           include/SourceOfCurrent.hpp\
           include/ComputeCycles.hpp\
           include/EObjectType.hpp\
           include/Dimension.hpp\
           include/Capacitor.hpp\
           include/Resistor.hpp\
           include/Inductor.hpp\
           include/Counter.hpp\
           include/EObject.hpp\
           include/Scheme.hpp\
           include/Graph.hpp\
           include/Rib.hpp\
           include/TestSuite.hpp\

OTHER_FILES += include/Counter.inl\


SOURCES += main.cpp

SOURCES += source/SourceOfElectricity.cpp\
           source/SourceOfCurrent.cpp\
           source/ComputeCycles.cpp\
           source/Capacitor.cpp\
           source/Resistor.cpp\
           source/Inductor.cpp\
           source/EObject.cpp\
           source/Scheme.cpp\
           source/Graph.cpp\
           source/Rib.cpp\
           source/TestSuite.cpp\

INCLUDEPATH += E:/Eigen/
DEPENDPATH += E:/Eigen/

INCLUDEPATH += E:/boost/boost_1_65_1/include
DEPENDPATH += E:/boost/boost_1_65_1/include

#to do compilation faster
CONFIG += precompile_header
PRECOMPILED_HEADER = include/static.hpp
HEADERS += static.hpp
