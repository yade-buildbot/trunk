# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./libraries/yade-lib-wm3-math
# Target is a library:  

LIBS += -lm \
        -rdynamic 
INCLUDEPATH += $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = $(YADEDYNLIBPATH)/yade-libs 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = $(YADEDYNLIBPATH)/yade-libs 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += Se3.hpp \
           Se3.ipp \
           Math.hpp \
           Matrix2.hpp \
           Matrix3.hpp \
           Matrix4.hpp \
           Quaternion.hpp \
           Vector2.hpp \
           Vector3.hpp \
           Vector4.hpp \
           Math.ipp \
           Matrix2.ipp \
           Matrix3.ipp \
           Matrix4.ipp \
           Quaternion.ipp \
           Vector2.ipp \
           Vector3.ipp \
           Vector4.ipp 
SOURCES += Se3.cpp \
           Math.cpp \
           Matrix2.cpp \
           Matrix3.cpp \
           Matrix4.cpp \
           Quaternion.cpp \
           Vector2.cpp \
           Vector3.cpp \
           Vector4.cpp 