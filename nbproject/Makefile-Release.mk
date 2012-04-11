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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/RecForme/Carte.o \
	${OBJECTDIR}/RecForme/NeuroneInput.o \
	${OBJECTDIR}/RecForme/NeuroneCarte.o \
	${OBJECTDIR}/RecForme/main.o


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
LDLIBSOPTIONS=-L/opt/local/lib /opt/local/lib/libpng.dylib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kohonen-code

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kohonen-code: /opt/local/lib/libpng.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kohonen-code: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kohonen-code ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/RecForme/Carte.o: RecForme/Carte.cpp 
	${MKDIR} -p ${OBJECTDIR}/RecForme
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/opt/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/RecForme/Carte.o RecForme/Carte.cpp

${OBJECTDIR}/RecForme/NeuroneInput.o: RecForme/NeuroneInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/RecForme
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/opt/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/RecForme/NeuroneInput.o RecForme/NeuroneInput.cpp

${OBJECTDIR}/RecForme/NeuroneCarte.o: RecForme/NeuroneCarte.cpp 
	${MKDIR} -p ${OBJECTDIR}/RecForme
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/opt/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/RecForme/NeuroneCarte.o RecForme/NeuroneCarte.cpp

${OBJECTDIR}/RecForme/main.o: RecForme/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/RecForme
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/opt/local/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/RecForme/main.o RecForme/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kohonen-code

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
