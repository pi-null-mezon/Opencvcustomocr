QT += core
QT -= gui

CONFIG += c++11

TARGET = customocr
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include( opencv.pri )
include( tesseract.pri )

DEFINES += OCR_RESOURCES_PATH=\\\"C:/Programming/customocr/Resources/\\\"

