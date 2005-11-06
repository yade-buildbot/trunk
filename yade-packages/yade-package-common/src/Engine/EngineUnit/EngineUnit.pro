isEmpty ( YADE_QMAKE_PATH ) {
error( "YADE_QMAKE_PATH internal qmake variable is not set, you should run for example qmake YADE_QMAKE_PATH=/usr/local, this will not work from inside kdevelop (when they will fix it?)" )
}


SUBDIRS += Box2AABB \
           MetaInteractingGeometry2AABB \
           LeapFrogOrientationIntegrator \
           LeapFrogPositionIntegrator \
           NewtonsForceLaw \
           NewtonsMomentumLaw \
           Sphere2AABB \
           CundallNonViscousForceDamping \
           CundallNonViscousMomentumDamping 
CONFIG += debug \
          thread \
warn_on
TEMPLATE = subdirs
INCLUDEPATH += $${YADE_QMAKE_PATH}/include
