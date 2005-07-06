# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./Engine/EngineUnit/ParticleSet2Mesh2D
# Target is a library:  

HEADERS += ParticleSet2Mesh2D.hpp 
SOURCES += ParticleSet2Mesh2D.cpp 
LIBS += -lParticleSetParameters \
        -lGeometricalModelMetaEngine \
        -lMesh2D \
        -rdynamic 
QMAKE_LIBDIR = ../../../../../bin \
               /usr/local/lib/yade/yade-libs/ 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = ../../../../../bin 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 