# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/MinGW-Windows
TARGET = RealTimeDrawingSystemGUIOK
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += Button.cpp ButtonManager.cpp CalibrationData.cpp ColorDecision.cpp Cross.cpp Homography.cpp InkDetection.cpp Introduction.cpp Parameters.cpp SheetDetection.cpp Utils.cpp VideoAnalyzer.cpp Welcome.cpp main.cpp
HEADERS += Button.h ButtonManager.h CalibrationData.h ColorDecision.h Cross.h Homography.h InkDetection.h Introduction.h Parameters.h SheetDetection.h Utils.h VideoAnalyzer.h Welcome.h
FORMS += Introduction.ui Welcome.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /C/opencv/build/include 
LIBS += C:/opencv/release/lib/libopencv_calib3d2410.dll.a C:/opencv/release/lib/libopencv_calib3d_pch_dephelp.a C:/opencv/release/lib/libopencv_contrib2410.dll.a C:/opencv/release/lib/libopencv_contrib_pch_dephelp.a C:/opencv/release/lib/libopencv_core2410.dll.a C:/opencv/release/lib/libopencv_core_pch_dephelp.a C:/opencv/release/lib/libopencv_features2d2410.dll.a C:/opencv/release/lib/libopencv_features2d_pch_dephelp.a C:/opencv/release/lib/libopencv_flann2410.dll.a C:/opencv/release/lib/libopencv_flann_pch_dephelp.a C:/opencv/release/lib/libopencv_gpu2410.dll.a C:/opencv/release/lib/libopencv_gpu_pch_dephelp.a C:/opencv/release/lib/libopencv_haartraining_engine.a C:/opencv/release/lib/libopencv_highgui2410.dll.a C:/opencv/release/lib/libopencv_highgui_pch_dephelp.a C:/opencv/release/lib/libopencv_imgproc2410.dll.a C:/opencv/release/lib/libopencv_imgproc_pch_dephelp.a C:/opencv/release/lib/libopencv_legacy2410.dll.a C:/opencv/release/lib/libopencv_legacy_pch_dephelp.a C:/opencv/release/lib/libopencv_ml2410.dll.a C:/opencv/release/lib/libopencv_ml_pch_dephelp.a C:/opencv/release/lib/libopencv_nonfree2410.dll.a C:/opencv/release/lib/libopencv_nonfree_pch_dephelp.a C:/opencv/release/lib/libopencv_objdetect2410.dll.a C:/opencv/release/lib/libopencv_objdetect_pch_dephelp.a C:/opencv/release/lib/libopencv_ocl2410.dll.a C:/opencv/release/lib/libopencv_ocl_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_calib3d_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_core_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_features2d_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_gpu_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_highgui_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_imgproc_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_nonfree_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_objdetect_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_ocl_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_photo_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_stitching_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_superres_pch_dephelp.a C:/opencv/release/lib/libopencv_perf_video_pch_dephelp.a C:/opencv/release/lib/libopencv_photo2410.dll.a C:/opencv/release/lib/libopencv_photo_pch_dephelp.a C:/opencv/release/lib/libopencv_stitching2410.dll.a C:/opencv/release/lib/libopencv_stitching_pch_dephelp.a C:/opencv/release/lib/libopencv_superres2410.dll.a C:/opencv/release/lib/libopencv_superres_pch_dephelp.a C:/opencv/release/lib/libopencv_test_calib3d_pch_dephelp.a C:/opencv/release/lib/libopencv_test_contrib_pch_dephelp.a C:/opencv/release/lib/libopencv_test_core_pch_dephelp.a C:/opencv/release/lib/libopencv_test_features2d_pch_dephelp.a C:/opencv/release/lib/libopencv_test_flann_pch_dephelp.a C:/opencv/release/lib/libopencv_test_gpu_pch_dephelp.a C:/opencv/release/lib/libopencv_test_highgui_pch_dephelp.a C:/opencv/release/lib/libopencv_test_imgproc_pch_dephelp.a C:/opencv/release/lib/libopencv_test_legacy_pch_dephelp.a C:/opencv/release/lib/libopencv_test_ml_pch_dephelp.a C:/opencv/release/lib/libopencv_test_nonfree_pch_dephelp.a C:/opencv/release/lib/libopencv_test_objdetect_pch_dephelp.a C:/opencv/release/lib/libopencv_test_ocl_pch_dephelp.a C:/opencv/release/lib/libopencv_test_photo_pch_dephelp.a C:/opencv/release/lib/libopencv_test_stitching_pch_dephelp.a C:/opencv/release/lib/libopencv_test_superres_pch_dephelp.a C:/opencv/release/lib/libopencv_test_video_pch_dephelp.a C:/opencv/release/lib/libopencv_ts2410.a C:/opencv/release/lib/libopencv_ts_pch_dephelp.a C:/opencv/release/lib/libopencv_video2410.dll.a C:/opencv/release/lib/libopencv_video_pch_dephelp.a C:/opencv/release/lib/libopencv_videostab2410.dll.a C:/opencv/release/lib/libopencv_videostab_pch_dephelp.a  
"LIBS +=C:/opencv/release/lib"
