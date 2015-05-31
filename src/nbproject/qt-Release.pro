# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/MinGW-Windows
TARGET = RealTimeDrawingSystemGUIOK
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += Button.cpp ButtonManager.cpp CalibrationData.cpp ColorDecision.cpp Cross.cpp Homography.cpp InkDetection.cpp Introduction.cpp Parameters.cpp SheetDetection.cpp Utils.cpp VideoAnalyzer.cpp Welcome.cpp main.cpp
HEADERS += Button.h ButtonManager.h CalibrationData.h ColorDecision.h Cross.h Homography.h InkDetection.h Introduction.h Parameters.h SheetDetection.h Utils.h VideoAnalyzer.h Welcome.h
FORMS += Introduction.ui Welcome.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
