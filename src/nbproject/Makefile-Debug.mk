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
QMAKE=qmake

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES=


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
LDLIBSOPTIONS=/C/opencv/release/lib/libopencv_calib3d2410.dll.a /C/opencv/release/lib/libopencv_calib3d_pch_dephelp.a /C/opencv/release/lib/libopencv_contrib2410.dll.a /C/opencv/release/lib/libopencv_contrib_pch_dephelp.a /C/opencv/release/lib/libopencv_core2410.dll.a /C/opencv/release/lib/libopencv_core_pch_dephelp.a /C/opencv/release/lib/libopencv_features2d2410.dll.a /C/opencv/release/lib/libopencv_features2d_pch_dephelp.a /C/opencv/release/lib/libopencv_flann2410.dll.a /C/opencv/release/lib/libopencv_flann_pch_dephelp.a /C/opencv/release/lib/libopencv_gpu2410.dll.a /C/opencv/release/lib/libopencv_gpu_pch_dephelp.a /C/opencv/release/lib/libopencv_haartraining_engine.a /C/opencv/release/lib/libopencv_highgui2410.dll.a /C/opencv/release/lib/libopencv_highgui_pch_dephelp.a /C/opencv/release/lib/libopencv_imgproc2410.dll.a /C/opencv/release/lib/libopencv_imgproc_pch_dephelp.a /C/opencv/release/lib/libopencv_legacy2410.dll.a /C/opencv/release/lib/libopencv_legacy_pch_dephelp.a /C/opencv/release/lib/libopencv_ml2410.dll.a /C/opencv/release/lib/libopencv_ml_pch_dephelp.a /C/opencv/release/lib/libopencv_nonfree2410.dll.a /C/opencv/release/lib/libopencv_nonfree_pch_dephelp.a /C/opencv/release/lib/libopencv_objdetect2410.dll.a /C/opencv/release/lib/libopencv_objdetect_pch_dephelp.a /C/opencv/release/lib/libopencv_ocl2410.dll.a /C/opencv/release/lib/libopencv_ocl_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_calib3d_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_core_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_features2d_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_gpu_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_highgui_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_imgproc_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_nonfree_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_objdetect_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_ocl_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_photo_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_stitching_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_superres_pch_dephelp.a /C/opencv/release/lib/libopencv_perf_video_pch_dephelp.a /C/opencv/release/lib/libopencv_photo2410.dll.a /C/opencv/release/lib/libopencv_photo_pch_dephelp.a /C/opencv/release/lib/libopencv_stitching2410.dll.a /C/opencv/release/lib/libopencv_stitching_pch_dephelp.a /C/opencv/release/lib/libopencv_superres2410.dll.a /C/opencv/release/lib/libopencv_superres_pch_dephelp.a /C/opencv/release/lib/libopencv_test_calib3d_pch_dephelp.a /C/opencv/release/lib/libopencv_test_contrib_pch_dephelp.a /C/opencv/release/lib/libopencv_test_core_pch_dephelp.a /C/opencv/release/lib/libopencv_test_features2d_pch_dephelp.a /C/opencv/release/lib/libopencv_test_flann_pch_dephelp.a /C/opencv/release/lib/libopencv_test_gpu_pch_dephelp.a /C/opencv/release/lib/libopencv_test_highgui_pch_dephelp.a /C/opencv/release/lib/libopencv_test_imgproc_pch_dephelp.a /C/opencv/release/lib/libopencv_test_legacy_pch_dephelp.a /C/opencv/release/lib/libopencv_test_ml_pch_dephelp.a /C/opencv/release/lib/libopencv_test_nonfree_pch_dephelp.a /C/opencv/release/lib/libopencv_test_objdetect_pch_dephelp.a /C/opencv/release/lib/libopencv_test_ocl_pch_dephelp.a /C/opencv/release/lib/libopencv_test_photo_pch_dephelp.a /C/opencv/release/lib/libopencv_test_stitching_pch_dephelp.a /C/opencv/release/lib/libopencv_test_superres_pch_dephelp.a /C/opencv/release/lib/libopencv_test_video_pch_dephelp.a /C/opencv/release/lib/libopencv_ts2410.a /C/opencv/release/lib/libopencv_ts_pch_dephelp.a /C/opencv/release/lib/libopencv_video2410.dll.a /C/opencv/release/lib/libopencv_video_pch_dephelp.a /C/opencv/release/lib/libopencv_videostab2410.dll.a /C/opencv/release/lib/libopencv_videostab_pch_dephelp.a

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -spec win32-g++ -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk
	@sed -e 's/\/qt\/bin/\/qt\/bin\//g' nbproject/qt-${CND_CONF}.mk >nbproject/qt-${CND_CONF}.tmp
	@mv -f nbproject/qt-${CND_CONF}.tmp nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/RealTimeDrawingSystemGUIOK.exe

${CND_BUILDDIR}/Debug/%.o: nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk "$@"

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk distclean

# Subprojects
.clean-subprojects:
