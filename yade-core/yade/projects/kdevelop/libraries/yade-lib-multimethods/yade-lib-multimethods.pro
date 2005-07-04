# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./libraries/yade-lib-multimethods
# Target is a library:  

LIBS += -rdynamic 
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
HEADERS += DynLibDispatcher.hpp \
           Indexable.hpp \
           MultiMethodsExceptions.hpp \
           FunctorWrapper.hpp 
SOURCES += MultiMethodsExceptions.cpp \
           Indexable.cpp 