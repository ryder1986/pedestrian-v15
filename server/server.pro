#unix{
#CVPATH=sss
include(../pedestrian.pri)
message($$CVPATH)

HEADERS+=\
    tools.h \
    camera.h
SOURCES+=main.cpp \
    tools.cpp \
    camera.cpp
QMAKE_CXXFLAGS+=-std=c++11
QMAKE_LIBS+=-lpthread
QT+=network core

QMAKE_CXXFLAGS+="-std=c++11"
#CVPATH="../../../res"
INCLUDEPATH +="$$CVPATH/include"
LIBS+=-L$$CVPATH/lib -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video -lX11
#LIBS += -lX11 -L/root/sources/opencv-2.4.9/build/__install/lib/  -lopencv_core  -lopencv_highgui  -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video

#}
TARGET = server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

unix{

#   DEFINES += IS_UNIX
 #  DEFINES -= IS_UNIX
  }
