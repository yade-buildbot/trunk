# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./Engine/EngineUnit/Sphere2Sphere4ClosestFeatures
# Target is a library:  

HEADERS += Sphere2Sphere4ClosestFeatures.hpp 
SOURCES += Sphere2Sphere4ClosestFeatures.cpp 
LIBS += -lInteractionGeometryMetaEngine \
        -lyade-lib-wm3-math \
        -lyade-lib-multimethods \
        -lInteractingSphere \
        -lSphere \
        -lClosestFeatures \
        -rdynamic 
QMAKE_LIBDIR = /usr/local/lib/yade/yade-libs/ 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = ../../../../../bin 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 