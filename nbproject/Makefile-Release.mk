#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Biome/Desert.o \
	${OBJECTDIR}/Biome/Flatland.o \
	${OBJECTDIR}/Biome/Forest.o \
	${OBJECTDIR}/Biome/Hell.o \
	${OBJECTDIR}/Biome/MountainRange.o \
	${OBJECTDIR}/Gui/Draw.o \
	${OBJECTDIR}/Gui/Event.o \
	${OBJECTDIR}/Gui/Gui.o \
	${OBJECTDIR}/Gui/LoadingScreen.o \
	${OBJECTDIR}/Gui/Popup/DisplayTypeMenu.o \
	${OBJECTDIR}/Gui/Popup/MapCommandMenu.o \
	${OBJECTDIR}/Gui/Popup/PopupMenu.o \
	${OBJECTDIR}/Matter/Animal.o \
	${OBJECTDIR}/Matter/Covering.o \
	${OBJECTDIR}/Matter/Fluid.o \
	${OBJECTDIR}/Matter/Food.o \
	${OBJECTDIR}/Matter/Fruit.o \
	${OBJECTDIR}/Matter/Grass.o \
	${OBJECTDIR}/Matter/Lava.o \
	${OBJECTDIR}/Matter/Liquid.o \
	${OBJECTDIR}/Matter/Matter.o \
	${OBJECTDIR}/Matter/Mobador.o \
	${OBJECTDIR}/Matter/Plant.o \
	${OBJECTDIR}/Matter/Roots.o \
	${OBJECTDIR}/Matter/Sky.o \
	${OBJECTDIR}/Matter/Snow.o \
	${OBJECTDIR}/Matter/Spring.o \
	${OBJECTDIR}/Matter/Terrain.o \
	${OBJECTDIR}/Matter/Thing.o \
	${OBJECTDIR}/Matter/Tree.o \
	${OBJECTDIR}/Matter/Water.o \
	${OBJECTDIR}/Ref/Dir.o \
	${OBJECTDIR}/Ref/DisplayType.o \
	${OBJECTDIR}/Ref/Earth.o \
	${OBJECTDIR}/Ref/FluidVel.o \
	${OBJECTDIR}/Ref/SizeVal.o \
	${OBJECTDIR}/Ref/Type.o \
	${OBJECTDIR}/Ref/Util.o \
	${OBJECTDIR}/Ref/Vector.o \
	${OBJECTDIR}/World/Animalia.o \
	${OBJECTDIR}/World/Game.o \
	${OBJECTDIR}/World/Grid.o \
	${OBJECTDIR}/World/Map.o \
	${OBJECTDIR}/World/Species.o \
	${OBJECTDIR}/World/Square.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eden

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eden: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eden ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Biome/Desert.o: Biome/Desert.cpp 
	${MKDIR} -p ${OBJECTDIR}/Biome
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Biome/Desert.o Biome/Desert.cpp

${OBJECTDIR}/Biome/Flatland.o: Biome/Flatland.cpp 
	${MKDIR} -p ${OBJECTDIR}/Biome
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Biome/Flatland.o Biome/Flatland.cpp

${OBJECTDIR}/Biome/Forest.o: Biome/Forest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Biome
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Biome/Forest.o Biome/Forest.cpp

${OBJECTDIR}/Biome/Hell.o: Biome/Hell.cpp 
	${MKDIR} -p ${OBJECTDIR}/Biome
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Biome/Hell.o Biome/Hell.cpp

${OBJECTDIR}/Biome/MountainRange.o: Biome/MountainRange.cpp 
	${MKDIR} -p ${OBJECTDIR}/Biome
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Biome/MountainRange.o Biome/MountainRange.cpp

${OBJECTDIR}/Gui/Draw.o: Gui/Draw.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gui/Draw.o Gui/Draw.cpp

${OBJECTDIR}/Gui/Event.o: Gui/Event.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gui/Event.o Gui/Event.cpp

${OBJECTDIR}/Gui/Gui.o: Gui/Gui.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gui/Gui.o Gui/Gui.cpp

${OBJECTDIR}/Gui/LoadingScreen.o: Gui/LoadingScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gui/LoadingScreen.o Gui/LoadingScreen.cpp

${OBJECTDIR}/Gui/Popup/DisplayTypeMenu.o: Gui/Popup/DisplayTypeMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui/Popup
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gui/Popup/DisplayTypeMenu.o Gui/Popup/DisplayTypeMenu.cpp

