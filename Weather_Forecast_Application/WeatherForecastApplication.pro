QT += core gui widgets charts

CONFIG += c++17

TEMPLATE = app

TARGET = WeatherForecastApplication


# ============================================================
# INCLUDE PATHS
# ============================================================

INCLUDEPATH += Includes


# ============================================================
# HEADER FILES
# ============================================================

HEADERS += \
    Includes/Cities.h \
    Includes/DataAbstract.h \
    Includes/Data.h \
    Includes/CurlAbstract.h \
    Includes/Curl.h \
    Includes/RapidjsonAbstract.h \
    Includes/Rapidjson.h \
    GUI/mainWindow.h


# ============================================================
# SOURCE FILES
# ============================================================

SOURCES += \
    main.cpp \
    Sources/Cities.cpp \
    Sources/DataAbstract.cpp \
    Sources/Data.cpp \
    Sources/CurlAbstract.cpp \
    Sources/Curl.cpp \
    Sources/RapidjsonAbstract.cpp \
    Sources/Rapidjson.cpp \
    GUI/mainWindow.cpp


# ============================================================
# LIBRARIES
# ============================================================

LIBS += -lcurl