# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./yade-lib-factory
# Target is a library:  ../../../bin/yade-lib-factory

INCLUDEPATH += /usr/local/include/yade 
TARGET = ../../../bin/yade-lib-factory 
CONFIG += release \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += ClassFactory.hpp \
           DynLibManager.hpp \
           Factorable.hpp \
           FactoryExceptions.hpp 
SOURCES += ClassFactory.cpp \
           DynLibManager.cpp \
           Factorable.cpp \
           FactoryExceptions.cpp 