${OBJECTDIR}/Gui/Popup/MapCommandMenu.o: Gui/Popup/MapCommandMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui/Popup
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gui/Popup/MapCommandMenu.o Gui/Popup/MapCommandMenu.cpp

${OBJECTDIR}/Gui/Popup/PopupMenu.o: Gui/Popup/PopupMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui/Popup
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gui/Popup/PopupMenu.o Gui/Popup/PopupMenu.cpp

${OBJECTDIR}/Matter/Animal.o: Matter/Animal.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Animal.o Matter/Animal.cpp

${OBJECTDIR}/Matter/Covering.o: Matter/Covering.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Covering.o Matter/Covering.cpp

${OBJECTDIR}/Matter/Fluid.o: Matter/Fluid.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Fluid.o Matter/Fluid.cpp

${OBJECTDIR}/Matter/Food.o: Matter/Food.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Food.o Matter/Food.cpp

${OBJECTDIR}/Matter/Fruit.o: Matter/Fruit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Fruit.o Matter/Fruit.cpp

${OBJECTDIR}/Matter/Grass.o: Matter/Grass.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Grass.o Matter/Grass.cpp

${OBJECTDIR}/Matter/Lava.o: Matter/Lava.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Lava.o Matter/Lava.cpp

${OBJECTDIR}/Matter/Liquid.o: Matter/Liquid.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Liquid.o Matter/Liquid.cpp

${OBJECTDIR}/Matter/Matter.o: Matter/Matter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Matter.o Matter/Matter.cpp

${OBJECTDIR}/Matter/Mobador.o: Matter/Mobador.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Mobador.o Matter/Mobador.cpp

${OBJECTDIR}/Matter/Plant.o: Matter/Plant.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Plant.o Matter/Plant.cpp

${OBJECTDIR}/Matter/Roots.o: Matter/Roots.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Roots.o Matter/Roots.cpp

${OBJECTDIR}/Matter/Sky.o: Matter/Sky.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Sky.o Matter/Sky.cpp

${OBJECTDIR}/Matter/Snow.o: Matter/Snow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Snow.o Matter/Snow.cpp

${OBJECTDIR}/Matter/Spring.o: Matter/Spring.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Spring.o Matter/Spring.cpp

${OBJECTDIR}/Matter/Terrain.o: Matter/Terrain.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Terrain.o Matter/Terrain.cpp

${OBJECTDIR}/Matter/Thing.o: Matter/Thing.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Thing.o Matter/Thing.cpp

${OBJECTDIR}/Matter/Tree.o: Matter/Tree.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Tree.o Matter/Tree.cpp

${OBJECTDIR}/Matter/Water.o: Matter/Water.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matter
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matter/Water.o Matter/Water.cpp

${OBJECTDIR}/Ref/Dir.o: Ref/Dir.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/Dir.o Ref/Dir.cpp

${OBJECTDIR}/Ref/DisplayType.o: Ref/DisplayType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/DisplayType.o Ref/DisplayType.cpp

${OBJECTDIR}/Ref/Earth.o: Ref/Earth.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/Earth.o Ref/Earth.cpp

${OBJECTDIR}/Ref/FluidVel.o: Ref/FluidVel.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/FluidVel.o Ref/FluidVel.cpp

${OBJECTDIR}/Ref/SizeVal.o: Ref/SizeVal.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/SizeVal.o Ref/SizeVal.cpp

${OBJECTDIR}/Ref/Type.o: Ref/Type.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/Type.o Ref/Type.cpp

${OBJECTDIR}/Ref/Util.o: Ref/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/Util.o Ref/Util.cpp

${OBJECTDIR}/Ref/Vector.o: Ref/Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/Ref
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ref/Vector.o Ref/Vector.cpp

${OBJECTDIR}/World/Animalia.o: World/Animalia.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Animalia.o World/Animalia.cpp

${OBJECTDIR}/World/Game.o: World/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Game.o World/Game.cpp

${OBJECTDIR}/World/Grid.o: World/Grid.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Grid.o World/Grid.cpp

${OBJECTDIR}/World/Map.o: World/Map.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Map.o World/Map.cpp

${OBJECTDIR}/World/Species.o: World/Species.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Species.o World/Species.cpp

${OBJECTDIR}/World/Square.o: World/Square.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Square.o World/Square.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eden

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
