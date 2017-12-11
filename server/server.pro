#unix{
#CVPATH=sss
include(../pedestrian.pri)
message($$CVPATH) # execute 3 times

HEADERS+=\
    tools.h \
    camera.h \
    server.h
SOURCES+=main.cpp  \
    tools.cpp \
    camera.cpp \
    server.cpp
#QMAKE_CXXFLAGS+=-std=c++11
unix{
QMAKE_LIBS+=-lpthread
}
QT+=network core


#CVPATH="../../../res"

INCLUDEPATH +="$$CVPATH/include"
unix{
QMAKE_CXXFLAGS+="-std=c++11"
LIBS+=-L$$CVPATH/lib -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video -lX11
}
win32{
CONFIG(debug, debug|release){
#message("debug mode ")
LIBS+=-L$$CVPATH/lib -lopencv_core249d -lopencv_highgui249d -lopencv_objdetect249d -lopencv_imgproc249d -lopencv_ml249d -lopencv_video249d
}else{
LIBS+=-L$$CVPATH/lib -lopencv_core249 -lopencv_highgui249 -lopencv_objdetect249 -lopencv_imgproc249 -lopencv_ml249 -lopencv_video249
#message("release mode ")
}
}
#build_pass:CONFIG(debug, debug|release) {
#    unix: message("os:unix debug ")
#    win32: message("os:win32 debug")
#    else: message("os:else debug")
#}
#build_pass:CONFIG(release, debug|release) {
#    unix: message("os:unix release ")
#    win32: message("os:win32 release")
#    else: message("os:else release")
#}
#LIBS += -lX11 -L/root/sources/opencv-2.4.9/build/__install/lib/  -lopencv_core  -lopencv_highgui  -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video

#}
TARGET = server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS



 #   DEFINES += IS_UNIX
 #   DEFINES += DISPLAY_VIDEO

