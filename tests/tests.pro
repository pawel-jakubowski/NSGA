TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += UT
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    TestExample.cpp \
    ../genetic_algorithm/Subject.cpp \
    genetic_algorithm/TestSubject.cpp \
    ../genetic_algorithm/Generation.cpp \
    genetic_algorithm/TestGeneration.cpp \
    ../genetic_algorithm/Population.cpp \
    genetic_algorithm/TestPopulation.cpp \
    ../math/Expression.cpp \
    math/TestExpression.cpp \
    ../math/GoalFunctions.cpp \
    math/TestGoalFunctions.cpp \
    math/TestRandomGenerator.cpp \
    ../math/RandomGenerator.cpp \
    ../genetic_algorithm/Fenotype.cpp \
    genetic_algorithm/TestFenotype.cpp \
    ../genetic_algorithm/Nsga.cpp \
    genetic_algorithm/TestNsga.cpp \
    ../genetic_algorithm/Front.cpp \
    genetic_algorithm/TestFront.cpp \
    ../genetic_algorithm/Fronts.cpp \
    genetic_algorithm/TestFronts.cpp

HEADERS += \
    ../genetic_algorithm/Subject.h \
    ../genetic_algorithm/Generation.h \
    ../genetic_algorithm/Population.h \
    ../math/Expression.h \
    ../libraries/exprtk.hpp \
    ../libraries/CustomAssertion.h \
    genetic_algorithm/GenerationMock.h \
    ../math/GoalFunctions.h \
    ../math/RandomGenerator.h \
    ../genetic_algorithm/Fenotype.h \
    genetic_algorithm/FenotypeMock.h \
    ../interfaces/Core.h \
    ../genetic_algorithm/Nsga.h \
    ../genetic_algorithm/Front.h \
    ../genetic_algorithm/Fronts.h

# add new folders here
INCLUDEPATH += genetic_algorithm/
INCLUDEPATH += ../genetic_algorithm/
INCLUDEPATH += ../interfaces/
INCLUDEPATH += ../libraries/
INCLUDEPATH += ../math/

LIBS += -lunittest++
