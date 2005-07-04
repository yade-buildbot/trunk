# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./libraries/yade-lib-opengl
# Target is a library:  

LIBS += -lyade-lib-time \
        -lglut 
INCLUDEPATH += $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = $(YADEDYNLIBPATH)/yade-libs 
DESTDIR = $(YADEDYNLIBPATH)/yade-libs 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += FpsTracker.hpp \
           GLTextLabel.hpp \
           GLWindow.hpp \
           GLWindowsManager.hpp \
           OpenGLWrapper.hpp 
SOURCES += FpsTracker.cpp \
           GLTextLabel.cpp \
           GLWindow.cpp \
           GLWindowsManager.cpp 